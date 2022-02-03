#include "erroneousDetection.h"
#include <iostream>

ErroneousDetection::ErroneousDetection(const char *fileDir)
{
    csvHandler = new Csv(fileDir);
}

ErroneousDetection::~ErroneousDetection()
{
    delete csvHandler;
}

//Detect if the line contains data for a new node
bool ErroneousDetection::isANewNode(unsigned int ID)
{
    if (std::any_of(uniqueNodes.begin(), uniqueNodes.end(), [=](const NodeData nodeData)
                    { return nodeData.ID == ID; }))
    {
        return false;
    }
    return true;
}

void ErroneousDetection::convertSensorDataToNodeData(SensorData sensorData)
{
    NodeData receivedNodeData;
    receivedNodeData.ID = sensorData.ID;
    for (int i : {0, 1})
    {
        receivedNodeData.overlapSum[i] = 0;
        receivedNodeData.gapSum[i] = 0;
    }
    receivedNodeData.data[sensorData.streamID - 2].isReceived = true;
    receivedNodeData.data[sensorData.streamID - 2].lastEpoch = sensorData.epoch;
    receivedNodeData.data[sensorData.streamID - 2].lastDuration = sensorData.duration;
    uniqueNodes.push_back(receivedNodeData);
}

void ErroneousDetection::calculateGapAndOverlap(unsigned int nodeIndex, SensorData sensorData)
{
    double expectedEpoch = uniqueNodes[nodeIndex].data[sensorData.streamID - 2].lastEpoch + uniqueNodes[nodeIndex].data[sensorData.streamID - 2].lastDuration;
    // Calc Gap
    if(sensorData.epoch - expectedEpoch > 0.1) {
        uniqueNodes[nodeIndex].gapSum[sensorData.streamID - 2] += sensorData.epoch - expectedEpoch;
    }
    // Calc Overlap
    if(expectedEpoch - sensorData.epoch > 0.1) {
        uniqueNodes[nodeIndex].overlapSum[sensorData.streamID - 2] += expectedEpoch - sensorData.epoch;
    }
    uniqueNodes[nodeIndex].data[sensorData.streamID - 2].lastEpoch = sensorData.epoch;
    uniqueNodes[nodeIndex].data[sensorData.streamID - 2].lastDuration = sensorData.duration;
}

void ErroneousDetection::detect(void)
{
    SensorData receivedData;
    while (csvHandler->readCsvLine(&receivedData))
    {
        if (isANewNode(receivedData.ID))
        {

            convertSensorDataToNodeData(receivedData);
        }
        else
        {
            //Find the node index that we already found
            auto it = std::find_if(uniqueNodes.begin(), uniqueNodes.end(), [=](const NodeData nodeData)
                                   { return nodeData.ID == receivedData.ID; });
            // Check if the stream data has been filled before or not
            if (uniqueNodes[std::distance(uniqueNodes.begin(), it)].data[receivedData.streamID - 2].isReceived == false)
            {
                uniqueNodes[std::distance(uniqueNodes.begin(), it)].data[receivedData.streamID - 2].isReceived = true;
                uniqueNodes[std::distance(uniqueNodes.begin(), it)].data[receivedData.streamID - 2].lastEpoch = receivedData.epoch;
                uniqueNodes[std::distance(uniqueNodes.begin(), it)].data[receivedData.streamID - 2].lastDuration = receivedData.duration;
            }
            else
            {
                calculateGapAndOverlap(std::distance(uniqueNodes.begin(), it), receivedData);
            }
        }
    }
    std::cout << std::endl;
    for(auto a: uniqueNodes) {
        std::cout<<a.ID<<" "<<a.gapSum[0]<<" "<<a.overlapSum[0]<<" "<<a.gapSum[1]<<" "<<a.overlapSum[1]<< std::endl;
    }
}

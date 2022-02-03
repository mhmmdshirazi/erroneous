#ifndef _ERRONEOUS_DETECTION_H
#define _ERRONEOUS_DETECTION_H

//Defines and Includes
#include <vector>
#include "dataExtractor.h"

struct StreamData {
    double epoch, lastEpoch;
    double duration, lastDuration;
    bool isReceived;
};

struct NodeData {
    unsigned int ID;
    StreamData data[2];
    double gapSum[2], overlapSum[2];
};

// Detect erroneous data
class ErroneousDetection
{
private:
    std::vector <NodeData> uniqueNodes;
    bool isANewNode(unsigned int ID);
    void convertSensorDataToNodeData(SensorData SensorData);
    void calculateGapAndOverlap(unsigned int nodeIndex, SensorData sensorData);
    Csv *csvHandler;
public:
    ErroneousDetection(const char* fileDir);
    ~ErroneousDetection();
    void detect(void);
};

#endif // !_ERRONEOUS_DETECTION_H

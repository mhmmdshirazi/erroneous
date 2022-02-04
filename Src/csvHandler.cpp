#include "csvHandler.h"
#include <iostream>
#include <sstream>
#include <vector>

Csv::Csv(const char *fileDir)
{
    fin.open(fileDir, std::ios::in);
    // Ignore the first line
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Read a line in csv file and store it in sensorData structure
bool Csv::readCsvLine(SensorData *sensorData)
{
    std::string line, word;
    if (fin >> line)
    {
        std::vector<std::string> row;
        // change the line type to string stream in order to seperate each word using getline
        std::stringstream lineStream(line);
        // Seperate words with comma
        while (lineStream.good())
        {
            getline(lineStream, word, ',');
            row.push_back(word);
        }

        if (row.size() != 12)
        {
            std::cout << "File is corrupted";
            return false;
        }

        sensorData->ID = stoul(row[0]);
        sensorData->cowID = stoul(row[1]);
        sensorData->epoch = stod(row[2]);
        sensorData->detectionTime = stod(row[3]);
        sensorData->duration = stod(row[4]);
        sensorData->event = row[5];
        sensorData->source = row[6];
        sensorData->streamID = stoul(row[7]);
        sensorData->latency = stoi(row[8]);
        sensorData->signalStrength = stoul(row[9]);
        sensorData->cloudRecieveTime = stoul(row[10]);
        sensorData->batteryLevel = stoul(row[11]);
        return true;
    }
    else
        return false;
}

// Create a csv file in order to show the result
void Csv::createOutputFile()
{
    fout.open("Result.csv", std::ios::out);
    fout << "NodeID,gapTwo,overlapTwo,gapThree,overlapThree\n";
}

// Write a line in the csv file
void Csv::writeLine(unsigned int nodeID, double gapTwo, double overlapTwo, double gapThree, double ovelapThree)
{
    fout<<std::setfill('0')<<std::setw(8)<<nodeID<<","
        <<std::fixed<<std::setprecision(2)<<gapTwo<<","
        <<std::fixed<<std::setprecision(2)<<overlapTwo<<","
        <<std::fixed<<std::setprecision(2)<<gapThree<<","
        <<std::fixed<<std::setprecision(2)<<ovelapThree<<"\n";
}

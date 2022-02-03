#ifndef _DATA_EXTRACTOR_H
#define _DATA_EXTRACTOR_H

//Defines and Includes
#include <string>
#include <fstream>

struct StreamData {
    double epoch, lastEpoch;
    double duration, lastDuration;
};

struct NodeData {
    unsigned int ID;
    StreamData data[2];
};

struct SensorData {
    unsigned int ID, cowID, signalStrength, cloudRecieveTime, batteryLevel, streamID;
    int latency;
    double epoch, detectionTime, duration;
    std::string event, source;
};
// Public Classes 

//Handle CSV Files
class Csv {
    private:
        std::fstream fin;
    public:
        Csv(const char* fileDir);
        bool readCsvLine(SensorData* sensorData);
};

#endif // !__DATA_EXTRACTOR_H

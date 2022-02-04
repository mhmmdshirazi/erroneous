#ifndef _CSV_HANDLER_H
#define _CSV_HANDLER_H

//Defines and Includes
#include <string>
#include <fstream>

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
        std::fstream fout;
    public:
        Csv(const char* fileDir);
        bool readCsvLine(SensorData* sensorData);
        void createOutputFile();
        void writeLine(unsigned int nodeID, double gapTwo, double overlapTwo, double gapThree, double ovelapThree);
};

#endif // !_CSV_HANDLER_H

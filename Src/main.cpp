#include <iostream>
#include "dataExtractor.h"


int main(int argc, const char** argv) {
    SensorData sensor;
    if(argc == 2) {
        Csv csvHandler(argv[1]);
        csvHandler.readCsvLine(&sensor);
        std::cout<<"0 "<<sensor.ID<<std::endl;
        std::cout<<"1 "<<sensor.cowID<<std::endl;
        std::cout<<"2 "<<sensor.epoch<<std::endl;
        std::cout<<"3 "<<sensor.detectionTime<<std::endl;
        std::cout<<"4 "<<sensor.duration<<std::endl;
        std::cout<<"5 "<<sensor.event<<std::endl;
        std::cout<<"6 "<<sensor.source<<std::endl;
        std::cout<<"7 "<<sensor.streamID<<std::endl;
        std::cout<<"8 "<<sensor.latency<<std::endl;
        std::cout<<"9 "<<sensor.signalStrength<<std::endl;
        std::cout<<"10 "<<sensor.cloudRecieveTime<<std::endl;
        std::cout<<"11 "<<sensor.batteryLevel<<std::endl;
        
    } else {
        std::cout<<"invalid input";
    }
    return 0;
}

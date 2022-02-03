#include <iostream>
#include "dataExtractor.h"
#include "erroneousDetection.h"

int main(int argc, const char** argv) {
    if(argc == 2) {
        ErroneousDetection detection(argv[1]);
        detection.detect();
    } else {
        std::cout<<"invalid input";
    }
    return 0;
}

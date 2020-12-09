//
// Created by beiyu on 2020-12-09.
//

#include "daencoder.h"
#include "filecoder.h"
#include <fstream>

namespace FileCoder {

    DaEncoder::DaEncoder() : FileCoder() {

    }

    int DaEncoder::loadTextFile() {
        std::ifstream ifs;
        ifs.open(textFilename, std::ios::in);
        unitCount = fileSize(ifs);
        ifs >> textInOrder;
        ifs.close();
        return 0;
    }

//    int DaEncoder::initSize(std::ifstream &ifs) {
//        int filesize = fileSize(ifs);
//        unitCount = filesize / daUnitSize;
//        return filesize;
//        return 0;
//    }

    DaEncoder::~DaEncoder() = default;

}
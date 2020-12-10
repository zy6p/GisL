//
// Created by beiyu on 2020-12-09.
//

#include "dadecoder.h"
#include <utility>
#include <algorithm>
#include <string>
#include <fstream>
#include "daencoder.h"
#include "filecoder.h"

// Question: erase units and receive next one
    void GisL::FileCoder::eraseUnits() {
        std::vector<DaUnit>::iterator iUnit;
        for (iUnit = units.begin(); iUnit != units.end();) {
            iUnit = units.erase(iUnit);
        }
    }

namespace GisL {

    FileCoder::FileCoder() {
        this->clean();
    }

    void FileCoder::clean() {
        this->buffer = nullptr;
        this->binaryFilename.clear();
        this->textFilename.clear();
        this->textDisOrder.clear();
        this->textInOrder.clear();
        this->units.clear();
    }

    FileCoder::~FileCoder() {
        this->clean();
    }

    int FileCoder::fileSize(std::ifstream &ifs) {
        ifs.seekg(0, std::ifstream::end);
        int filesize = ifs.tellg();
        ifs.seekg(0, std::ifstream::beg);
        return filesize;
    }

}
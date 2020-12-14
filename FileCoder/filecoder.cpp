//
// Created by beiyu on 2020-12-09.
//

#include <vector>
#include <fstream>
#include "filecoder.h"

namespace GisL {

    FileCoder::FileCoder() {
        this->clear();
    }

    void FileCoder::clear() {
        this->buffer = nullptr;
        if (pUnits != nullptr) {
            delete[] pUnits;
            pUnits = nullptr;
        }
        this->binaryFilename.clear();
        this->textFilename.clear();
        this->textDisOrder.clear();
        this->textInOrder.clear();
        this->units.clear();
    }

    FileCoder::~FileCoder() {
        this->clear();
    }

    int FileCoder::fileSize(std::ifstream &ifs) {
        ifs.seekg(0, std::ifstream::end);
        int filesize = (int) ifs.tellg();
        ifs.seekg(0, std::ifstream::beg);
        return filesize;
    }

    // Question: erase units and receive next one
    void GisL::FileCoder::eraseUnits() {
        std::vector<DaUnit>::iterator iUnit;
        for (iUnit = units.begin(); iUnit != units.end();) {
            iUnit = units.erase(iUnit);
        }
    }
}
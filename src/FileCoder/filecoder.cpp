//
// Created by beiyu on 2020-12-09.
//

#include <vector>
#include <fstream>
#include "filecoder.h"

namespace GisL {

    FileCoder::FileCoder() {
        unitCount = 0;
        this->clear();
    }

    void FileCoder::clear() {
        if (buffer != nullptr) {
            buffer = nullptr;
        }
        if (pUnits != nullptr) {
            for (int i = 0; i < unitCount; ++i) {
                delete pUnits[i];
                pUnits[i] = nullptr;
            }
            delete[] pUnits;
            pUnits = nullptr;
        }
        binaryFilename.clear();
        textFilename.clear();
        textDisOrder.clear();
        textInOrder.clear();
        units.clear();
        unitCount = 0;
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

    const std::string &FileCoder::getTextInOrder() const {
        return textInOrder;
    }

    void FileCoder::setTextInOrder(const std::string& textInOrder) {
        FileCoder::textInOrder = textInOrder;
    }
}
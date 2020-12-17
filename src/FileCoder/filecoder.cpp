//
// Created by beiyu on 2020-12-09.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "filecoder.h"

namespace GisL {

    FileCoder::FileCoder() {
        unitCount = 0;
        pUnits = nullptr;
        this->clear();
    }

    /*!
     * @bug SIGTRAP (Trace/breakpoint trap) when delete the last pUnits[i]
     */
    void FileCoder::clear() {
        if (nullptr != buffer) {
            buffer = nullptr;
        }
        if (nullptr != pUnits) {
            for (int i = 0; i < unitCount; ++i) {
                if (nullptr != pUnits) {
                    try {
                        delete pUnits[i];
                        pUnits[i] = nullptr;
                    } catch (const char *e) {
                        std::cout << e;
                    }
                }
            }
            delete[] pUnits;
            pUnits = nullptr;
        }
        binaryFilename.clear();
        textFilename.clear();
        textDisOrder.clear();
        textInOrder.clear();
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

    const std::string &FileCoder::getTextInOrder() const {
        return textInOrder;
    }

    void FileCoder::setTextInOrder(const std::string &textInOrder) {
        FileCoder::textInOrder = textInOrder;
    }
}
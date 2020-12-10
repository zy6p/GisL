//
// Created by beiyu on 2020-12-09.
//

#include "daencoder.h"
#include "filecoder.h"
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <array>
#include <utility>

namespace FileCoder {

    DaEncoder::DaEncoder() : FileCoder() {

    }

    int DaEncoder::loadTextFile2Text(std::string textFilename) {
        this->textFilename = std::move(textFilename);
        std::ifstream ifs;
        ifs.open(this->textFilename, std::ios::in);
        unitCount = fileSize(ifs);
        ifs >> textInOrder;
        ifs.close();
        return 0;
    }

    std::string DaEncoder::encode() {
//        std::array<int, unitCount> p;
        int* pEncryptionIndex = encryptionIndex();
        int p[unitCount];
        int* pEncryptionIndexInOrder = encryptionIndex();
        std::sort(pEncryptionIndexInOrder, pEncryptionIndexInOrder + unitCount);
        for (int i = 0; i < unitCount; ++i) {
            DaUnit unit = DaUnit(textInOrder[i], pEncryptionIndex[i]);
            units.push_back(unit);
        }
        delete[] pEncryptionIndex;
        delete[] pEncryptionIndexInOrder;
    }

    int * DaEncoder::encryptionIndex() {
        int* pEncryptionIndex = new int[unitCount];
        std::srand((unsigned)time(nullptr));
        for (int i = 0; i < unitCount; ++i) {
            pEncryptionIndex[i] = (int)(rand() % (2000 * unitCount));
        }
        return pEncryptionIndex;
    }

    void DaEncoder::writeBinaryFile() {


    }



//    int DaEncoder::initSize(std::ifstream &ifs) {
//        int filesize = fileSize(ifs);
//        unitCount = filesize / daUnitSize;
//        return filesize;
//        return 0;
//    }

    DaEncoder::~DaEncoder() = default;

}
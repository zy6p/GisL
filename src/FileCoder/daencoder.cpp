//
// Created by beiyu on 2020-12-09.
//

#include "daencoder.h"
#include "filecoder.h"
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>

namespace GisL {

    DaEncoder::DaEncoder() : FileCoder() {

    }

    int DaEncoder::loadTextFile2Text(std::string textFilename) {
        clear();
        this->textFilename = std::move(textFilename);
        std::ifstream ifs;
        ifs.open(this->textFilename);
        unitCount = fileSize(ifs);
        char *charTextInOrder = new char[unitCount];
        ifs.read(charTextInOrder, unitCount);
        textInOrder = charTextInOrder;
        ifs.close();
        delete[] charTextInOrder;
        return 0;
    }

    void DaEncoder::encode() {
        int *pEncryptionIndexInOrder = encryptionIndexInOrder();
        for (int i = 0; i < unitCount; ++i) {
            DaUnit unit(textInOrder[i], pEncryptionIndexInOrder[i]);
            units.push_back(unit);
        }
        disOrderUnits();
        delete[] pEncryptionIndexInOrder;
    }

    int *DaEncoder::encryptionIndexInOrder() {
        std::default_random_engine e((unsigned) time(nullptr));
        std::uniform_int_distribution<> u(0, unitCount * unitCount);
        int *pEncryptionIndex = new int[unitCount];
        for (int i = 0; i < unitCount; ++i) *(pEncryptionIndex + i) = u(e);
        std::sort(pEncryptionIndex, pEncryptionIndex + unitCount - 1);
        return pEncryptionIndex;
    }

    void DaEncoder::disOrderUnits() {
        std::default_random_engine e((unsigned) time(nullptr));
        std::uniform_int_distribution<> u(0, unitCount - 1);
        for (int i = 0; i < unitCount / 2; ++i) {
            std::swap(units[i], units[u(e)]);
        }
    }

    void DaEncoder::writeBinaryFile(std::string binaryFilename) {
        this->binaryFilename = std::move(binaryFilename);
        std::ofstream ofs;
        int charSize = sizeof(char);
        int intSize = sizeof(int);
        ofs.open(this->binaryFilename, std::ios::out | std::ios::binary);
        for (int i = 0; i < unitCount; ++i) {
            ofs.write((char *) &(units[i].value), charSize);
            ofs.write((char *) &units[i].index, intSize);
        }
        ofs.close();
    }

    DaEncoder::~DaEncoder() = default;

}
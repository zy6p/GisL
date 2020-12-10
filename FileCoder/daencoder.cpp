//
// Created by beiyu on 2020-12-09.
//

#include "daencoder.h"
#include "filecoder.h"
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
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

    void DaEncoder::encode() {
        encryptionUnits();
        disOrderUnits();
    }

    void DaEncoder::encryptionUnits() {
        std::srand((unsigned) time(nullptr));
        for (int i = 0; i < unitCount; ++i) {
            int randInt = (int) rand() % 846;
            DaUnit unit(textInOrder[i], i * 846 + randInt);
            units.pop_back();
        }
    }

    void DaEncoder::disOrderUnits() {
        std::srand(unitCount);
        for (int i = 0; i < unitCount / 2; ++i) {
            int j = rand() % unitCount;
            std::swap(units[i], units[j]);
        }
    }

    void DaEncoder::writeBinaryFile(std::string binaryFilename) {
        this->binaryFilename = std::move(binaryFilename);
        std::ofstream ofs;
        ofs.open(this->binaryFilename, std::ios::out | std::ios::binary);
        for (int i = 0; i < unitCount; ++i) {
            ofs << units[i].value;
            ofs << units[i].index;
        }
        ofs.close();
    }

    DaEncoder::~DaEncoder() = default;

}
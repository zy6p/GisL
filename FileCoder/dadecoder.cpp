//
// Created by beiyu on 2020-12-06.
//

#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include "dadecoder.h"
#include "filecoder.h"

namespace GisL {

    DaDecoder::DaDecoder() : FileCoder() {}

// Question: why string can not be in construct
    DaDecoder::DaDecoder(const char *binaryFilename) {
        loadBinaryFile(binaryFilename);
    }

    void DaDecoder::loadBinaryFile(std::string binaryFilename) {
        clean();
        this->binaryFilename = std::move(binaryFilename);
        loadBinaryFile2Text();
    }

    int DaDecoder::loadBinaryFile2Text() {
        std::ifstream ifs;
        ifs.open(binaryFilename, std::ios::in | std::ios::binary);
        if (ifs.fail()) return 0;
        loadUnitInFile(ifs);
        ifs.close();
        return 0;
    }

    void DaDecoder::loadUnitInFile(std::ifstream &ifs) {
        int filesize = findFilesize(ifs);
        buffer = new char[filesize];
        ifs.read(buffer, filesize);
        int positionInFile = 0;
        for (int ii = 0; ii < unitCount; ii++) {
            DaUnit unit(*(buffer + positionInFile), *(int *) (buffer + positionInFile + 1));
            positionInFile += 5;
            units.push_back(unit);
        }
    }

    int DaDecoder::findFilesize(std::ifstream &ifs) {
        int filesize = fileSize(ifs);
        unitCount = filesize / daUnitSize;
        return filesize;
    }

    void DaDecoder::decode() {
        std::sort(units.begin(), units.end(), DaUnit::isSmaller);
        units2text();
    }

    void DaDecoder::units2text() {
        for (int ii = 0; ii < unitCount; ++ii) textInOrder.push_back(units[ii].value);
    }

    void DaDecoder::writeTextFile(std::string textFilename) {
        this->textFilename = std::move(textFilename);
        std::ofstream ofs(this->textFilename, std::ios::out);
        ofs << textInOrder;
        ofs.close();
    }

    int DaDecoder::initSize(std::ifstream &ifs) {
        int filesize = fileSize(ifs);
        unitCount = filesize / daUnitSize;
        return filesize;
        return 0;
    }

    DaDecoder::~DaDecoder() = default;

}

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
        clear();
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
        pUnits = new DaUnit*[unitCount];
        buffer = new char[filesize];
        ifs.read(buffer, filesize);
        int positionInFile = 0;
        for (int ii = 0; ii < unitCount; ii++) {
            pUnits[ii] = new DaUnit(*(buffer + positionInFile), *(int *) (buffer + positionInFile + 1));
            positionInFile += 5;
        }
        delete buffer;
    }

    int DaDecoder::findFilesize(std::ifstream &ifs) {
        int filesize = fileSize(ifs);
        unitCount = filesize / daUnitSize;
        return filesize;
    }

    void DaDecoder::decode() {
        std::sort(pUnits[0], pUnits[unitCount - 1], DaUnit::isSmaller);
        units2text();
    }

    void DaDecoder::units2text() {
//        textInOrder = new std::string[unitCount];
        for (int ii = 0; ii < unitCount; ++ii) textInOrder.push_back(pUnits[ii].value);
    }

    void DaDecoder::writeTextFile(std::string textFilename) {
        this->textFilename = std::move(textFilename);
        std::ofstream ofs(this->textFilename, std::ios::out);
        ofs.write(this->textFilename.c_str(), sizeof(this->textFilename));
//        ofs << textInOrder;
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

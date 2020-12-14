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
    DaDecoder::DaDecoder(std::string binaryFilename) {
        loadBinaryFile(std::move(binaryFilename));
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
        pUnits = new DaUnit *[unitCount];
        DaUnit *pTempUnit;
        buffer = new char[filesize];
        ifs.read(buffer, filesize);
        int positionInFile = 0;
        printf("%d\n", sizeof(pUnits));
        for (int ii = 0; ii < unitCount; ii++) {
            pTempUnit = new DaUnit(*(buffer + positionInFile), *(int *) (buffer + positionInFile + 1));
            pUnits[ii] = pTempUnit;
            printf("%p  %p\n", pTempUnit, pUnits[ii]);
            positionInFile += 5;
        }
        delete pTempUnit;
        delete buffer;
    }

    int DaDecoder::findFilesize(std::ifstream &ifs) {
        int filesize = fileSize(ifs);
        unitCount = filesize / daUnitSize;
        return filesize;
    }

    void DaDecoder::decode() {
        sortUnits();
        units2text();
    }

    // TODO
    //  need to write own sort algorithm
    //  this is wrong because of pointer array memory address discontinuity
    void DaDecoder::sortUnits() const {
        // std::vector<DaUnit> disOrderUnits (pUnits[0], pUnits[unitCount - 1]);
        std::sort(pUnits[0], pUnits[unitCount - 1], DaUnit::isSmaller);
    }

    void DaDecoder::units2text() {
        for (int ii = 0; ii < unitCount; ++ii) textInOrder.push_back(pUnits[ii]->value);
    }

    void DaDecoder::writeTextFile(std::string textFilename) {
        this->textFilename = std::move(textFilename);
        std::ofstream ofs(this->textFilename, std::ios::out);
        ofs.write(this->textFilename.c_str(), this->textFilename.size());
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

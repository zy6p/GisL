//
// Created by beiyu on 2020-12-06.
//

#include <string>
#include <fstream>
#include <algorithm>
#include <utility>
#include "dadecoder.h"
#include "dacodecvt.h"

namespace GisL {

    DaDecoder::DaDecoder() : DaCodecvt() {}

    /*!
     * @brief Construct function for DaDecoder
     * @param [in] binaryFilename
     * @bug string can not be in construct
     */
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
//        printf("%d\n", sizeof(pUnits));
        for (int ii = 0; ii < unitCount; ii++) {
            pTempUnit = new DaUnit(*(buffer + positionInFile), *(int *) (buffer + positionInFile + 1));
            pUnits[ii] = pTempUnit;
//            printf("%p  %p\n", pTempUnit, pUnits[ii]);
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

    /*!
     * @brief decode binary
     */
    void DaDecoder::decode() {
        sortUnits();
        units2text();
    }

    /*!
     *
     * @bug pointer array memory address discontinuity
     */
    void DaDecoder::sortUnits() {
//        vectorSort();
//        std::sort(pUnits, pUnits + unitCount - 1, DaUnit::isSmaller2);
        DaUnit **nn = pUnits + 1;
        DaUnit **nm = pUnits + 100;
        bool a = DaUnit::isSmaller2(*(*nn), **nm);
//        quickSort(0, unitCount - 1);
    }

    void DaDecoder::quickSort(int left, int right) {
        if (left < right) {
            int i = left, j = right;
            DaUnit *pTempUnit = pUnits[left];
            while (i < j) {
                while (i < j && DaUnit::isSmaller(*pTempUnit, *pUnits[j])) j--;
                if (i < j) pUnits[i++] = pUnits[j];
                while (i < j && DaUnit::isSmaller(*pUnits[i], *pTempUnit)) i++;
                if (i < j) pUnits[j--] = pUnits[i];
            }
            pUnits[i] = pTempUnit;
            quickSort(left, i - 1);
            quickSort(i + 1, right);
        }
    }

    void DaDecoder::vectorSort() {
        std::sort(*(pUnits), *(pUnits + unitCount - 1), DaUnit::isSmaller);
        std::vector<DaUnit> disOrderUnits;
        disOrderUnits.reserve(unitCount);
        for (int i = 0; i < unitCount; ++i) {
            disOrderUnits[i] = *pUnits[i];
        }
        std::sort(disOrderUnits.begin(), disOrderUnits.end(), DaUnit::isSmaller);
        for (int i = 0; i < unitCount; ++i) {
            *(pUnits + i) = &disOrderUnits[i];
        }
    }

    void DaDecoder::units2text() {
        for (int ii = 0; ii < unitCount; ++ii) textInOrder.push_back(pUnits[ii]->value);
    }

    void DaDecoder::writeTextFile(std::string textFilename) {
        this->textFilename = std::move(textFilename);
        std::ofstream ofs(this->textFilename, std::ios::out);
//        ofs.write(this->textInOrder.c_str(), sizeof(textInOrder.c_str()));
        ofs << textInOrder;
        ofs.close();
    }

    int DaDecoder::initSize(std::ifstream &ifs) {
        int filesize = fileSize(ifs);
        unitCount = filesize / daUnitSize;
        return filesize;
    }

    DaDecoder::~DaDecoder() = default;

}

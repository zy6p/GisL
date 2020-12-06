//
// Created by beiyu on 2020-12-06.
//

#include <string>
#include <fstream>
#include <algorithm>
#include "dadecoder.h"

DaDecoder::DaDecoder(const char filename[]) {
    this->filename = filename;
    this->buffer = nullptr;
    success = loadFile();
}

int DaDecoder::loadFile() {
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);
    if(ifs.fail()) return 0;
    loadUnitInFile(ifs);
    meaning = decode();
    ifs.close();
    return 1;
}

void DaDecoder::loadUnitInFile(std::ifstream& ifs) {
    int filesize = findFilesize(ifs);
    buffer = new char[filesize];
    ifs.read(buffer, filesize);
    int positionInFile = 0;
    for(int ii = 0; ii < unitCount; ii++){
        DaUnit unit(*(buffer + positionInFile), *(int*)(buffer + positionInFile + 1));
        positionInFile += 5;
        units.push_back(unit);
    }
}

int DaDecoder::findFilesize(std::ifstream& ifs) {
    ifs.seekg(0, ifs.end);
    int filesize = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    unitCount = filesize / daUnitSize;
    return filesize;
}

std::string DaDecoder::decode() {
    std::sort(units.begin(), units.end(), DaUnit::isSmaller);
    return textInUnits();
}

std::string DaDecoder::textInUnits() {
    for (int ii = 0; ii < unitCount; ++ii) meaning.push_back(units[ii].value);
    return meaning;
}

void DaDecoder::writeIntoFile(const std::string& outfile) {
    std::ofstream ofs(outfile);
    ofs.write(meaning.c_str(), meaning.size());
}

DaDecoder::~DaDecoder() = default;

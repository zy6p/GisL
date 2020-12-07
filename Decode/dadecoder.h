//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DADECODER_H
#define GISL_DADECODER_H
#include "daunit.h"
#include <vector>
#include <string>

class DaDecoder{
public:

    DaDecoder();

//    DaDecoder();
    explicit DaDecoder(const char *filepath);

    ~DaDecoder();
    void writeIntoFile(const std::string& outfile) const;
    void getFilename(const char *encodeFilename);

    std::string meaning;
    int success = 0;

private:
    int loadFile();
    void loadUnitInFile(std::ifstream& ifs);
    int findFilesize(std::ifstream& ifs);
    std::string decode();

    std::string filename;
    char* buffer{};
    std::vector<DaUnit> units;
    int daUnitSize = sizeof(int) + sizeof(char);
    int unitCount = 0;

    std::string textInUnits();

    void eraseUnits();
};


#endif //GISL_DADECODER_H

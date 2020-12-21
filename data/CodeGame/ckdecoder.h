#ifndef CKDECODER_H
#define CKDECODER_H

#include <string>
#include <vector>
#include "ckunit.h"

using namespace std;

class CKDecoder {
public:
    CKDecoder();

    ~CKDecoder();

    int loadFile(std::string path);

    string decode();

    int outputResult(std::string oPath);

    int find_first_char(char);

    int find_all_chars(char);

private:
    std::vector<CKUnit> units;
    char *buffer;
    string o_str;
};

#endif // CKDECODER_H

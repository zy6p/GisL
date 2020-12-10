//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DADECODER_H
#define GISL_DADECODER_H

#include "daunit.h"
#include "filecoder.h"
#include <vector>
#include <string>

namespace GisL {

    class DaDecoder : public FileCoder {
    public:
        enum CoderFuncTYPE FileCoderType = DECODE;

        DaDecoder();

        explicit DaDecoder(const char *binaryFilename);

        ~DaDecoder();

        void writeTextFile(std::string textFilename);

        void loadBinaryFile(std::string binaryFilename);

        void decode();

    private:
        int loadBinaryFile2Text();

        void loadUnitInFile(std::ifstream &ifs);

        int findFilesize(std::ifstream &ifs);


        void units2text();

        int initSize(std::ifstream &ifs);
    };

}
#endif //GISL_DADECODER_H
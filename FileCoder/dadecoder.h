//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DADECODER_H
#define GISL_DADECODER_H

#include "daunit.h"
#include "filecoder.h"
#include <vector>
#include <string>

namespace FileCoder {

    class DaDecoder : public FileCoder {
    public:
        enum FILECODERTYPE FileCoderType = DECODE;

        DaDecoder();

//    DaDecoder();
        explicit DaDecoder(const char *filepath);

        ~DaDecoder();

        void writeIntoFile(const std::string &outfile) const;

        void getFilename(const char *encodeFilename);

        std::string meaning;
        int success = 0;

    private:
        int loadFile();

        void loadUnitInFile(std::ifstream &ifs);

        int findFilesize(std::ifstream &ifs);

        std::string decode();

        std::string textInUnits();

        void eraseUnits();

        int initSize(std::ifstream &ifs);
    };

}
#endif //GISL_DADECODER_H
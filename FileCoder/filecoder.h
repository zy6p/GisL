//
// Created by beiyu on 2020-12-09.
//

#ifndef DECODE_FILECODER_H
#define DECODE_FILECODER_H

#include <vector>
#include <string>
#include "daunit.h"

namespace GisL {

    enum CoderFuncTYPE {
        ENCODE = 1, DECODE = 2
    };

    class FileCoder {
    protected:
        char *buffer{};
        std::string textDisOrder;
        std::string binaryFilename;
        std::string textFilename;
        std::vector<DaUnit> units;
        int daUnitSize = sizeof(int) + sizeof(char);
        int unitCount = 0;

        void eraseUnits();

    public:
        FileCoder();

        ~FileCoder();

        void clean();

//        virtual int initSize(std::ifstream &ifs) = 0;

        static int fileSize(std::ifstream &ifs);

        std::string textInOrder;
    };

}

#endif //DECODE_FILECODER_H

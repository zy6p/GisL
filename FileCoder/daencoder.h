//
// Created by beiyu on 2020-12-09.
//

#ifndef GISL_DAENCODER_H
#define GISL_DAENCODER_H

#include "filecoder.h"

namespace FileCoder {

    class DaEncoder : public FileCoder {
    public:
        enum FILECODERTYPE FileCoderType = ENCODE;

        DaEncoder();

        ~DaEncoder();

        int loadTextFile();

//        int initSize(std::ifstream &ifs) override;

    };

}

#endif //GISL_DAENCODER_H

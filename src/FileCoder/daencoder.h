//
// Created by beiyu on 2020-12-09.
//

#ifndef GISL_DAENCODER_H
#define GISL_DAENCODER_H

#include "filecoder.h"

namespace GisL {

    /*!
     * @brief encode text
     */
    class DaEncoder : public FileCoder {
    public:
        enum CoderFuncTYPE FileCoderType = ENCODE;

        DaEncoder();

        ~DaEncoder();

        int loadTextFile2Text(std::string textFilename);

        void encode();

        void writeBinaryFile(std::string binaryFilename);

    private:

        int *encryptionIndexInOrder();


        void disOrderUnits();
    };

}

#endif //GISL_DAENCODER_H

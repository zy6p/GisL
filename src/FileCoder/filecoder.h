//
// Created by beiyu on 2020-12-09.
//

#ifndef DECODE_FILECODER_H
#define DECODE_FILECODER_H

#include <vector>
#include <string>
#include "daunit.h"

namespace GisL {

    /*!
     * @brief file operate enum
     * @details file operate enum, 1 for ENCODE, and 2 for DECODE
     */
    enum CoderFuncTYPE {
        ENCODE = 1, DECODE = 2
    };

    /*!
     * @brief file operate
     * @details base class of DaDecoder and DaEncoder
     */
    class FileCoder {
    protected:
        char *buffer{};
        std::string textDisOrder;
        std::string binaryFilename;
        std::string textFilename;
        DaUnit **pUnits;
        int daUnitSize = sizeof(int) + sizeof(char);
        int unitCount = 0;

        static int fileSize(std::ifstream &ifs);

        std::string textInOrder;

    public:
        FileCoder();

        ~FileCoder();

        void clear();

//        virtual int initSize(std::ifstream &ifs) = 0;

        void setTextInOrder(const std::string &textInOrder);

        const std::string &getTextInOrder() const;
    };

}

#endif //DECODE_FILECODER_H

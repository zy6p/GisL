//
// Created by beiyu on 2020-12-06.
//

#ifndef GISL_DADECODER_H
#define GISL_DADECODER_H

#include "daunit.h"
#include "dacodecvt.h"
#include <vector>
#include <string>

namespace GisL {

    /*!
     * @brief decode binary file
     * @details operate binary file, decode and write text file
     */
    class DaDecoder : public DaCodecvt {
    public:
        enum DaCodecvt::CodecvtMode FileCoderType = DECODE;

        DaDecoder( );

        /*!
         * @brief Construct function for DaDecoder
         * @param [in] binaryFilename
         * @bug string can not be in construct
         */
        explicit DaDecoder( std::string binaryFilename );

        ~DaDecoder( );

        void writeTextFile( std::string textFilename );

        void loadBinaryFile( std::string binaryFilename );

        /*!
         * @brief decode binary
         */
        void decode( );

    private:
        int loadBinaryFile2Text( );

        void loadUnitInFile( std::ifstream &ifs );

        int findFilesize( std::ifstream &ifs );


        void units2text( );

        int initSize( std::ifstream &ifs );

        /*!
         *
         * @bug pointer array memory address discontinuity
         */
        void sortUnits( );

        void vectorSort( );

        void quickSort( int left, int right );
    };

}
#endif //GISL_DADECODER_H
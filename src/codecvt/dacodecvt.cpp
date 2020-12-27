//
// Created by beiyu on 2020-12-09.
//

#include <vector>
#include <fstream>
#include <iostream>
#include "dacodecvt.h"

namespace GisL {

    DaCodecvt::DaCodecvt( ) {
        unitCount = 0;
        pUnits = nullptr;
        this->clear();
    }

    void DaCodecvt::clear( ) {
        if ( nullptr != buffer ) {
            buffer = nullptr;
        }
        if ( nullptr != pUnits ) {
            for ( int i = 0; i < unitCount; ++i ) {
                if ( nullptr != pUnits ) {
                    try {
                        delete pUnits[i];
                        pUnits[i] = nullptr;
                    } catch ( const char *e ) {
                        std::cout << e;
                    }
                }
            }
            delete[] pUnits;
            pUnits = nullptr;
        }
        binaryFilename.clear();
        textFilename.clear();
        textDisOrder.clear();
        textInOrder.clear();
        unitCount = 0;
    }

    DaCodecvt::~DaCodecvt( ) {
        this->clear();
    }

    int DaCodecvt::fileSize( std::ifstream &ifs ) {
        ifs.seekg( 0, std::ifstream::end );
        int filesize = ( int ) ifs.tellg();
        ifs.seekg( 0, std::ifstream::beg );
        return filesize;
    }

    const std::string &DaCodecvt::getTextInOrder( ) const {
        return textInOrder;
    }

    void DaCodecvt::setTextInOrder( const std::string &textInOrder ) {
        DaCodecvt::textInOrder = textInOrder;
    }
}
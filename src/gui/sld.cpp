//
// Created by omega on 14/12/2020.
//

#include "sld.h"

#include <string>
#include <random>

#include "../utils/stringoperate.h"
#include "../utils/merror.h"

namespace GisL {

    Sld::Symbol::Symbol( bool rand ) {
        std::default_random_engine e(( unsigned ) time( nullptr ));
        std::uniform_int_distribution<> u( 0, 255 );
        this->polygonFill = true;
        this->polygonFillColor = QColor( u( e ), u( e ), u( e ));
        this->polygonStroke = true;
        this->polygonStrokeColor = QColor( u( e ), u( e ), u( e ));
        this->polygonStrokeWidth = 1;
        this->polygonStrokeLinejoin = "bevel";
    }

    Sld::Sld( ) : Xml(), GisLObject() {

    }

    Sld::Sld( const std::string &theSldFilename ) : Xml( theSldFilename ), GisLObject() {

    }

    void Sld::loadSldFile( const std::string &theSldFilename ) {
        Xml::loadXmlFile( theSldFilename );
    }

}
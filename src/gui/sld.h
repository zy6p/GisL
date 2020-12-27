//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <map>
#include <string>
#include <QColor>

#include "../utils/gislobject.h"
#include "../utils/xml.h"

namespace GisL {

    /*!
     * Styled Layer Descriptor
     */
    class Sld : public Xml {
    public:
        class Symbol {
        public:
            bool polygonFill;
            QColor polygonFillColor;

            bool polygonStroke;
            QColor polygonStrokeColor;
            float polygonStrokeWidth;
            std::string polygonStrokeLinejoin;

            explicit Symbol( bool rand = true );
        };

    public:
        Sld( );

        explicit Sld( const std::string &theSldFilename );

        void loadSldFile( const std::string &theSldFilename );

        ~Sld( );


    private:

        void readSld( QFile &qFile );

        std::string propertyName;
        std::map<std::string, Symbol *> symbolMap;

    };

}

#endif //GISL_SLD_H

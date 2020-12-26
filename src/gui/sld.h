//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <string>
#include <QColor>

#include "../utils/gislobject.h"
#include "../utils/xml.h"

namespace GisL {

    /*!
     * Styled Layer Descriptor
     */
    class Sld : public Xml, public GisLObject {
    public:
        class Symbol {
        public:
            bool polygonFill;
            QColor polygonFillColor;

            bool polygonStroke;
            QColor polygonStrokeColor;
            int polygonStrokeWidth;
            std::string polygonStrokeLinejoin;

            explicit Symbol( bool rand = true );
        };


//    protected:
//        friend class SldDoc;
//        friend class SldHead;
//        friend class SldAttribute;
//        friend class SldElement;
//        friend class Xml::XmlDoc;

    public:
        Sld( );

        explicit Sld( const std::string &theSldFilename );

        void loadSldFile( const std::string &theSldFilename );


    private:


    };

}

#endif //GISL_SLD_H

/*!
 * @author tau 
 * @date 12/28/20
*/

#include <iostream>
#include "textsymbolizer.h"

namespace GisL {
    void TextSymbolizer::rand( ) {
        propertyName = "fid";

        fontFamily = "Times New Roman";
        fontSize = 13;

        anchorPointX = 0;
        anchorPointY = 0;

        fillColor.setNamedColor( "#000000" );

        maxDisplacement = 1;
    }

    void TextSymbolizer::init( QXmlStreamReader &sldStream ) {
        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        propertyName = sldStream.readElementText().toStdString();

        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNextStartElement();
        fontFamily = sldStream.readElementText().toStdString();
        sldStream.readNextStartElement();
        fontSize = sldStream.readElementText().toInt();


        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        anchorPointX = sldStream.readElementText().toFloat();
        sldStream.readNextStartElement();
        anchorPointY = sldStream.readElementText().toFloat();

//        GisLObject::mErrorMessage;
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNextStartElement();
        fillColor.setNamedColor( sldStream.readElementText());

        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        sldStream.readNext();
        maxDisplacement = sldStream.readElementText().toFloat();

    }
}
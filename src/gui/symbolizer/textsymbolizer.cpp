/*!
 * @author tau 
 * @date 12/28/20
*/

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

        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        fontFamily = sldStream.readElementText().toStdString();
        sldStream.readNextStartElement();
        fontSize = sldStream.readElementText().toInt();

        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        anchorPointX = sldStream.readElementText().toFloat();
        sldStream.readNextStartElement();
        anchorPointY = sldStream.readElementText().toFloat();

        sldStream.readNextStartElement();
        sldStream.readNextStartElement();
        fillColor.setNamedColor( sldStream.readElementText());

        sldStream.readNextStartElement();
        maxDisplacement = sldStream.readElementText().toFloat();

    }
}
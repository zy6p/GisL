#include "ckpolygonsymbolizer.h"
#include <QDebug>

CKPolygonSymbolizer::CKPolygonSymbolizer( ) {

}

CKPolygonSymbolizer::CKPolygonSymbolizer( QXmlStreamReader &sld ) {
    QXmlStreamReader::TokenType token;
    while ( !sld.atEnd()) {
        token = sld.readNext();

        switch ( token ) {
            case QXmlStreamReader::StartElement:
                if ( sld.name() == "Fill" ) {
                    sld.readNextStartElement();
                    fill_color.setNamedColor( sld.readElementText());
                    break;
                }
                if ( sld.name() == "Stroke" ) {
                    sld.readNextStartElement();
                    stroke_color.setNamedColor( sld.readElementText());
                    sld.readNextStartElement();
                    stroke_width = sld.readElementText().toFloat();
                    sld.readNextStartElement();
                    stroke_join = sld.readElementText();
                    break;
                }
                break;
            case QXmlStreamReader::EndElement:
                if ( sld.name() == "PolygonSymbolizer" )
                    return;
                break;
            default:
                break;
        }
    }
}

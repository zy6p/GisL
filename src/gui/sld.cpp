//
// Created by omega on 14/12/2020.
//

#include "sld.h"

#include <string>
#include <random>
#include <QXmlStreamReader>

#include "../utils/stringoperate.h"
#include "../utils/ptroperate.h"

namespace GisL {

    Sld::Symbol::Symbol( bool rand ) {
        std::default_random_engine e(( unsigned ) time( nullptr ));
        std::uniform_int_distribution<> u( 0, 255 );
        this->polygonFill = true;
        this->polygonFillColor = QColor( u( e ), u( e ), u( e ));
        this->polygonStroke = true;
        this->polygonStrokeColor = QColor( u( e ), u( e ), u( e ));
        this->polygonStrokeWidth = 1.0;
        this->polygonStrokeLinejoin = "bevel";
    }

    Sld::Sld( ) : Xml() {

    }

    Sld::Sld( const std::string &theSldFilename ) : Xml( theSldFilename ) {

    }

    void Sld::loadSldFile( const std::string &theSldFilename ) {
        Xml::loadXmlFile( theSldFilename );

        if ( !StringOperate::isEndWith( theSldFilename, ".sld" )) {
            mError = MError::GisLError::ErrXml;
            mErrorMessage += "wrong filename\n";
            return;
        }

        QFile qFile;
//        QFile XmlFile(QString::fromStdString(theXmlFilename));
        if ( !qFile.open( QFile::ReadOnly | QFile::Text )) {
            mError = MError::GisLError::ErrXml;
            mErrorMessage.append( "Wrong! cannot open this file\n" );
            return;
        }

        readSld( qFile );

        qFile.close();
    }

    void Sld::readSld( QFile &qFile ) {
        QXmlStreamReader sldStream( &qFile );
        Symbol *pSymbol;
        std::string sldName;
        while ( !sldStream.atEnd()) {
            QXmlStreamReader::TokenType token = sldStream.readNext();

            switch ( token ) {
                case QXmlStreamReader::NoToken: {
                    break;
                }
                case QXmlStreamReader::Invalid: {
                    mError = MError::GisLError::ErrXml;
                    mErrorMessage = sldStream.errorString().toStdString();
                    return;
                }
                case QXmlStreamReader::StartElement: {
                    if ( sldStream.name() == "PropertyName" ) {
                        propertyName = sldStream.readElementText().toStdString();
                        pSymbol = new Symbol;
                        symbolMap[sldName] = pSymbol;
                    }

                    if ( sldStream.name() == "Literal" ) {
                        sldName = sldStream.readElementText().toStdString();
                    }

                    if ( sldStream.name() == "Fill" ) {
                        pSymbol->polygonFill = true;
                        sldStream.readNextStartElement();
                        pSymbol->polygonFillColor.setNamedColor( sldStream.readElementText());
                    }

                    if ( sldStream.name() == "Stroke" ) {
                        pSymbol->polygonStroke = true;
                        sldStream.readNextStartElement();
                        pSymbol->polygonStrokeColor.setNamedColor( sldStream.readElementText());
                        sldStream.readNextStartElement();
                        pSymbol->polygonStrokeWidth = sldStream.readElementText().toFloat();
                        sldStream.readNextStartElement();
                        pSymbol->polygonStrokeLinejoin = sldStream.readElementText().toStdString();
                    }
                    break;
                }

            }
        }
    }

    Sld::~Sld( ) {
        for ( const auto &p : symbolMap ) {
            PtrOperate::clear( p.second );
        }
    }

}
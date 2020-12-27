/*!
 * @file xml.cpp
 * @author omega 
 * @date 23/12/2020
 * 
 * @brief xml lib
 * @details 
 *
 *
 */

#include "xml.h"

#include <istream>
#include <fstream>
#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include "ptroperate.h"
#include "stringoperate.h"


namespace GisL {

    Xml::XmlAttribute::XmlAttribute( std::string name, std::string value ) : name( name ), value( value ) {}

    Xml::XmlHead::XmlHead( std::string version, std::string encoding, std::string standalone ) {
        head = new XmlAttribute( *( std::string * ) ( "version" ), version );
        head->next = new XmlAttribute( *( std::string * ) ( "encoding" ), encoding );
        if ( !standalone.empty()) {
            head->next->next = new XmlAttribute( *( std::string * ) ( "standalone" ), standalone );
        }
    }

    Xml::XmlHead::~XmlHead( ) {
        delete head->next->next;
        head->next->next = nullptr;
        delete head->next;
        head->next = nullptr;
        delete head;
        head = nullptr;
    }

    Xml::XmlDoc::XmlDoc( ) {
        pXmlHead = new XmlHead();
    }

    Xml::XmlDoc::~XmlDoc( ) {

    }


    Xml::Xml( ) = default;

    Xml::Xml( const std::string &theXmlFilename ) {
        filename = theXmlFilename;
        loadXmlFile( filename );
    }

    void Xml::loadXmlFile( const std::string &theXmlFilename ) {

        if ( !StringOperate::isEndWith<std::string>( theXmlFilename, ".xml", ".sld" )) {
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

        QXmlStreamReader qXmlStreamReader( &qFile );
        pXmlDoc = new XmlDoc;

        while ( !qXmlStreamReader.atEnd()) {
            QXmlStreamReader::TokenType type = qXmlStreamReader.readNext();

            if ( type == QXmlStreamReader::StartDocument ) {
                pXmlDoc->pXmlHead = new XmlHead( qXmlStreamReader.documentVersion().toString().toStdString(),
                                                 qXmlStreamReader.documentEncoding().toString().toStdString());
            }

            if ( type == QXmlStreamReader::StartElement ) {
                pXmlDoc->pElement->tag = qXmlStreamReader.name().toString().toStdString();
                auto attribute = qXmlStreamReader.attributes().begin();
                XmlAttribute *currentAttribute = pXmlDoc->pElement->pAttribute;

                currentAttribute = new XmlAttribute( attribute->name().toString().toStdString(),
                                                     attribute->value().toString().toStdString());
                currentAttribute = currentAttribute->next;
            }

        }


        qFile.close();


    }

    Xml::~Xml( ) {
        PtrOperate::clear( pXmlDoc );

    }

    bool Xml::hasError( ) {
        return ( mError == MError::GisLError::NoError );
    }

    std::string Xml::errorMessage( ) {
        return mErrorMessage;
    }


}

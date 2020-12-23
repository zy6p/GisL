/*!
 * @file xml.cpp.cc
 * @author omega 
 * @date 23/12/2020
 * 
 * @brief xml lib
 * @details 
 * @verbatim
 *
 */

#include "xml.h"

#include <istream>
#include <fstream>
//#include <>
#include <qt5/QtCore/QFile>
#include <qt5/QtCore/QString>
#include <qt5/QtCore/QXmlStreamReader>
#include <qt5/QtCore/QXmlStreamWriter>

#include "stringoperate.h"

namespace GisL {

    Xml::XmlDoc::XmlDoc( ) {

    }

    Xml::XmlDoc::~XmlDoc( ) {

    }

    Xml::XmlHead::~XmlHead( ) {
        delete head->next->next;
        head->next->next = nullptr;
        delete head->next;
        head->next = nullptr;
        delete head;
        head = nullptr;
    }

    Xml::XmlHead::XmlHead( std::string version, std::string encoding, std::string standalone ) {
        head = new XmlAttribute(*(std::string *)("version"), version);
        head->next = new XmlAttribute(*(std::string *)("encoding"), encoding);
        if ( !standalone.empty() ) {
            head->next->next = new XmlAttribute(*(std::string *)("standalone"), standalone);
        }
    }

    Xml::XmlAttribute::XmlAttribute( std::string &name, std::string &value ) : name(name), value(value) {}

    Xml::Xml() = default;

    Xml::Xml(const std::string &theXmlFilename) {
        loadXmlFile( theXmlFilename );
    }

    void Xml::loadXmlFile(const std::string &theXmlFilename) {
        if ( theXmlFilename.length() <= 4 ) {
            mError = MError::GisLError::ErrInFileName;
            mErrorMessage += "empty file name\n";
        }

        if ( StringOperate::isEndWith( theXmlFilename, ".Xml" )) {
            mError = MError::GisLError::ErrInFileName;
            mErrorMessage += "wrong filename\n";
        }

        QFile XmlFile;
//        QFile XmlFile(QString::fromStdString(theXmlFilename));
        if ( !XmlFile.open(QFile::ReadOnly | QFile::Text) ) {
            mError = MError::GisLError::ErrCreateDataSource;
            mErrorMessage.append("Wrong! cannot open this file\n");
            return;
        }

        QXmlStreamReader xmlStreamReader(&XmlFile);
//        xmlStreamReader.
        pXmlDoc = new XmlDoc;


        XmlFile.close();



    }

    Xml::~Xml( ) {

    }

    bool Xml::hasError( ) {
        return (mError == MError::GisLError::NoError);
    }

    std::string Xml::errorMessage( ) {
        return mErrorMessage;
    }


}

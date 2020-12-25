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

#include "stringoperate.h"


namespace GisL {

    Xml::XmlAttribute::XmlAttribute(std::string &name, std::string &value) : name(name), value(value) {}

    Xml::XmlHead::XmlHead(std::string version, std::string encoding, std::string standalone) {
        head = new XmlAttribute(*(std::string *) ("version"), version);
        head->next = new XmlAttribute(*(std::string *) ("encoding"), encoding);
        if (!standalone.empty()) {
            head->next->next = new XmlAttribute(*(std::string *) ("standalone"), standalone);
        }
    }

    Xml::XmlHead::~XmlHead() {
        delete head->next->next;
        head->next->next = nullptr;
        delete head->next;
        head->next = nullptr;
        delete head;
        head = nullptr;
    }

    Xml::XmlDoc::XmlDoc() {
        pXmlHead = new XmlHead();
    }

    Xml::XmlDoc::~XmlDoc() {

    }


    Xml::Xml() = default;

    Xml::Xml(const std::string &theXmlFilename) {
        filename = theXmlFilename;
        loadXmlFile(filename);
    }

    void Xml::loadXmlFile(const std::string &theXmlFilename) {

        if (!StringOperate::isEndWith(theXmlFilename.c_str(), ".xml")
         || !StringOperate::isEndWith(theXmlFilename.c_str(), ".sld")
            ) {
            mError = MError::GisLError::ErrXml;
            mErrorMessage += "wrong filename\n";
            return;
        }

        QFile XmlFile;
//        QFile XmlFile(QString::fromStdString(theXmlFilename));
        if (!XmlFile.open(QFile::ReadOnly | QFile::Text)) {
            mError = MError::GisLError::ErrXml;
            mErrorMessage.append("Wrong! cannot open this file\n");
            return;
        }

        QXmlStreamReader xmlStreamReader(&XmlFile);
//        xmlStreamReader.
        pXmlDoc = new XmlDoc;


        XmlFile.close();


    }

    Xml::~Xml() {
        if ( nullptr != pXmlDoc ) {
            delete pXmlDoc;
            pXmlDoc = nullptr;
        }

    }

    bool Xml::hasError() {
        return (mError == MError::GisLError::NoError);
    }

    std::string Xml::errorMessage() {
        return mErrorMessage;
    }


}

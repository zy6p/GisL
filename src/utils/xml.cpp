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

#include <QFile>
#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <fstream>
#include <istream>
#include <utility>

#include "ptroperate.h"
#include "stringoperate.h"

namespace gisl {

Xml::XmlHead::XmlHead(
    const std::string& version,
    const std::string& encoding,
    const std::string& standalone) {
  head["version"] = version;
  head["encoding"] = encoding;
  if (!standalone.empty()) {
    head["standalone"] = standalone;
  }
}

Xml::XmlHead::~XmlHead() = default;

Xml::XmlDoc::XmlDoc() {
  pXmlHead = nullptr;
  pElement = nullptr;
}

Xml::XmlDoc::~XmlDoc() {
  PtrOperate::clear(pElement);
  PtrOperate::clear(pXmlHead);
}

Xml::Xml() { pXmlDoc = nullptr; };

Xml::Xml(const std::string& theXmlFilename) {
  pXmlDoc = nullptr;
  filename = theXmlFilename;
}

void Xml::loadXmlFile(const std::string& theXmlFilename) {
  if (!StringOperate::isEndWith<std::string>(theXmlFilename, ".xml", ".sld")) {
    //            mError = MError::GisLError::ErrXml;
    mErrorMessage += "wrong filename\n";
  }

  QFile qFile(QString::fromStdString(theXmlFilename));
  if (!qFile.open(QFile::ReadOnly | QFile::Text)) {
    //            mError = MError::GisLError::ErrXml;
    mErrorMessage.append("Wrong! cannot open this file\n");
  }

  readXml(qFile);
  qFile.close();
}

void Xml::readXml(QFile& qFile) {
  QXmlStreamReader xmlStream(&qFile);
  pXmlDoc = new XmlDoc;
  XmlElement* pCurrentElement = pXmlDoc->pElement;
  XmlElement* pPreviousElement;

  while (!xmlStream.atEnd()) {
    QXmlStreamReader::TokenType token = xmlStream.readNext();

    switch (token) {
    case QXmlStreamReader::NoToken: {
      break;
    }
    case QXmlStreamReader::Invalid: {
      //                    mError = MError::GisLError::ErrXml;
      mErrorMessage = xmlStream.errorString().toStdString();
      return;
    }
    case QXmlStreamReader::StartDocument: {
      pXmlDoc->pXmlHead = new XmlHead(
          xmlStream.documentVersion().toString().toStdString(),
          xmlStream.documentEncoding().toString().toStdString());
      break;
    }
    case QXmlStreamReader::StartElement: {
      pCurrentElement = new XmlElement;
      pCurrentElement->tag = xmlStream.name().toString().toStdString();
      for (int i = 0; i < xmlStream.attributes().count(); ++i) {
        pCurrentElement->attribute
            [xmlStream.attributes().at(i).name().toString().toStdString()] =
            xmlStream.attributes().at(i).value().toString().toStdString();
      }
      pCurrentElement->text = xmlStream.text().toString().toStdString();
      pPreviousElement = pCurrentElement;
      pCurrentElement = pPreviousElement->next;
      break;
    }
    case QXmlStreamReader::EndElement: {
      pCurrentElement = nullptr;
      break;
    }
    case QXmlStreamReader::EndDocument: {
      break;
    }

    case QXmlStreamReader::Characters:
      break;
    case QXmlStreamReader::Comment:
      break;
    case QXmlStreamReader::DTD:
      break;
    case QXmlStreamReader::EntityReference:
      break;
    case QXmlStreamReader::ProcessingInstruction:
      break;
    }
  }
}

Xml::~Xml() { PtrOperate::clear(pXmlDoc); }

} // namespace gisl

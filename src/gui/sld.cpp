//
// Created by omega on 14/12/2020.
//

#include "sld.h"

#include <QXmlStreamReader>
#include <random>
#include <string>

#include "../core/layertree.h"
#include "../utils/ptroperate.h"
#include "../utils/stringoperate.h"
#include "src/gui/symbolizer/abstractsymbolizer.h"
#include "symbolizer/polygonsymbolizer.h"
#include "symbolizer/textsymbolizer.h"

namespace gisl {

Sld::Sld() : Xml() {}

Sld::Sld(const std::string &theSldFilename) : Xml(theSldFilename) {
  loadSldFile(theSldFilename);
}

void Sld::loadSldFile(const std::string &theSldFilename) {

  if (!StringOperate::isEndWith<std::string>(theSldFilename, ".xml", ".sld")) {
    //            mError = MError::GisLError::ErrXml;
    mErrorMessage += "wrong filename\n";
  }

  QFile qFile(QString::fromStdString(theSldFilename));
  if (!qFile.open(QFile::ReadOnly | QFile::Text)) {
    //            mError = MError::GisLError::ErrXml;
    mErrorMessage.append("Wrong! cannot open this file\n");
  }

  readSld(qFile);

  qFile.close();
}

void Sld::readSld(QFile &qFile) {
  QXmlStreamReader sldStream(&qFile);
  AbstractSymbolizer *pSymbolizer;
  std::string featureName;
  while (!sldStream.atEnd()) {
    QXmlStreamReader::TokenType token = sldStream.readNext();

    switch (token) {
    case QXmlStreamReader::NoToken: {
      break;
    }
    case QXmlStreamReader::Invalid: {
      //                    mError = MError::GisLError::ErrXml;
      mErrorMessage = sldStream.errorString().toStdString();
      return;
    }
    case QXmlStreamReader::StartElement: {

      if (sldStream.name() == "Literal") {
        featureName = sldStream.readElementText().toStdString();
      }

      if (sldStream.name() == "PropertyName") {
        propertyName = sldStream.readElementText().toStdString();
      }

      if (sldStream.name() == "PolygonSymbolizer") {
        pSymbolizer = new PolygonSymbolizer;
        pSymbolizer->init(sldStream);
        symbolizerMap[featureName] = pSymbolizer;
      }

      if (sldStream.name() == "TextSymbolizer") {
        pSymbolizer = new TextSymbolizer;
        pSymbolizer->init(sldStream);
        symbolizerMap[featureName] = pSymbolizer;
      }

      break;
    }
    }
  }
}

AbstractSymbolizer *Sld::operator[](const std::string &Literal) {
  return symbolizerMap[Literal];
}

//    std::_Rb_tree_iterator<std::pair<const std::string, AbstractSymbolizer *>>
//    Sld::begin( ) {
//        return symbolizerMap.begin();
//    }
//
//    std::_Rb_tree_iterator<std::pair<const std::string, AbstractSymbolizer *>>
//    Sld::end( ) {
//        return symbolizerMap.end();
//    }

Sld::~Sld() {
  for (const auto &p : symbolizerMap) {
    PtrOperate::clear(p.second);
  }
}

const SymMap &Sld::getSymbolizerMap() const { return symbolizerMap; }

const std::string &Sld::getPropertyName() const { return propertyName; }

void Sld::rand(const std::string &layerName) {
  auto *layerTree = gisl::LayerTree::getLayerTree();
  auto *layer = layerTree->getLayer(layerName);
  // todo set rand style
  //        for ( auto feature : layer. ) {
  //
  //        }
}

} // namespace gisl
//
// Created by km on 6/14/21.
//

#include "georeference.h"
void gisl::GeoReference::execAlg() {
  AnalysisAlg::execAlg();
  qDebug("execAlg: %s", this->_algName.c_str());
}
void gisl::GeoReference::reverse() {}
const std::string& gisl::GeoReference::output() { return this->_errorMessage; }
void gisl::GeoReference::execute(QWidget* parent) {
  this->_algName = tr("GeoReference").toStdString();
  AnalysisAlg::execute(parent);
}
gisl::GeoReference::~GeoReference() {}
void gisl::GeoReference::initGui() {
  AnalysisAlg::initGui();
  qDebug("initGui: %s", this->_algName.c_str());

}

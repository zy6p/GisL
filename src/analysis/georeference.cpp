//
// Created by km on 6/14/21.
//

#include "georeference.h"

#include <absl/strings/str_cat.h>
#include <filesystem>

#include "analysisgui.h"
#include "core/layer/layertree.h"

void gisl::GeoReference::reverse() {}
const std::string& gisl::GeoReference::output() {
    return this->_errorMessage;
}
void gisl::GeoReference::execute(QWidget* parent) {
    this->_algName = tr("GeoReference").toStdString();
    AnalysisAlg::execute(parent);
}
gisl::GeoReference::~GeoReference() {
    delete this->pProviderBox1;
    this->pProviderBox1 = nullptr;
    delete this->pProviderBox2;
    this->pProviderBox2 = nullptr;
};
void gisl::GeoReference::initGui() {
    AnalysisAlg::initGui();
    qDebug("initGui: %s", this->_algName.c_str());
    const auto* layerTree = LayerTree::getLayerTree();
    QStringList providerNameList;
    for (auto [fid, pProvider] : layerTree->getProviderMap()) {
        std::string s = std::filesystem::path(pProvider->getFileName()).filename();
        providerNameList << QString::fromStdString(
                             absl::StrCat(std::to_string(fid), ": ", s.substr(0, s.size() - 4)));
    }
    this->pProviderBox1 = new QComboBox{};
    this->pProviderBox2 = new QComboBox{};
    this->pProviderBox1->addItems(providerNameList);
    this->pProviderBox2->addItems(providerNameList);
    this->gui->addItemToUi(tr("need to be corrected"), this->pProviderBox1);
    this->gui->addItemToUi(tr("correct layer"), this->pProviderBox2);
}
void gisl::GeoReference::execAlg() {
    qDebug("execAlg: %s", this->_algName.c_str());
}

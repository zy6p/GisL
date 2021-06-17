//
// Created by km on 6/14/21.
//

#include "georeference.h"

#include <Eigen/Dense>
#include <absl/strings/str_cat.h>
#include <filesystem>
#include <fstream>

#include "analysisgui.h"
#include "core/layer/layertree.h"
#include "core/provider/rasterprovider.h"
#include "gisl_config.h"

void gisl::Trans2D::loadPosData(
    std::string_view sv,
    Eigen::MatrixXf& inPos,
    Eigen::MatrixXf& refPos) {
  std::ifstream ifs;
  ifs.open(sv.data(), std::ios::in);
  if (ifs.fail())
    return;
  ifs.seekg(0, std::ifstream::end);
  int fileSize = (int)ifs.tellg();
  auto buffer = (char*)malloc(fileSize);
  ifs.seekg(0, std::ifstream::beg);
  ifs.read(buffer, fileSize);
  int selCount = 0;
  std::string val;
  std::vector<float> inValues;
  std::vector<float> refValues;
  for (int i = 0; i < fileSize; ++i) {
    if (buffer[i] == ',') {
      if (selCount < 2) {
        inValues.emplace_back(std::stof(val));
        qDebug("inPos ( %d): %s", selCount, val.c_str());
      } else {
        refValues.emplace_back(std::stof(val));
        qDebug("refPos ( %d): %s", selCount, val.c_str());
      }
      val = "";
      selCount++;
      continue;
    }
    if (buffer[i] == '\\') {
      refValues.emplace_back(std::stof(val));
      qDebug("refPos ( %d): %s", selCount, val.c_str());
      i += 3;
      continue;
    }
    val += buffer[i];
  }
  inPos =
      Eigen::Map<Eigen::MatrixXf>(inValues.data(), 1, (int)inValues.size() / 2);
  refPos = Eigen::Map<Eigen::MatrixXf>(
      refValues.data(),
      1,
      (int)refValues.size() / 2);
  free(buffer);
}
void gisl::Trans2D::adjust(
    Eigen::MatrixXf& inPos,
    Eigen::MatrixXf& refPos,
    Eigen::MatrixXf& trans) {}

void gisl::GeoReference::reverse() {}
const std::string& gisl::GeoReference::output() { return this->_errorMessage; }
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
  this->pPosLineEdit = new QLineEdit{};
  this->pPosLineEdit->setText(QString::fromStdString(STRINGIFY(TEST_DATA_DIR)));
  this->gui->addItemToUi(tr("points data"), this->pPosLineEdit);
}
void gisl::GeoReference::execAlg() {
  qDebug("execAlg: %s", this->_algName.c_str());
  const auto* layerTree = LayerTree::getLayerTree();
  RasterProvider* inputProvider =
      std::get<RasterProvider*>(layerTree->getProviderClassifyMap().at(
          this->pProviderBox1->currentText().toInt()));
  RasterProvider* refRasterProvider =
      std::get<RasterProvider*>(layerTree->getProviderClassifyMap().at(
          this->pProviderBox2->currentText().toInt()));
  std::string thePosFileName = this->pPosLineEdit->text().toStdString();
  this->realAlg(inputProvider, refRasterProvider, thePosFileName);
}
void gisl::GeoReference::realAlg(
    RasterProvider* input,
    RasterProvider* ref,
    std::string_view posFileName) {
  Eigen::MatrixXf inPos;
  Eigen::MatrixXf refPos;
  Trans2D::loadPosData(posFileName, inPos, refPos);
  Eigen::MatrixXf trans;
  Trans2D::adjust(inPos, refPos, trans);
}

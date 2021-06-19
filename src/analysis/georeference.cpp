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

void gisl::Trans2D::loadPosData(std::string_view sv) {
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
    if (buffer[i] == '\r') {
      refValues.emplace_back(std::stof(val));
      qDebug("refPos ( %d): %s", selCount, val.c_str());
      i += 1;
      selCount = 0;
      continue;
    }
    val += buffer[i];
  }
  inPos = Eigen::Map<Eigen::MatrixXf>(
      inValues.data(),
      (int)inValues.size() / 2 - 1,
      2);
  refPos = Eigen::Map<Eigen::MatrixXf>(
      refValues.data(),
      (int)refValues.size() / 2 - 1,
      2);
  accuracyPos << inValues[inValues.size() - 2], inValues[inValues.size() - 1],
      refValues[refValues.size() - 2], refValues[refValues.size() - 1];
  free(buffer);
}
void gisl::Trans2D::adjust() {
  adjust_A.resize(inPos.rows(), 6);
  adjust_A.col(0) = Eigen::MatrixXf::Constant(inPos.rows(), 1, 1);
  adjust_A.col(1) = refPos.col(0);
  adjust_A.col(2) = refPos.col(1);
  adjust_A.col(3) = refPos.col(0).array().square();
  adjust_A.col(4) = refPos.col(0).array() * refPos.col(1).array();
  adjust_A.col(5) = refPos.col(1).array().square();
  //  adjust_A << Eigen::MatrixXf::Constant(inPos.rows(), 1, 1), refPos.col(0),
  //  refPos.col(1), refPos.col(0).array().square(), refPos.col(0).array() *
  //  refPos.col(1).array(), refPos.col(1).array().square();
  trans = (adjust_A.transpose() * adjust_A).inverse() * adjust_A.transpose() *
          inPos;
}
void gisl::Trans2D::transRectangle(
    const gisl::Rectangle& in,
    gisl::Rectangle& out) {
  auto [xOut1, yOut1] = this->transPoint(in.minX, in.minY);
  auto [xOut2, yOut2] = this->transPoint(in.maxX, in.minY);
  auto [xOut3, yOut3] = this->transPoint(in.minX, in.maxY);
  auto [xOut4, yOut4] = this->transPoint(in.maxX, in.maxY);
  out.minX = std::min(std::min(std::min(xOut1, xOut2), xOut3), xOut4);
  out.minY = std::min(std::min(std::min(yOut1, yOut2), yOut3), yOut4);
  out.maxX = std::max(std::max(std::max(xOut1, xOut2), xOut3), xOut4);
  out.maxY = std::max(std::max(std::max(yOut1, yOut2), yOut3), yOut4);
}
std::pair<float, float> gisl::Trans2D::transPoint(float x, float y) {
  float xOut = this->trans(0, 0) + this->trans(1, 0) * x +
               this->trans(2, 0) * y + this->trans(3, 0) * x * x +
               this->trans(4, 0) * x * y + this->trans(5, 0) * y * y;
  float yOut = this->trans(0, 1) + this->trans(1, 1) * x +
               this->trans(2, 1) * y + this->trans(3, 1) * x * x +
               this->trans(4, 1) * x * y + this->trans(5, 1) * y * y;
  return std::pair<float, float>(xOut, yOut);
}

void gisl::GeoReference::reverse() {}
const std::string& gisl::GeoReference::output() { return this->_errorMessage; }
void gisl::GeoReference::execute(QWidget* parent) {
  this->_algName = tr("GeoReference").toStdString();
  AnalysisAlg::execute(parent);
}
gisl::GeoReference::~GeoReference() {
  delete this->pPosLineEdit;
  this->pPosLineEdit = nullptr;
  delete this->pProviderBox;
  this->pProviderBox = nullptr;
}
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
  this->pProviderBox = new QComboBox{};
  this->pProviderBox->addItems(providerNameList);
  this->gui->addItemToUi(tr("need to be corrected"), this->pProviderBox);
  this->pPosLineEdit = new QLineEdit{};
  this->pPosLineEdit->setText(QString::fromStdString(STRINGIFY(TEST_DATA_DIR)));
  this->gui->addItemToUi(tr("points data"), this->pPosLineEdit);
}
void gisl::GeoReference::execAlg() {
  qDebug("execAlg: %s", this->_algName.c_str());
  const auto* layerTree = LayerTree::getLayerTree();
  auto inputProvider =
      std::get<RasterProvider*>(layerTree->getProviderClassifyMap().at(
          this->pProviderBox->currentText().toInt()));
  std::string thePosFileName = this->pPosLineEdit->text().toStdString();
  this->realAlg(inputProvider, thePosFileName);
}
void gisl::GeoReference::realAlg(
    const RasterProvider* input,
    std::string_view posFileName) {
  trans2D = Trans2D{};
  trans2D.loadPosData(posFileName);
  trans2D.adjust();
  Rectangle inRectangle{
      0.0f,
      0.0f,
      float(input->getXSize() - 1),
      float(input->getYSize() - 1)};
  Rectangle outRectangle{};
  trans2D.transRectangle(inRectangle, outRectangle);
  qDebug(
      "outRec: %f, %f, %f, %f",
      outRectangle.minX,
      outRectangle.minY,
      outRectangle.maxX,
      outRectangle.maxY);
  trans2D.transRec = std::make_pair(
      outRectangle.maxY - outRectangle.minY + 1.0f,
      outRectangle.maxX - outRectangle.minX + 1.0f);
}
const gisl::Trans2D& gisl::GeoReference::getTrans2D() const { return trans2D; }

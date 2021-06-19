//
// Created by km on 6/14/21.
//

#include "georeference.h"

#include <Eigen/Dense>
#include <absl/strings/str_cat.h>
#include <filesystem>
#include <fstream>
#include <limits>

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
  this->i2rAdjustA.resize(inPos.rows(), 6);
  this->i2rAdjustA.col(0) = Eigen::MatrixXf::Constant(inPos.rows(), 1, 1);
  this->i2rAdjustA.col(1) = refPos.col(0);
  this->i2rAdjustA.col(2) = refPos.col(1);
  this->i2rAdjustA.col(3) = refPos.col(0).array().square();
  this->i2rAdjustA.col(4) = refPos.col(0).array() * refPos.col(1).array();
  this->i2rAdjustA.col(5) = refPos.col(1).array().square();
  //  adjust_A << Eigen::MatrixXf::Constant(inPos.rows(), 1, 1), refPos.col(0),
  //  refPos.col(1), refPos.col(0).array().square(), refPos.col(0).array() *
  //  refPos.col(1).array(), refPos.col(1).array().square();
  this->i2rTrans = (i2rAdjustA.transpose() * i2rAdjustA).inverse() *
                   i2rAdjustA.transpose() * inPos;
  this->r2iAdjustA.resize(inPos.rows(), 6);
  this->r2iAdjustA.col(0) = Eigen::MatrixXf::Constant(inPos.rows(), 1, 1);
  this->r2iAdjustA.col(1) = inPos.col(0);
  this->r2iAdjustA.col(2) = inPos.col(1);
  this->r2iAdjustA.col(3) = inPos.col(0).array().square();
  this->r2iAdjustA.col(4) = inPos.col(0).array() * inPos.col(1).array();
  this->r2iAdjustA.col(5) = inPos.col(1).array().square();
  this->r2iTrans = (r2iAdjustA.transpose() * r2iAdjustA).inverse() *
                   r2iAdjustA.transpose() * refPos;
}
void gisl::Trans2D::i2rTransRectangle(const gisl::Rectangle& in) {
  this->inRecPos.row(0) = Eigen::Matrix<float, 1, 2>{in.minX, in.minY};
  this->inRecPos.row(1) = Eigen::Matrix<float, 1, 2>{in.minX, in.maxY};
  this->inRecPos.row(2) = Eigen::Matrix<float, 1, 2>{in.maxX, in.maxY};
  this->inRecPos.row(3) = Eigen::Matrix<float, 1, 2>{in.maxX, in.minY};
  this->outRecPos.row(0) = Eigen::Matrix<float, 1, 2>{
      this->i2rTransPoint(std::make_pair(in.minX, in.minY)).first,
      this->i2rTransPoint(std::make_pair(in.minX, in.minY)).second};
  this->outRecPos.row(1) = Eigen::Matrix<float, 1, 2>{
      this->i2rTransPoint(std::make_pair(in.minX, in.minY)).first,
      this->i2rTransPoint(std::make_pair(in.minX, in.maxY)).second};
  this->outRecPos.row(2) = Eigen::Matrix<float, 1, 2>{
      this->i2rTransPoint(std::make_pair(in.minX, in.minY)).first,
      this->i2rTransPoint(std::make_pair(in.maxX, in.maxY)).second};
  this->outRecPos.row(3) = Eigen::Matrix<float, 1, 2>{
      this->i2rTransPoint(std::make_pair(in.minX, in.minY)).first,
      this->i2rTransPoint(std::make_pair(in.maxX, in.minY)).second};
  this->transRecMN = std::make_pair(
      ceil(
          this->outRecPos.col(1).maxCoeff() -
          this->outRecPos.col(1).minCoeff() + 1),
      ceil(
          this->outRecPos.col(0).maxCoeff() -
          this->outRecPos.col(0).minCoeff() + 0));
}
std::pair<float, float>
gisl::Trans2D::i2rTransPoint(const std::pair<int, int>& p) const noexcept {
  auto q = std::make_pair((float)p.first, (float)p.second);
  float xOut = this->i2rTrans(0, 0) + this->i2rTrans(1, 0) * q.first +
               this->i2rTrans(2, 0) * q.second +
               this->i2rTrans(3, 0) * q.first * q.first +
               this->i2rTrans(4, 0) * q.first * q.second +
               this->i2rTrans(5, 0) * q.second * q.second;
  float yOut = this->i2rTrans(0, 1) + this->i2rTrans(1, 1) * q.first +
               this->i2rTrans(2, 1) * q.second +
               this->i2rTrans(3, 1) * q.first * q.first +
               this->i2rTrans(4, 1) * q.first * q.second +
               this->i2rTrans(5, 1) * q.second * q.second;
  return std::pair<float, float>(
      xOut - this->transRecMN.second,
      yOut - this->transRecMN.first);
}
std::pair<float, float>
gisl::Trans2D::r2iTransPoint(const std::pair<int, int>& p) const noexcept {
  std::pair<float, float> q = std::make_pair(
      (float)p.first + this->transRecMN.second,
      (float)p.second + this->transRecMN.first);
  float xOut = this->r2iTrans(0, 0) + this->i2rTrans(1, 0) * q.first +
               this->r2iTrans(2, 0) * q.second +
               this->r2iTrans(3, 0) * q.first * q.first +
               this->r2iTrans(4, 0) * q.first * q.second +
               this->r2iTrans(5, 0) * q.second * q.second;
  float yOut = this->r2iTrans(0, 1) + this->r2iTrans(1, 1) * q.first +
               this->r2iTrans(2, 1) * q.second +
               this->r2iTrans(3, 1) * q.first * q.first +
               this->r2iTrans(4, 1) * q.first * q.second +
               this->r2iTrans(5, 1) * q.second * q.second;
  return std::pair<float, float>(xOut, yOut);
}
bool gisl::Trans2D::isIInsideR(int x, int y) const noexcept {
  return false;
#if 0
  auto xf = float(x);
  auto yf = float(y);
  float m1 = this->outRecPos(0, 1) - this->outRecPos(1, 1);
  float m2 = this->outRecPos(0, 0) - this->outRecPos(1, 0);
  float m3 = this->outRecPos(1, 1) * this->outRecPos(0, 0) -
             this->outRecPos(0, 1) * this->outRecPos(1, 0);
  float m4 = this->outRecPos(2, 1) * this->outRecPos(3, 0) -
             this->outRecPos(3, 1) * this->outRecPos(2, 0);
  float m5 = this->outRecPos(2, 1) - this->outRecPos(1, 1);
  float m6 = this->outRecPos(2, 0) - this->outRecPos(1, 0);
  float m7 = this->outRecPos(1, 1) * this->outRecPos(2, 0) -
             this->outRecPos(2, 1) * this->outRecPos(1, 0);
  float m8 = this->outRecPos(0, 1) * this->outRecPos(3, 0) -
             this->outRecPos(3, 1) * this->outRecPos(0, 0);
  return abs(abs(m1 * xf - m2 * yf + m3) + abs(m1 * xf - m2 * yf + m4) -
             abs(m3 - m4)) < std::numeric_limits<float>::epsilon() &&
         abs(abs(m5 * xf - m6 * yf + m7) + abs(m5 * xf - m6 * yf + m8) -
             abs(m7 - m8)) < std::numeric_limits<float>::epsilon();
#endif
}
bool gisl::Trans2D::isRInsideI(const std::pair<int, int>& q) const noexcept {
  auto p = this->r2iTransPoint(q);
  return p.first >= this->inRecPos(0, 0) && p.first <= this->inRecPos(2, 0) &&
         p.second >= this->inRecPos(0, 1) && p.second <= this->inRecPos(1, 1);
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
  trans2D.i2rTransRectangle(inRectangle);

  this->outImage = QImage{
      this->trans2D.transRecMN.second,
      this->trans2D.transRecMN.first,
      QImage::Format_RGB32};

  for (int i = 0; i < this->trans2D.transRecMN.second; ++i) {
    for (int j = 0; j < this->trans2D.transRecMN.first; ++j) {
      auto p = this->trans2D.r2iTransPoint(std::make_pair(i, j));
      if (this->trans2D.isRInsideI(std::make_pair(i, j))) {
        this->outImage.setPixel(
            j,
            i,
            qRgb(
                input->getPmBand()[0]->getFData()(int(p.first), int(p.second)) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first) + 1,
                        int(p.second)) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first),
                        int(p.second) + 1) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first) + 1,
                        int(p.second) + 1),
                input->getPmBand()[0]->getFData()(int(p.first), int(p.second)) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first) + 1,
                        int(p.second)) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first),
                        int(p.second) + 1) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first) + 1,
                        int(p.second) + 1),
                input->getPmBand()[0]->getFData()(int(p.first), int(p.second)) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first) + 1,
                        int(p.second)) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first),
                        int(p.second) + 1) +
                    input->getPmBand()[0]->getFData()(
                        int(p.first) + 1,
                        int(p.second) + 1)));
      }
    }
  }
}
const gisl::Trans2D& gisl::GeoReference::getTrans2D() const { return trans2D; }

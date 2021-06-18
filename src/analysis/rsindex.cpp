//
// Created by omega on 6/18/21.
//

#include <QColor>
#include <absl/strings/str_cat.h>

#include "rsindex.h"

void gisl::RsIndex::execAlg() {}
void gisl::RsIndex::reverse() {}
const std::string& gisl::RsIndex::output() { return this->_errorMessage; }
void gisl::RsIndex::execute(QWidget* parent) { AnalysisAlg::execute(parent); }
void gisl::RsIndex::initGui() { AnalysisAlg::initGui(); }
void gisl::RsIndex::realAlg(
    RsIndexMethod m,
    RasterBand& band1,
    RasterBand& band2) {
  switch (m) {
  case gisl::RsIndex::RsIndexMethod::Normal:
    return;
  case gisl::RsIndex::RsIndexMethod::NDWI: {
    this->imgFileName = absl::StrCat(
        band1.getFileName().substr(0, band1.getFileName().size() - 6),
        ".NDWI.png");
    auto greenBandData = band1.getFData();
    auto mriBandData = band2.getFData();
    this->index = (greenBandData.array() - mriBandData.array()) /
                  (greenBandData.array() + mriBandData.array());
  }
  case gisl::RsIndex::RsIndexMethod::MNDWI: {
  }
  }
}
void gisl::RsIndex::toImg() {
  this->qImage =
      QImage(this->index.cols(), this->index.rows(), QImage::Format_RGB32);

  for (int i = 0; i < this->index.cols(); ++i) {
    for (int j = 0; j < this->index.rows(); ++j) {
      this->qImage.setPixel(
          i,
          j,
          qRgb(
              this->index(j, i) > 0 ? 255 : 0,
              this->index(j, i) > 0 ? 255 : 0,
              this->index(j, i) > 0 ? 255 : 0));
    }
  }
  this->qImage.save(QString::fromStdString(this->imgFileName));
}

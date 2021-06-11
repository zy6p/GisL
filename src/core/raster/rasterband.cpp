//
// Created by omega on 6/10/21.
//

#include <absl/strings/str_cat.h>

#include "rasterband.h"
gisl::RasterBand::~RasterBand() { CPLFree(fData); }
void gisl::RasterBand::draw(gisl::PainterFactory &p) {}
void gisl::RasterBand::setGDALLayer(GDALRasterBand *gdalRasterBand) {
  this->pmRasterBand = gdalRasterBand;
  this->xSize = this->pmRasterBand->GetXSize();
  this->ySize = this->pmRasterBand->GetYSize();

  for (int i = 0; i < ySize; ++i) {
    fData = (float *)CPLMalloc(sizeof(float) * xSize * ySize);

    pmRasterBand->RasterIO(GF_Read, 0, i, xSize, ySize, fData, xSize, ySize,
                           GDT_Float32, 0, 0);
  }
}

void gisl::RasterBand::matrixToStr() {
  std::string matrix{};
  for (int i = 0; i < xSize; ++i) {
    for (int j = 0; j < ySize; ++j) {
      matrix += absl::StrCat(std::to_string(*(fData + i * xSize + j)), "\t");
    }
    matrix += "\n";
  }
  qDebug("%s", matrix.c_str());
}

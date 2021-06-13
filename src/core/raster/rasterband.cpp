//
// Created by omega on 6/10/21.
//

#include <QImageWriter>
#include <QPixmap>
#include <absl/strings/str_cat.h>

#include "rasterband.h"
#include "src/utils/ptroperate.h"
gisl::RasterBand::~RasterBand() {}
void gisl::RasterBand::draw(gisl::PainterFactory& p) {
  QPixmap qPixmap = QPixmap::fromImage(*qImage);
  p.drawRaster(std::make_shared<QPixmap>(qPixmap));
}
void gisl::RasterBand::setGDALLayer(GDALRasterBand* gdalRasterBand) {
  this->pmRasterBand = gdalRasterBand;
  this->xSize = this->pmRasterBand->GetXSize();
  this->ySize = this->pmRasterBand->GetYSize();
  this->pmRasterBand->GetStatistics(
      true,
      true,
      &minimumValue,
      &maximumValue,
      &meanValue,
      &sigmaValue);
  fData = Eigen::MatrixXf{ySize, xSize};

  /*
   * function float** GetRasterBand(int z):
   * This function reads a band from a geotiff at a
   * specified vertical level (z value, 1 ...
   * n bands). To this end, the Geotiff's GDAL
   * data type is passed to a switch statement,
   * and the template function GetArray2D (see below)
   * is called with the appropriate C++ data type.
   * The GetArray2D function uses the passed-in C++
   * data type to properly read the band data from
   * the Geotiff, cast the data to float**, and return
   * it to this function. This function returns that
   * float** pointer.
   */
  switch (GDALGetRasterDataType(pmRasterBand)) {
  case 0:
    mErr = LayerErr::DataErr;
    return;
  case 1:
    // GDAL GDT_Byte (-128 to 127) - unsigned  char
    GetArray2D<unsigned char>(GDT_Byte, 1);
  case 2:
    // GDAL GDT_UInt16 - short
    GetArray2D<unsigned short>(GDT_UInt16, 2);
  case 3:
    // GDT_Int16
    GetArray2D<short>(GDT_Int16, 2);
  case 4:
    // GDT_UInt32
    GetArray2D<unsigned int>(GDT_UInt32, 4);
  case 5:
    // GDT_Int32
    GetArray2D<int>(GDT_Int32, 4);
  case 6:
    // GDT_Float32
    GetArray2D<float>(GDT_Float32, 4);
  case 7:
    // GDT_Float64
    GetArray2D<double>(GDT_Float64, 8);
  default:
    break;
  }
}

void gisl::RasterBand::matrixToStr() {
  std::string matrix{};
  for (int i = 0; i < ySize; ++i) {
    for (int j = 0; j < xSize; ++j) {
      matrix += absl::StrCat(std::to_string(fData(i, j)), "\t");
    }
    matrix += "\n";
  }
  qDebug("%s", matrix.c_str());
}
void gisl::RasterBand::toImg() {
  qImage = new QImage(xSize, ySize, QImage::Format_RGB32);
  Eigen::MatrixXf tmp = (fData - Eigen::MatrixXf::Constant(
                                     ySize,
                                     xSize,
                                     float(meanValue - 2 * sigmaValue))) *
                        128.0f / sigmaValue;
  imgData = tmp.cast<int>();
  for (int i = 0; i < ySize; ++i) {
    for (int j = 0; j < xSize; ++j) {
      qImage->setPixel(j, i, qRgb(imgData(i, j), imgData(i, j), imgData(i, j)));
    }
  }
  qImage->save(QString::fromStdString(fileName));
}

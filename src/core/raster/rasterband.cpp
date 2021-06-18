//
// Created by omega on 6/10/21.
//

#include <QImageWriter>
#include <QPixmap>
#include <absl/strings/str_cat.h>
#include <limits>

#include "rasterband.h"
gisl::RasterBand::~RasterBand() = default;
void gisl::RasterBand::draw(gisl::PainterFactory& p) {
  QPixmap qPixmap = QPixmap::fromImage(qImage);
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
  this->histogramArray = new unsigned long long[this->histogramBuckets];
  pmRasterBand->GetHistogram(
      minimumValue - std::numeric_limits<double>::epsilon(),
      maximumValue + std::numeric_limits<double>::epsilon(),
      histogramBuckets,
      histogramArray,
      false,
      false,
      GDALDummyProgress,
      nullptr);

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
void gisl::RasterBand::toImg(ContrastEnhancementMethod m) {
  qImage = QImage(xSize, ySize, QImage::Format_RGB32);
  this->contrastEnhancement(m);
  for (int i = 0; i < ySize; ++i) {
    for (int j = 0; j < xSize; ++j) {
      qImage.setPixel(j, i, qRgb(imgData(i, j), imgData(i, j), imgData(i, j)));
    }
  }
  qImage.save(QString::fromStdString(fileName));
}
void gisl::RasterBand::contrastEnhancement(ContrastEnhancementMethod m) {
  switch (m) {
  case ContrastEnhancementMethod::Normal: {
    imgData = fData.cast<int>();
    break;
  }
  case ContrastEnhancementMethod::StretchToRealMinMax: {
    imgData =
        ((fData -
          Eigen::MatrixXf::Constant(ySize, xSize, (float)this->minimumValue)) *
         256.0f / (this->maximumValue - this->minimumValue))
            .cast<int>();
    break;
  }
  case ContrastEnhancementMethod::StretchToCumulative96RealMinMax: {
    double minPercent = 0;
    double maxPercent = 1;
    unsigned long long p1 = 0;
    unsigned long long p2 = this->histogramBuckets - 1;
    while (minPercent < 0.02) {
      minPercent += (double)this->histogramArray[p1++] /
                    double(this->xSize * this->ySize);
    }
    while (maxPercent > 0.98) {
      maxPercent -= (double)this->histogramArray[p2--] /
                    double(this->xSize * this->ySize);
    }
    double gap = (this->maximumValue - this->minimumValue) /
                 (double)this->histogramBuckets;
    imgData = ((fData - Eigen::MatrixXf::Constant(
                            ySize,
                            xSize,
                            float(minimumValue + (float)p1 * gap))) *
               256.0 / float(minimumValue + (float)p2 * gap))
                  .cast<int>();
    qDebug(
        "2'per is: %f, 98'per is: %f",
        float(minimumValue + (float)p1 * gap),
        float(minimumValue + (float)p2 * gap));
    imgData = (imgData.array() < 0)
                  .select(Eigen::MatrixXi::Constant(ySize, xSize, 0), imgData);
    imgData =
        (imgData.array() > 255)
            .select(Eigen::MatrixXi::Constant(ySize, xSize, 255), imgData);
    break;
  }
  case ContrastEnhancementMethod::StretchTo2StandardDeviation: {
    imgData = ((fData - Eigen::MatrixXf::Constant(
                            ySize,
                            xSize,
                            float(meanValue - 2.0f * sigmaValue))) *
               256.0f / sigmaValue)
                  .cast<int>();
    imgData = (imgData.array() < 0)
                  .select(Eigen::MatrixXi::Constant(ySize, xSize, 0), imgData);
    imgData =
        (imgData.array() > 255)
            .select(Eigen::MatrixXi::Constant(ySize, xSize, 255), imgData);
    break;
  }
  default: {
    imgData = fData.cast<int>();
    break;
  }
  }
}
void gisl::RasterBand::draw() {
  auto* rv = new ImgViewWidget();
  rv->show();
  this->draw(*rv);
}
QPolygonF gisl::RasterBand::calHistogram() const {
  QPolygonF polygonF{this->histogramBuckets};
  double gap =
      (this->maximumValue - this->minimumValue) / this->histogramBuckets;
  double begin = this->minimumValue + 0.5 * gap;
  for (int i = 0; i < this->histogramBuckets; ++i) {
    polygonF << QPointF{begin + i * gap, (double)this->histogramArray[i]};
  }
  return polygonF;
}
const Eigen::MatrixXf& gisl::RasterBand::getFData() const { return fData; }

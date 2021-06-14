//
// Created by omega on 6/10/21.
//

#ifndef GISL_RASTERBAND_H
#define GISL_RASTERBAND_H

#include <Eigen/Dense>
#include <gdal_rat.h>

#include "src/core/layer/layer.h"

namespace gisl {
class RasterBand final : public Layer {
public:
  enum class ContrastEnhancementMethod {
    None = 0,
    StretchToRealMinMax = 1,
    StretchToCumulative96RealMinMax = 2,
    StretchTo2StandardDeviation = 3,
  };

  void setGDALLayer(GDALRasterBand* gdalRasterBand);
  void draw() override;
  void draw(PainterFactory& p) override;
  [[nodiscard]] QPolygonF calHistogram() const;
  ~RasterBand() override;
  void matrixToStr();
  void toImg();
  void contrastEnhancement(ContrastEnhancementMethod m);

private:
  int xSize = 0;
  int ySize = 0;
  double maximumValue = 0;
  double minimumValue = 0;
  double meanValue = 0;
  double sigmaValue = 0;

  unsigned long long* histogramArray = nullptr;
  int histogramBuckets = 1024;

  GDALRasterBand* pmRasterBand = nullptr;
  Eigen::MatrixXf fData;
  Eigen::MatrixXi imgData;

  template <typename T> float** GetArray2D(GDALDataType t, int nbytes) {

    /*
     * function float** GetArray2D(int layerIndex):
     * This function returns a pointer (to a pointer)
     * for a float array that holds the band (array)
     * data from the geotiff, for a specified layer
     * index layerIndex (1,2,3... for GDAL, for Geotiffs
     * with more than one band or data layer, 3D that is).
     *
     * Note this is a template function that is meant
     * to take in a valid C++ data type (i.e. char,
     * short, int, float), for the Geotiff in question
     * such that the Geotiff band data may be properly
     * read-in as numbers. Then, this function casts
     * the data to a float data type automatically.
     */
    //    GDALDataType bandType = GDALGetRasterDataType(pmRasterBand);
    //
    //    // get number of bytes per pixel in Geotiff
    //    int nbytes = GDALGetDataTypeSize(bandType);

    // allocate pointer to memory block for one row (scanline)
    // in 2D Geotiff array.
    T* rowBuff = (T*)CPLMalloc(nbytes * xSize * ySize);
    //    void* rowBuff = malloc(nbytes * xSize);

    //    for (int row = 0; row < ySize; row++) { // iterate through rows

    // read the scanline into the dynamically allocated row-buffer
    if (0 != pmRasterBand->RasterIO(
                 GF_Read,
                 0,
                 0,
                 xSize,
                 ySize,
                 rowBuff,
                 xSize,
                 ySize,
                 t,
                 0,
                 0)) {
      this->mErr = LayerErr::DataErr;
    }

    for (int row = 0; row < ySize; ++row) {
      for (int col = 0; col < xSize; col++) { // iterate through columns
        fData(row, col) = (float)rowBuff[row * xSize + col];
      }
    }
    CPLFree(rowBuff);
  }
  friend class RasterProvider;
};

} // namespace gisl

#endif // GISL_RASTERBAND_H

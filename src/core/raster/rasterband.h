//
// Created by omega on 6/10/21.
//

#ifndef GISL_RASTERBAND_H
#define GISL_RASTERBAND_H

#include <gdal_rat.h>

#include <src/core/layer/layer.h>

namespace gisl {
class RasterBand final : public Layer {
public:
  void setGDALLayer(GDALRasterBand* gdalRasterBand);
  virtual void draw(PainterFactory& p) override;
  ~RasterBand();
  void matrixToStr();
  void toImg();

protected:
  int xSize = 0;
  int ySize = 0;
  double maximumValue = 0;
  double minimumValue = 0;

  GDALRasterBand* pmRasterBand = nullptr;
  float** fData = nullptr;
  QImage* qImage;

  template <typename T> float** GetArray2D() {

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

    // get the raster data type (ENUM integer 1-12,
    // see GDAL C/C++ documentation for more details)
    GDALDataType bandType = GDALGetRasterDataType(pmRasterBand);

    // get number of bytes per pixel in Geotiff
    int nbytes = GDALGetDataTypeSizeBytes(bandType);

    // allocate pointer to memory block for one row (scanline)
    // in 2D Geotiff array.
    T* rowBuff = (T*)CPLMalloc(nbytes * xSize);

    for (int row = 0; row < ySize; row++) { // iterate through rows

      // read the scanline into the dynamically allocated row-buffer
      CPLErr e = pmRasterBand->RasterIO(
          GF_Read,
          0,
          row,
          xSize,
          1,
          rowBuff,
          xSize,
          1,
          bandType,
          0,
          0);
      if (e != 0) {
        this->mErr = LayerErr::DataErr;
      }

      fData[row] = new float[xSize];
      for (int col = 0; col < xSize; col++) { // iterate through columns
        fData[row][col] = (float)rowBuff[col];
      }
    }
    CPLFree(rowBuff);
  }
};

} // namespace gisl

#endif // GISL_RASTERBAND_H

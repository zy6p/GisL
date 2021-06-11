//
// Created by omega on 6/10/21.
//

#include "rasterband.h"
gisl::RasterBand::~RasterBand() {
  for (int i = 0; i < ySize; ++i) {
    CPLFree(data[i]);
  }
  delete[] data;
  data = nullptr;
}
void gisl::RasterBand::draw(gisl::PainterFactory &p) {}
void gisl::RasterBand::setGDALLayer(GDALRasterBand &gdalRasterBand) {
  this->pmRasterBand = &gdalRasterBand;
  this->xSize = this->pmRasterBand->GetXSize();
  this->ySize = this->pmRasterBand->GetYSize();

  for (int i = 0; i < ySize; ++i) {
    float *fScanline;
    fScanline = (float *) CPLMalloc(sizeof(float)*xSize);

    pmRasterBand->RasterIO( GF_Read, 0, i, xSize, 1,
                           fScanline, xSize, 1, GDT_Float32, 0, 0 );
    data[i] = fScanline;
  }

}

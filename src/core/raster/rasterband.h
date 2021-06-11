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
  void setGDALLayer(GDALRasterBand &gdalRasterBand);
  virtual void draw(PainterFactory &p) override;
  ~RasterBand();

protected:
  int xSize = 0;
  int ySize = 0;

  GDALRasterBand* pmRasterBand = nullptr;
  float** data = nullptr;
};
} // namespace gisl

#endif // GISL_RASTERBAND_H

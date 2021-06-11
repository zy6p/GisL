//
// Created by omega on 6/10/21.
//

#ifndef GISL_RASTERBAND_H
#define GISL_RASTERBAND_H

#include <src/core/layer/layer.h>
namespace gisl {
class RasterBand final : public Layer {
public:
  virtual void draw(PainterFactory &p) override;
  ~RasterBand();

protected:
  int xSize;
  int ySize;
};
} // namespace gisl

#endif // GISL_RASTERBAND_H

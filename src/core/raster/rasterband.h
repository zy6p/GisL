//
// Created by omega on 6/10/21.
//

#ifndef GISL_RASTERBAND_H
#define GISL_RASTERBAND_H

#include <src/core/layer/layer.h>
namespace gisl {
class rasterband final : public Layer {
public:
protected:
  int xSize;
  int ySize;
};
} // namespace gisl

#endif // GISL_RASTERBAND_H

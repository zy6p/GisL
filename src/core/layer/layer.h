//
// Created by omega on 6/10/21.
//

#ifndef GISL_LAYER_H
#define GISL_LAYER_H

#include <memory>

#include <src/core/spatialreference.h>
#include <src/gui/painter/painterfactory.h>
#include <src/utils/log.h>
namespace gisl {
class Layer {
public:
  static void seed(int seed);

  Layer();
  virtual ~Layer();

  virtual void draw(PainterFactory &p) = 0;

protected:
  static int fidSeed;
  int fid;

  std::shared_ptr<SpatialReference> pmCrs;

  std::shared_ptr<Log> log;
};
} // namespace gisl
#endif // GISL_LAYER_H

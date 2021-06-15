//
// Created by omega on 6/10/21.
//

#ifndef GISL_LAYER_H
#define GISL_LAYER_H

#include <QImage>
#include <memory>

#include "core/spatialreference.h"
#include "gui/painter/painterfactory.h"
#include "gui/render/imgviewwidget.h"
#include "utils/log.h"
namespace gisl {
class Layer {
public:
  enum class LayerErr {
    NoErr = 0,
    DataErr,
  };
  bool hasError() { return mErr != LayerErr::NoErr; }
  static void seed(int seed);

  Layer();
  int getFid();
  virtual ~Layer();

  virtual void draw(PainterFactory& p) = 0;
  virtual void draw() = 0;

  const std::string& getFileName() const;
  void setFileName(const std::string& fileName);

protected:
  static int fidSeed;
  int fid;

  std::string fileName;
  LayerErr mErr = LayerErr::NoErr;
  std::shared_ptr<SpatialReference> pmCrs;

  QImage qImage;

  std::shared_ptr<Log> log;
};
} // namespace gisl
#endif // GISL_LAYER_H

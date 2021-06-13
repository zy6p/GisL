/*!
 * @author tau
 * @date 1/1/21
 */

#ifndef GISL_PAINTERFACTORY_H
#define GISL_PAINTERFACTORY_H

#include "../../core/coordinatetransform.h"
#include "../../core/geometry/rectangle.h"
#include "../sld.h"

namespace gisl {
class PainterFactory {
public:
  void getLayerFid(int fid);

  virtual void drawPoint(ExchangePointXY& p) = 0;

  virtual void drawLine(ExchangeLine& p) = 0;

  virtual void drawPolygon(ExchangePolygon& p) = 0;

  virtual void drawMultiPolygon(ExchangePolygon** ps, int count) = 0;

  virtual void drawRaster(std::shared_ptr<QPixmap>) = 0;

  virtual void
  drawLinearRing(ExchangeLinearRing* p, const std::string& featureName) = 0;

  virtual void getEnvelope(Rectangle& rectangle);

  Sld* getSld() const;

  void setSld(Sld* pSld);

  virtual void setRandSld();

  virtual ~PainterFactory() = default;

  Sld* pmSld = nullptr;

protected:
  int layerFid;

  Rectangle* pmEnvelope = nullptr;
};
} // namespace gisl

#endif // GISL_PAINTERFACTORY_H

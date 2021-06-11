/*!
 * @author tau
 * @date 1/1/21
 */

#ifndef GISL_GLPAINTERFACTORY_H
#define GISL_GLPAINTERFACTORY_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "painterfactory.h"

namespace gisl {
class GlPainterFactory : public PainterFactory {
public:
  void drawPoint(ExchangePointXY& p) override;

  void drawLine(ExchangeLine& p) override;

  void drawPolygon(ExchangePolygon& p) override;

  QOpenGLWidget* parent;
};
} // namespace gisl

#endif // GISL_GLPAINTERFACTORY_H

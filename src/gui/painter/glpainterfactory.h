/*!
 * @author tau 
 * @date 1/1/21
*/

#ifndef GISL_GLPAINTERFACTORY_H
#define GISL_GLPAINTERFACTORY_H

#include "painterfactory.h"

namespace GisL {
    class GlPainterFactory : public PainterFactory {
    public:
        void drawPoint( ExchangePointXY &p ) override;

        void drawLine( ExchangeLine &p ) override;

        void drawPolygon( ExchangePolygon &p ) override;
    };
}

#endif //GISL_GLPAINTERFACTORY_H

/*!
 * @author tau 
 * @date 1/1/21
*/

#ifndef GISL_PAINTERFACTORY_H
#define GISL_PAINTERFACTORY_H

#include "../../core/coordinatetransform.h"
#include "../../core/geometry/rectangle.h"

namespace GisL {
    class PainterFactory {
    public:
        virtual void drawPoint( ExchangePointXY &p ) = 0;

        virtual void drawLine( ExchangeLine &p ) = 0;

        virtual void drawPolygon( ExchangePolygon &p ) = 0;

        virtual void drawMultiPolygon( ExchangePolygon **ps, int count ) = 0;

        virtual void drawLinearRing( ExchangeLinearRing *p ) = 0;

        virtual void getEnvelope( Rectangle &rectangle );

        virtual ~PainterFactory( ) = default;

    protected:
        Rectangle *pmEnvelope = nullptr;

    };
}

#endif //GISL_PAINTERFACTORY_H

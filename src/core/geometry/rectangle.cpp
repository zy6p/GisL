/*!
 * @author tau 
 * @date 12/29/20
*/

#include "rectangle.h"

namespace GisL {
    Rectangle::Rectangle( OGREnvelope &envelope ) : pmEnvelope( &envelope ) {
        minX = pmEnvelope->MinX;
        maxX = pmEnvelope->MaxX;
        minY = pmEnvelope->MinY;
        maxY = pmEnvelope->MaxY;
    }

    void Rectangle::merge( const Rectangle &sOther ) {
        minX = MIN( minX, sOther.minX );
        maxX = MAX( maxX, sOther.maxX );
        minY = MIN( minY, sOther.minY );
        maxY = MAX( maxY, sOther.maxY );
    }

    void Rectangle::merge( double dfX, double dfY ) {
        minX = MIN( minX, dfX );
        maxX = MAX( maxX, dfX );
        minY = MIN( minY, dfY );
        maxY = MAX( maxY, dfY );
    }
}
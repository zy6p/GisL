/*!
 * @author tau 
 * @date 12/20/20
*/

#include "geometry.h"

namespace GisL {

    Geometry::Geometry(OGRGeometry &poGeometry) {
        pmGeometry = &poGeometry;
    }

    Geometry &Geometry::operator=( const Geometry &ths ) {
        return *this;
    }
}
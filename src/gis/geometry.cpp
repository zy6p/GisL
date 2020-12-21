/*!
 * @author tau 
 * @date 12/20/20
*/

#include "geometry.h"

namespace GisL {

    Geometry::Geometry(OGRGeometry *poGeometry) {
        pmGeometry = poGeometry;
    }
}
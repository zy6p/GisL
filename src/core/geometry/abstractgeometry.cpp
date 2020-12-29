/*!
 * @author tau 
 * @date 12/29/20
*/

#include "abstractgeometry.h"

namespace GisL {

    AbstractGeometry::WkbType AbstractGeometry::wkbType( ) const {
        return mWkbType;
    }

    bool AbstractGeometry::hasError( ) const {
        return mGeomErr;
    }

}
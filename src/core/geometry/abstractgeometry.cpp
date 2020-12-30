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

    void AbstractGeometry::detectWkbType( AbstractGeometry &p ) {
        OGRwkbGeometryType type = p.getGeometryType();
        switch ( type ) {
            case wkbPoint:
                p.mWkbType = Point;
                p.toPoint();
                break;
            case wkbLineString:
                p.mWkbType = LineString;
                break;
            case wkbPolygon:
                p.mWkbType = Polygon;
                break;
            case wkbMultiPoint:
                p.mWkbType = MultiPoint;
                break;
            case wkbMultiLineString:
                p.mWkbType = MultiLineString;
                break;
            case wkbMultiPolygon:
                p.mWkbType = MultiPolygon;
                break;
            case wkbUnknown:
                p.mWkbType = Unknown;
                break;
            case wkbNone:
                p.mWkbType = NoGeometry;
                break;
            default:
                p.mWkbType = Unknown;
        }
    }

}
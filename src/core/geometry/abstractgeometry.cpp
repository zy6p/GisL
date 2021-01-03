/*!
 * @author tau 
 * @date 12/29/20
*/

#include "abstractgeometry.h"

namespace GisL {


    AbstractGeometry::AbstractGeometry( OGRGeometry &p ) {
        pmGeometry = &p;
    }

    bool AbstractGeometry::hasError( ) const {
        return mGeomErr;
    }

    void AbstractGeometry::detectWkbType( AbstractGeometry &p ) {
        OGRwkbGeometryType type = p.pmGeometry->getGeometryType();
        switch ( type ) {
            case wkbPoint:
                p.mWkbType = Point;
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

    void AbstractGeometry::clear( ) {
        pmGeometry->empty();
    }

    Rectangle *AbstractGeometry::boundary( ) const {
        Rectangle *p;
        pmGeometry->getEnvelope( p );
        return p;
    }

    AbstractGeometry::~AbstractGeometry( ) {
        AbstractGeometry::clear();
    }

    OGRGeometry *AbstractGeometry::getGeometry( ) const {
        return pmGeometry;
    }

    const std::string &AbstractGeometry::getFeatureName( ) const {
        return featureName;
    }

    void AbstractGeometry::setFeatureName( const std::string &name ) {
        AbstractGeometry::featureName = name;
    }


}
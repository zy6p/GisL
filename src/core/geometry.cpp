/*!
 * @author tau 
 * @date 12/20/20
*/

#include "geometry.h"

#include <gdal/ogr_geometry.h>
#include "../utils/ptroperate.h"

namespace GisL {

    Geometry::Geometry( OGRGeometry &poGeometry ) : GisLObject() {
        geoType = None;
        pmSymbol = nullptr;
        if ( !poGeometry.IsValid()) {
            mError = MError::GisLError::ErrGeometry;
            mErrorMessage = "wrong! the geometry is not valid";
            return;
        }

        if ( !poGeometry.IsEmpty()) {
            mError = MError::GisLError::ErrGeometry;
            mErrorMessage = "wrong! the geometry is empty";
            return;
        }
        pmGeometry = &poGeometry;
    }

    Geometry::GeoType Geometry::detectGeoType( OGRGeometry &poGeometry ) {
        OGRwkbGeometryType wkbGeometryType = poGeometry.getGeometryType();
        GeoType result;
        switch ( wkbGeometryType ) {
            default:
                result = None;
                break;
            case wkbPoint: {
                result = Point;
                break;
            }
            case wkbLineString: {
                result = LineString;
                break;
            }
            case wkbPolygon: {
                result = Polygon;
                break;
            }
            case wkbMultiPoint: {
                result = MultiPoint;
                break;
            }
            case wkbMultiLineString: {
                result = MultiLineString;
                break;
            }
            case wkbMultiPolygon: {
                result = MultiPolygon;
                break;
            }
        }
        return result;
    }


    Geometry &Geometry::operator=( const Geometry &ths ) {
        return *this;
    }

    void Geometry::setSymbol( Sld::Symbol &poSymbol ) {
        pmSymbol = &poSymbol;
    }

    Geometry::~Geometry( ) {
        PtrOperate::clear( pmSymbol );
    };
}
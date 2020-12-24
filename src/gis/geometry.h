/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_GEOMETRY_H
#define GISL_GEOMETRY_H

#include <gdal/ogr_geometry.h>

#include "../utils/merror.h"

namespace GisL {
    class Geometry {
    public:

        enum GeoType {
            None,
            Point = OGRwkbGeometryType::wkbPoint,
            LineString = OGRwkbGeometryType::wkbLineString,
            Polygon = OGRwkbGeometryType::wkbPolygon,
            MultiPoint = OGRwkbGeometryType::wkbMultiPoint,
            MultiLineString = OGRwkbGeometryType::wkbMultiLineString,
            MultiPolygon = OGRwkbGeometryType::wkbMultiPolygon
        };


        explicit Geometry(OGRGeometry &poGeometry);

        virtual void initRender() = 0;

        ~Geometry();

        Geometry &operator=(const Geometry &rhs);

        static Geometry::GeoType detectGeoType(OGRGeometry &poGeometry);

        bool hasError();

        std::string errorMessage();


    protected:
        MError::GisLError mError;
        std::string mErrorMessage;

        OGRGeometry *pmGeometry;

        GeoType geoType;
    };
}

#endif //GISL_GEOMETRY_H

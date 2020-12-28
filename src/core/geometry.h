/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_GEOMETRY_H
#define GISL_GEOMETRY_H

#include <gdal/ogr_geometry.h>

#include "../utils/gislobject.h"
#include "../gui/sld.h"

namespace GisL {
    class Geometry : public GisLObject {
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

        explicit Geometry( OGRGeometry &poGeometry );

        void setSymbol( Symbolizer &symbolizer );

        ~Geometry( ) = default;

        Geometry &operator=( const Geometry &rhs );

        static Geometry::GeoType detectGeoType( OGRGeometry &poGeometry );


    protected:

        Symbolizer *pmSymbolizer;

        OGRGeometry *pmGeometry;

        GeoType geoType;
    };
}

#endif //GISL_GEOMETRY_H

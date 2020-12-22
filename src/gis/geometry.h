/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_GEOMETRY_H
#define GISL_GEOMETRY_H

#include <gdal/ogr_geometry.h>

namespace GisL {
    class Geometry {
    public:

        enum GeoType {
            Point,
            Line,
            Polygon,
            MultiPoint,
            MultiLine,
            MultiPolygon
        };




        explicit Geometry(OGRGeometry* poGeometry);


    private:
        OGRGeometry* pmGeometry;

    };
}

#endif //GISL_GEOMETRY_H

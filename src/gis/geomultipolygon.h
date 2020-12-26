//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTIPOLYGON_H
#define GISL_GEOMULTIPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"

namespace GisL {

    class GeoMultiPolygon : public Geometry {
    public:
        explicit GeoMultiPolygon( OGRGeometry &poGeometry );

        ~GeoMultiPolygon( );

    };

}

#endif //GISL_GEOMULTIPOLYGON_H


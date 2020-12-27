//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTILINE_H
#define GISL_GEOMULTILINE_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"

namespace GisL {

    class GeoMultiLine : public Geometry {
    public:
        explicit GeoMultiLine( OGRGeometry &poGeometry );

        ~GeoMultiLine( );
    };

}

#endif //GISL_GEOMULTILINE_H

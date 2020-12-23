//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTIPOINT_H
#define GISL_GEOMULTIPOINT_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"

namespace GisL {

    class GeoMultiPoint : public Geometry {
    public:
        explicit GeoMultiPoint(OGRGeometry &poGeometry);

        ~GeoMultiPoint();
    };

}

#endif //GISL_GEOMULTIPOINT_H

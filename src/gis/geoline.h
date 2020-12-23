//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOLINE_H
#define GISL_GEOLINE_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"

namespace GisL {

    class GeoLine : public Geometry {
    public:
        explicit GeoLine(OGRGeometry &poGeometry);

    };

}

#endif //GISL_GEOLINE_H

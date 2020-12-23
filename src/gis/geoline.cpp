//
// Created by omega on 14/12/2020.
//

#include "geoline.h"

#include <gdal/ogr_geometry.h>

namespace GisL {

    GeoLine::GeoLine(OGRGeometry &poGeometry) : Geometry(poGeometry) {

    }
}
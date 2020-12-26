//
// Created by omega on 14/12/2020.
//

#include "geopolygon.h"

namespace GisL {

    GeoPolygon::GeoPolygon( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {

    }

    GeoPolygon::~GeoPolygon( ) {

    }
}
//
// Created by omega on 14/12/2020.
//

#include "geomultipolygon.h"

namespace GisL {

    GeoMultiPolygon::GeoMultiPolygon(OGRGeometry &poGeometry) : Geometry(poGeometry) {

    }

    GeoMultiPolygon::~GeoMultiPolygon() {

    }
}
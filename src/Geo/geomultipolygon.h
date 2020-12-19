//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTIPOLYGON_H
#define GISL_GEOMULTIPOLYGON_H

#include "geofeature.h"

namespace GisL {

    class GeoMultiPolygon : public GeoFeature {

        GeoMultiPolygon() : GeoFeature(std::__cxx11::string(), 0) {}
    };

}

#endif //GISL_GEOMULTIPOLYGON_H


//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOPOLYGON_H
#define GISL_GEOPOLYGON_H

#include "geofeature.h"

namespace GisL {

    class GeoPolygon : public GeoFeature {

        GeoPolygon() : GeoFeature(std::__cxx11::string(), 0) {}
    };

}

#endif //GISL_GEOPOLYGON_H

//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTIPOINT_H
#define GISL_GEOMULTIPOINT_H

#include "geofeature.h"

namespace GisL {

    class GeoMultiPoint : public GeoFeature {

        GeoMultiPoint() : GeoFeature(std::__cxx11::string(), 0) {}
    };

}

#endif //GISL_GEOMULTIPOINT_H

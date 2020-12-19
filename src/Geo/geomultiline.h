//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTILINE_H
#define GISL_GEOMULTILINE_H

#include "geofeature.h"

namespace GisL {

    class GeoMultiLine : public GeoFeature {

        GeoMultiLine() : GeoFeature(std::__cxx11::string(), 0) {}
    };

}

#endif //GISL_GEOMULTILINE_H

//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOLINE_H
#define GISL_GEOLINE_H

#include "geofeature.h"

namespace GisL {

    class GeoLine : public GeoFeature {

        GeoLine() : GeoFeature(std::__cxx11::string(), 0) {}
    };

}

#endif //GISL_GEOLINE_H

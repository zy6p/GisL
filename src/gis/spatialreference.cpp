//
// Created by omega on 14/12/2020.
//

#include "spatialreference.h"

namespace GisL {
    SpatialReference::SpatialReference(OGRSpatialReference *poSRS) {
        pmCRS = poSRS;
    }

    SpatialReference::~SpatialReference() = default;
}
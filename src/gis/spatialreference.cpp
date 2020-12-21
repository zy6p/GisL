//
// Created by omega on 14/12/2020.
//

#include "spatialreference.h"

#include <string>
#include <gdal/ogr_spatialref.h>
#include <gdal/cpl_conv.h>

namespace GisL {
    SpatialReference::SpatialReference(OGRSpatialReference *poSRS) {
        pmCRS = poSRS;
    }

    std::string SpatialReference::toWKT() {
        std::string wkt;
        pmCRS->exportToWkt((char **) wkt.c_str());
        return std::move(wkt);
    }

    SpatialReference::~SpatialReference() = default;
}
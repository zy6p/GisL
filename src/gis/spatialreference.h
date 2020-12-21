//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SPATIALREFERENCE_H
#define GISL_SPATIALREFERENCE_H

#include <string>
#include <gdal/ogr_spatialref.h>

namespace GisL {
    /*!
     * @brief Coordinate Reference System
     */
    class SpatialReference {
    public:
        explicit SpatialReference(OGRSpatialReference *poSRS);

        std::string toWKT();

    private:
        OGRSpatialReference *pmCRS;

        ~SpatialReference();

    };
}

#endif //GISL_SPATIALREFERENCE_H

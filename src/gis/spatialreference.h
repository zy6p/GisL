//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SPATIALREFERENCE_H
#define GISL_SPATIALREFERENCE_H

#include <string>
#include <gdal/ogr_spatialref.h>

#include "../utils/merror.h"

namespace GisL {
    /*!
     * @brief Coordinate Reference System
     */
    class SpatialReference {
    public:
        explicit SpatialReference(OGRSpatialReference &poSRS);

        void toWKT(std::string &outWkt);

        ~SpatialReference();

        bool hasError();

        std::string errorMessage();


    private:
        OGRSpatialReference *pmCRS;

        MError::GisLError mError;
        std::string mErrorMessage;
    };
}

#endif //GISL_SPATIALREFERENCE_H

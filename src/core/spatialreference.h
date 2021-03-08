//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SPATIALREFERENCE_H
#define GISL_SPATIALREFERENCE_H

#include <string>
#include <ogr_spatialref.h>

#include "../utils/gislobject.h"

namespace GisL {
    /*!
     * @brief Coordinate Reference System
     */
    class SpatialReference {
    public:
        explicit SpatialReference( OGRSpatialReference &poSRS );

        void toWKT( std::string &outWkt );

        ~SpatialReference( );


    private:
        OGRSpatialReference *pmCRS;

    };
}

#endif //GISL_SPATIALREFERENCE_H

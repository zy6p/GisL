//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SPATIALREFERENCE_H
#define GISL_SPATIALREFERENCE_H

#include <gdal/ogrsf_frmts.h>

namespace GisL {
    /*!
     * @brief Coordinate Reference System
     */
    class SpatialReference {
    public:
        explicit SpatialReference(OGRSpatialReference *poSRS);

    private:
        OGRSpatialReference *pmCRS;

        ~SpatialReference();

    };
}

#endif //GISL_SPATIALREFERENCE_H

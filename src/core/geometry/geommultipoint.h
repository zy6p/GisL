//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTIPOINT_H
#define GISL_GEOMMULTIPOINT_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomMultiPoint : virtual public AbstractGeometry, virtual public OGRMultiPoint {
    public:
        explicit GeomMultiPoint( );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomMultiPoint( ) override;

    private:

    };

}

#endif //GISL_GEOMMULTIPOINT_H

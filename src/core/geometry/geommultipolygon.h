//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTIPOLYGON_H
#define GISL_GEOMMULTIPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomMultiPolygon : virtual public AbstractGeometry, virtual public OGRMultiPolygon {
    public:
        explicit GeomMultiPolygon( );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomMultiPolygon( ) override;

    private:


    };

}

#endif //GISL_GEOMMULTIPOLYGON_H


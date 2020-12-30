//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTILINE_H
#define GISL_GEOMMULTILINE_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeoMultiLine : virtual public AbstractGeometry, virtual public OGRMultiLineString {
    public:
        explicit GeoMultiLine( );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeoMultiLine( ) override;

    private:

    };

}

#endif //GISL_GEOMMULTILINE_H

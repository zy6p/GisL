//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMLINE_H
#define GISL_GEOMLINE_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomLine : virtual public AbstractGeometry, virtual public OGRLineString {
    public:
        explicit GeomLine( );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomLine( ) override;

    private:

    };

}

#endif //GISL_GEOMLINE_H

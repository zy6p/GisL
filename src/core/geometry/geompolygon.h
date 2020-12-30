//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMPOLYGON_H
#define GISL_GEOMPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomPolygon : public AbstractGeometry {
    public:
        explicit GeomPolygon( OGRPolygon &ogrPolygon );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomPolygon( );

        OGRGeometry *getGeometry( ) const override;

    private:
        OGRPolygon *pmPolygon;

    };

}

#endif //GISL_GEOMPOLYGON_H

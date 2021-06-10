//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMPOLYGON_H
#define GISL_GEOMPOLYGON_H

#include <ogr_geometry.h>

#include "abstractgeometry.h"
#include "../coordinatetransform.h"

namespace gisl {

    class GeomPolygon : public AbstractGeometry {
    public:
        explicit GeomPolygon( OGRPolygon &ogrPolygon );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( PainterFactory &p ) override;

        bool isEmpty( ) const override;

        ~GeomPolygon( );

        OGRGeometry *getGeometry( ) const override;

        ExchangePolygon *toTransPolygon( );

    private:
        OGRPolygon *pmPolygon;

    };

}

#endif //GISL_GEOMPOLYGON_H

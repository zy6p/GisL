//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMPOINT_H
#define GISL_GEOMPOINT_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"
#include "../../utils/ptroperate.h"

namespace GisL {
    class GeomPoint : virtual public AbstractGeometry, virtual public OGRPoint {
    public:
        explicit GeomPoint( );

        ~GeomPoint( ) override;

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

    private:

    };

}

#endif //GISL_GEOMPOINT_H

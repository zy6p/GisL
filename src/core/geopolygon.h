//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOPOLYGON_H
#define GISL_GEOPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"

namespace GisL {

    class GeoPolygon : public Geometry {
    public:
        explicit GeoPolygon( OGRGeometry &poGeometry );

        void paint( );

        void paint( Symbolizer &symbol );

        ~GeoPolygon( );

    private:
        OGRPolygon *pmPolygon;

    };

}

#endif //GISL_GEOPOLYGON_H

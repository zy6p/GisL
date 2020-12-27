//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMULTIPOLYGON_H
#define GISL_GEOMULTIPOLYGON_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"
#include "geopolygon.h"
#include "../gui/sld.h"

namespace GisL {

    class GeoMultiPolygon : public Geometry {
    public:
        explicit GeoMultiPolygon( OGRGeometry &poGeometry );

        void paint( );

        void paint( Sld::Symbol &symbol );

        static GeoPolygon **getEachPolygon( const GeoMultiPolygon &poMultiPolygon, int &polygonCount );

        ~GeoMultiPolygon( );

    private:
        OGRMultiPolygon *pmMultiPolygon;

        int polygonCount;

        GeoPolygon **pmPolygon;

    };

}

#endif //GISL_GEOMULTIPOLYGON_H


//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMLINESTRING_H
#define GISL_GEOMLINESTRING_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"

namespace GisL {

    class GeomLineString : virtual public AbstractGeometry, virtual public OGRLineString {
    public:
        explicit GeomLineString( OGRLineString &ogrLineString );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        ~GeomLineString( ) override;

        OGRGeometry *getGeometry( ) const override;

    private:
        OGRLineString *pmLineString;
    };

}

#endif //GISL_GEOMLINESTRING_H

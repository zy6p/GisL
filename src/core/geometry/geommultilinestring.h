//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMMULTILINESTRING_H
#define GISL_GEOMMULTILINESTRING_H

#include <ogr_geometry.h>

#include "abstractgeometry.h"

namespace gisl {

    class GeomMultiLineString : public AbstractGeometry {
    public:
        explicit GeomMultiLineString( OGRMultiLineString &ogrMultiLineString );

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( PainterFactory &p ) override;

        bool isEmpty( ) const override;

        ~GeomMultiLineString( );

        OGRGeometry *getGeometry( ) const override;

    private:
        OGRMultiLineString *pmMultiLineString;

    };

}

#endif //GISL_GEOMMULTILINESTRING_H

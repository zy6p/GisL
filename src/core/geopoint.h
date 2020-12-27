//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOPOINT_H
#define GISL_GEOPOINT_H

#include <gdal/ogr_geometry.h>

#include "geometry.h"

namespace GisL {

    class GeoPoint : public Geometry {
    public:
        explicit GeoPoint( OGRGeometry &poGeometry );

//        GeoPoint(double x, double y);

//        GeoPoint(double x, double y, double z);

        ~GeoPoint( );

        [[nodiscard]] double getX( ) const;

        void setX( double x );

        [[nodiscard]] double getY( ) const;

        void setY( double y );

        [[nodiscard]] double getZ( ) const;

        void setZ( double z );

    private:
        OGRPoint pmPoint;
        double x;
        double y;
        double z;

    };

}

#endif //GISL_GEOPOINT_H

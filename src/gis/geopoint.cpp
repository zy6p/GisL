//
// Created by omega on 14/12/2020.
//

#include "geopoint.h"

#include <gdal/ogr_geometry.h>

namespace GisL {

//    GeoPoint::GeoPoint() : x(0), y(0), z(0) {}

//    GeoPoint::GeoPoint(double x, double y) : x(x), y(y), z(0) {}

//    GeoPoint::GeoPoint(double x, double y, double z) : x(x), y(y), z(z) {}

    double GeoPoint::getY( ) const {
        return y;
    }

    void GeoPoint::setY( double y ) {
        GeoPoint::y = y;
    }

    double GeoPoint::getX( ) const {
        return x;
    }

    void GeoPoint::setX( double x ) {
        GeoPoint::x = x;
    }

    double GeoPoint::getZ( ) const {
        return z;
    }

    void GeoPoint::setZ( double z ) {
        GeoPoint::z = z;
    }

    GeoPoint::GeoPoint( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {

//        pmGeometry = OGRGeometryFactory::forceTo(pmGeometry, OGRwkbGeometryType::wkbPoint, nullptr);
        pmPoint = *pmGeometry->toPoint();

        x = pmPoint.getX();
        y = pmPoint.getY();
        if ( pmPoint.Is3D()) {
            z = pmPoint.getZ();
        } else {
            z = 0.0;
        }


    }

    void initRender( ) {

    }

    GeoPoint::~GeoPoint( ) = default;
}
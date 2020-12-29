//
// Created by omega on 14/12/2020.
//

#include "geompoint.h"

#include <gdal/ogr_geometry.h>

namespace GisL {

    GeomPoint::GeomPoint( ) {

        mWkbType = Point;
    }

    Rectangle *GeomPoint::boundary( ) const {
        Rectangle *p;
        OGRPoint::getEnvelope( p );
        return p;
    }

    void GeomPoint::clear( ) {
        OGRPoint::empty();
    }

    void GeomPoint::draw( ) {
        //todo how to do it?
    }

    bool GeomPoint::isEmpty( ) const {
        return OGRPoint::IsEmpty();
    }

    GeomPoint::~GeomPoint( ) {
        GeomPoint::clear();
    };
}
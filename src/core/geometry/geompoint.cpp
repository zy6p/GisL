//
// Created by omega on 14/12/2020.
//

#include "geompoint.h"

#include <gdal/ogr_geometry.h>

namespace GisL {

    GeomPoint::GeomPoint( OGRPoint &ogrPoint ) : AbstractGeometry( ogrPoint ) {
        mWkbType = Point;
        pmPoint = &ogrPoint;
    }

    Rectangle *GeomPoint::boundary( ) const {
        Rectangle *p;
        pmPoint->getEnvelope( p );
        return p;
    }

    void GeomPoint::clear( ) {
        pmPoint->empty();
    }

    void GeomPoint::draw( ) {
        //todo how to do it?
    }

    bool GeomPoint::isEmpty( ) const {
        return pmPoint->IsEmpty();
    }

    GeomPoint::~GeomPoint( ) {
        GeomPoint::clear();
    }

    OGRGeometry *GeomPoint::getGeometry( ) const {
        return pmPoint;
    }
}
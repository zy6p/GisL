//
// Created by omega on 14/12/2020.
//

#include "geompoint.h"

#include <ogr_geometry.h>

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

    bool GeomPoint::isEmpty( ) const {
        return pmPoint->IsEmpty();
    }

    GeomPoint::~GeomPoint( ) {
        GeomPoint::clear();
    }

    OGRGeometry *GeomPoint::getGeometry( ) const {
        return pmPoint;
    }

    void GeomPoint::draw( PainterFactory &p ) {
        p.drawPoint( *toPointXY());
    }

    ExchangePointXY *GeomPoint::toPointXY( ) {
        return new ExchangePointXY( pmPoint->getX(), pmPoint->getY(), nullptr );
    };
}
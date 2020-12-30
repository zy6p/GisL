//
// Created by omega on 14/12/2020.
//

#include "geompolygon.h"

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomPolygon::GeomPolygon( OGRPolygon &ogrPolygon ) {
        mWkbType = AbstractGeometry::WkbType::Polygon;
        pmPolygon = &ogrPolygon;
    }


    GeomPolygon::~GeomPolygon( ) {
        GeomPolygon::clear();
    }

    Rectangle *GeomPolygon::boundary( ) const {
        Rectangle *p;
        pmPolygon->getEnvelope( p );
        return p;
    }

    void GeomPolygon::clear( ) {
        pmPolygon->empty();
    }

    void GeomPolygon::draw( ) {
        //todo
    }

    OGRGeometry *GeomPolygon::getGeometry( ) const {
        return pmPolygon;
    }

    bool GeomPolygon::isEmpty( ) const {
        return pmPolygon->IsEmpty();
    }

}
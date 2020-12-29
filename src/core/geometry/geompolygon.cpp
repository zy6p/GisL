//
// Created by omega on 14/12/2020.
//

#include "geompolygon.h"

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomPolygon::GeomPolygon( ) {
        mWkbType = AbstractGeometry::WkbType::Polygon;
    }


    GeomPolygon::~GeomPolygon( ) {
        GeomPolygon::clear();
    }

    Rectangle *GeomPolygon::boundary( ) const {
        Rectangle *p;
        OGRPolygon::getEnvelope( p );
        return p;
    }

    void GeomPolygon::clear( ) {
        OGRPolygon::empty();
    }

    void GeomPolygon::draw( ) {
        //todo
    }

    bool GeomPolygon::isEmpty( ) const {
        return OGRPolygon::IsEmpty();
    }

}
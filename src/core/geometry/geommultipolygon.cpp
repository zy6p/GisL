//
// Created by omega on 14/12/2020.
//

#include "geommultipolygon.h"

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomMultiPolygon::GeomMultiPolygon( ) {
        mWkbType = AbstractGeometry::WkbType::MultiPolygon;
    }


    GeomMultiPolygon::~GeomMultiPolygon( ) {
        GeomMultiPolygon::clear();
    }

    Rectangle *GeomMultiPolygon::boundary( ) const {
        Rectangle *p;
        OGRMultiPolygon::getEnvelope( p );
        return p;
    }

    void GeomMultiPolygon::clear( ) {
        OGRMultiPolygon::empty();
    }

    void GeomMultiPolygon::draw( ) {
        //todo
    }

    bool GeomMultiPolygon::isEmpty( ) const {
        return OGRMultiPolygon::IsEmpty();
    }
}
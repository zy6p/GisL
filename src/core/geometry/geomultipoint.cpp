//
// Created by omega on 14/12/2020.
//

#include "geomultipoint.h"

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomMultiPoint::GeomMultiPoint( ) {
        mWkbType = AbstractGeometry::WkbType::MultiPoint;
    }

    GeomMultiPoint::~GeomMultiPoint( ) {
        GeomMultiPoint::clear();
    }

    Rectangle *GeomMultiPoint::boundary( ) const {
        Rectangle *p;
        OGRMultiPoint::getEnvelope( p );
        return p;
    }

    void GeomMultiPoint::clear( ) {
        OGRMultiPoint::empty();
    }

    void GeomMultiPoint::draw( ) {
        //todo
    }

    bool GeomMultiPoint::isEmpty( ) const {
        return OGRMultiPoint::IsEmpty();
    }
}
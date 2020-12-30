//
// Created by omega on 14/12/2020.
//

#include "geommultilinestring.h"

#include "rectangle.h"
#include "../../utils/ptroperate.h"

namespace GisL {

    GeomMultiLineString::GeomMultiLineString( OGRMultiLineString &ogrMultiLineString ) {
        mWkbType = AbstractGeometry::WkbType::MultiLineString;
        pmMultiLineString = &ogrMultiLineString;
    }

    GeomMultiLineString::~GeomMultiLineString( ) {
        GeomMultiLineString::clear();
    }

    void GeomMultiLineString::clear( ) {
        pmMultiLineString->empty();
    }

    void GeomMultiLineString::draw( ) {
        //todo
    }

    bool GeomMultiLineString::isEmpty( ) const {
        return pmMultiLineString->IsEmpty();
    }

    Rectangle *GeomMultiLineString::boundary( ) const {
        Rectangle *p;
        pmMultiLineString->getEnvelope( p );
        return p;
    }

    OGRGeometry *GeomMultiLineString::getGeometry( ) const {
        return pmMultiLineString;
    }
}
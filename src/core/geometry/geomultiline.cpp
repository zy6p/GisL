//
// Created by omega on 14/12/2020.
//

#include "geomultiline.h"

#include "rectangle.h"
#include "../../utils/ptroperate.h"

namespace GisL {

    GeoMultiLine::GeoMultiLine( ) {
        mWkbType = AbstractGeometry::WkbType::MultiLineString;
    }

    GeoMultiLine::~GeoMultiLine( ) {
        GeoMultiLine::clear();
    }

    void GeoMultiLine::clear( ) {
        OGRMultiLineString::empty();
    }

    void GeoMultiLine::draw( ) {
        //todo
    }

    bool GeoMultiLine::isEmpty( ) const {
        return OGRMultiLineString::IsEmpty();
    }

    Rectangle *GeoMultiLine::boundary( ) const {
        Rectangle *p;
        OGRMultiLineString::getEnvelope( p );
        return p;
    }
}
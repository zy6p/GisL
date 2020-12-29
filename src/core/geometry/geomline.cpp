//
// Created by omega on 14/12/2020.
//

#include "geomline.h"

#include <gdal/ogr_geometry.h>

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomLine::GeomLine( ) {
        mWkbType = AbstractGeometry::WkbType::LineString;
    }

    Rectangle *GeomLine::boundary( ) const {
        Rectangle *p;
        OGRLineString::getEnvelope( p );
        return p;
    }

    void GeomLine::clear( ) {
        OGRLineString::empty();
    }

    void GeomLine::draw( ) {
        //todo
    }

    bool GeomLine::isEmpty( ) const {
        return OGRLineString::IsEmpty();
    }

    GeomLine::~GeomLine( ) {
        GeomLine::clear();
    }

}
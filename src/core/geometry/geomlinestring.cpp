//
// Created by omega on 14/12/2020.
//

#include "geomlinestring.h"

#include <gdal/ogr_geometry.h>

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomLineString::GeomLineString( OGRLineString &ogrLineString ) {
        mWkbType = AbstractGeometry::WkbType::LineString;
        pmLineString = &ogrLineString;
    }

    Rectangle *GeomLineString::boundary( ) const {
        Rectangle *p;
        pmLineString->getEnvelope( p );
        return p;
    }

    void GeomLineString::clear( ) {
        pmLineString->empty();
    }

    void GeomLineString::draw( ) {
        //todo
    }

    bool GeomLineString::isEmpty( ) const {
        return pmLineString->IsEmpty();
    }

    GeomLineString::~GeomLineString( ) {
        GeomLineString::clear();
    }

    OGRGeometry *GeomLineString::getGeometry( ) const {
        return pmLineString;
    }

}
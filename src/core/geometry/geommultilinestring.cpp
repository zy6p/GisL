//
// Created by omega on 14/12/2020.
//

#include "geommultilinestring.h"

#include "rectangle.h"
#include "../../utils/ptroperate.h"
#include "geomlinestring.h"

namespace gisl {

    GeomMultiLineString::GeomMultiLineString( OGRMultiLineString &ogrMultiLineString ) : AbstractGeometry(
            ogrMultiLineString ) {
        mWkbType = AbstractGeometry::WkbType::MultiLineString;
        pmMultiLineString = &ogrMultiLineString;
    }

    GeomMultiLineString::~GeomMultiLineString( ) {
        GeomMultiLineString::clear();
    }

    void GeomMultiLineString::clear( ) {
        pmMultiLineString->empty();
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

    void GeomMultiLineString::draw( PainterFactory &p ) {
        for ( auto line : pmMultiLineString ) {
            auto mLine = new GeomLineString( *line );
            mLine->draw( p );
        }
    }

}
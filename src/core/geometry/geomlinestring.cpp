//
// Created by omega on 14/12/2020.
//

#include "geomlinestring.h"

#include <ogr_geometry.h>

#include "../../utils/ptroperate.h"

namespace gisl {

    GeomLineString::GeomLineString( OGRLineString &ogrLineString ) : AbstractGeometry( ogrLineString ) {
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

    bool GeomLineString::isEmpty( ) const {
        return pmLineString->IsEmpty();
    }

    GeomLineString::~GeomLineString( ) {
        GeomLineString::clear();
    }

    OGRGeometry *GeomLineString::getGeometry( ) const {
        return pmLineString;
    }

    void GeomLineString::draw( PainterFactory &p ) {
        p.drawLine( *toExchangeLine());
    }

    ExchangeLine *GeomLineString::toExchangeLine( ) {
        auto p = new ExchangeLine;
        for ( const auto &point : pmLineString ) {
            p->append( point.getX(), point.getY());
        }
        return p;
    }
}
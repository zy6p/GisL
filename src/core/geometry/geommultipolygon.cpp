//
// Created by omega on 14/12/2020.
//

#include "geommultipolygon.h"

#include "../../gui/symbolizer/polygonsymbolizer.h"
#include "../../utils/ptroperate.h"

namespace gisl {

    GeomMultiPolygon::GeomMultiPolygon( OGRMultiPolygon &ogrMultiPolygon ) : AbstractGeometry( ogrMultiPolygon ) {
        mWkbType = AbstractGeometry::WkbType::MultiPolygon;
        pmMultiPolygon = &ogrMultiPolygon;
    }


    GeomMultiPolygon::~GeomMultiPolygon( ) {
        GeomMultiPolygon::clear();
    }

    Rectangle *GeomMultiPolygon::boundary( ) const {
//        Rectangle *p;
//        pmMultiPolygon->getEnvelope( p );
//        return p;
        auto *p = new OGREnvelope;
        pmMultiPolygon->getEnvelope( p );
        return new Rectangle( *p );
    }

    void GeomMultiPolygon::clear( ) {
        pmMultiPolygon->empty();
    }

    bool GeomMultiPolygon::isEmpty( ) const {
        return pmMultiPolygon->IsEmpty();
    }

    OGRGeometry *GeomMultiPolygon::getGeometry( ) const {
        return pmMultiPolygon;
    }

    void GeomMultiPolygon::draw( PainterFactory &p ) {
        for ( auto polygon : pmMultiPolygon ) {
            for ( auto line : polygon ) {
                p.drawLinearRing( new ExchangeLinearRing( line ), featureName );
            }
        }
    }
}
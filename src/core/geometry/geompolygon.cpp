//
// Created by omega on 14/12/2020.
//

#include "geompolygon.h"

#include "../../utils/ptroperate.h"

namespace GisL {

    GeomPolygon::GeomPolygon( OGRPolygon &ogrPolygon ) : AbstractGeometry( ogrPolygon ) {
        mWkbType = AbstractGeometry::WkbType::Polygon;
        pmPolygon = &ogrPolygon;
    }


    GeomPolygon::~GeomPolygon( ) {
        GeomPolygon::clear();
    }

    Rectangle *GeomPolygon::boundary( ) const {
        Rectangle *p;
        pmPolygon->getEnvelope( p );
        return p;
    }

    void GeomPolygon::clear( ) {
        pmPolygon->empty();
    }

    void GeomPolygon::draw( PainterFactory &p ) {
//        p.drawPolygon( *this->toTransPolygon());
        for ( auto ring : pmPolygon ) {
            p.drawLinearRing( new ExchangeLinearRing( ring ));
        }
    }

    OGRGeometry *GeomPolygon::getGeometry( ) const {
        return pmPolygon;
    }

    bool GeomPolygon::isEmpty( ) const {
        return pmPolygon->IsEmpty();
    }

    ExchangePolygon *GeomPolygon::toTransPolygon( ) {
        auto *polygon = new ExchangePolygon;
        for ( auto lineString : pmPolygon ) {
            auto *line = new ExchangeLine;
            for ( const auto &point : lineString ) {
                line->append( point.getX(), point.getY());
            }
            polygon->append( line );
        }
        return polygon;
    }

}
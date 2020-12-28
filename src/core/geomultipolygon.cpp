//
// Created by omega on 14/12/2020.
//

#include "geomultipolygon.h"

#include "../gui/symbolizer/polygonsymbolizer.h"
#include "../utils/ptroperate.h"

namespace GisL {

    GeoMultiPolygon::GeoMultiPolygon( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {
        pmMultiPolygon = dynamic_cast<OGRMultiPolygon *>(pmGeometry);
        polygonCount = 0;
        pmPolygon = getEachPolygon( *this, polygonCount );
        pmSymbolizer = nullptr;
    }

    GeoPolygon **GeoMultiPolygon::getEachPolygon( const GeoMultiPolygon &poMultiPolygon, int &polygonCount ) {
        OGRPolygon **pOgrPolygon = poMultiPolygon.pmMultiPolygon->begin();
        polygonCount = 0;
        for ( pOgrPolygon; pOgrPolygon != poMultiPolygon.pmMultiPolygon->end(); ++pOgrPolygon ) {
            polygonCount++;
        }

        auto **rst = new GeoPolygon *[polygonCount];
        for ( int i = 0; i < polygonCount; ++i ) {
            rst[i] = new GeoPolygon( *( *pOgrPolygon - i ));
        }
        return rst;
    }

    void GeoMultiPolygon::paint( ) {
        if ( nullptr == pmSymbolizer ) {
            pmPolygonSymbolizer->rand();
            pmSymbolizer = pmPolygonSymbolizer;
        }
        for ( int i = 0; i < polygonCount; ++i ) {
            pmPolygon[i]->paint( *pmPolygonSymbolizer );
        }
    }

    void GeoMultiPolygon::paint( Symbolizer &symbol ) {
        setSymbol( symbol );
        paint();
    }

    GeoMultiPolygon::~GeoMultiPolygon( ) {
        PtrOperate::clear( pmPolygon, polygonCount );
    }
}
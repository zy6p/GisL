//
// Created by omega on 14/12/2020.
//

#include "geopolygon.h"

#include "../gui/symbolizer/polygonsymbolizer.h"
#include "../utils/ptroperate.h"

namespace GisL {

    GeoPolygon::GeoPolygon( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {
        pmPolygon = dynamic_cast<OGRPolygon *>(pmGeometry);
    }

    void GeoPolygon::paint( ) {
        if ( nullptr == pmSymbolizer ) {
            pmSymbolizer = new PolygonSymbolizer;
            pmSymbolizer->rand();
        }
        //TODO: paint symbol using opengl

    }

    void GeoPolygon::paint( Symbolizer &symbol ) {
        setSymbol( symbol );
        paint();
    }

    GeoPolygon::~GeoPolygon( ) {
        PtrOperate::clear( pmPolygon );
    }

}
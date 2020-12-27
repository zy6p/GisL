//
// Created by omega on 14/12/2020.
//

#include "geopolygon.h"

#include "../utils/ptroperate.h"

namespace GisL {

    GeoPolygon::GeoPolygon( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {
        pmPolygon = dynamic_cast<OGRPolygon *>(pmGeometry);
    }

    void GeoPolygon::paint( ) {
        if ( nullptr == pmSymbol ) {
            pmSymbol = new Sld::Symbol( true );
        }
        //TODO: paint symbol using opengl

    }

    void GeoPolygon::paint( Sld::Symbol &symbol ) {
        setSymbol( symbol );
        paint();
    }

    GeoPolygon::~GeoPolygon( ) {
        PtrOperate::clear( pmPolygon );
    }

}
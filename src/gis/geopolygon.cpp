//
// Created by omega on 14/12/2020.
//

#include "geopolygon.h"

#include "../utils/ptroperate.h"

namespace GisL {

    GeoPolygon::GeoPolygon( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {
        pmPolygon = dynamic_cast<OGRPolygon *>(pmGeometry);
    }

    void GeoPolygon::plot( ) {
        if ( nullptr == pmSymbol ) {
            pmSymbol = new Sld::Symbol( true );
        }
        //TODO: plot symbol using opengl

    }

    void GeoPolygon::plot( Sld::Symbol &symbol ) {
        setSymbol( symbol );
        plot();
    }

    GeoPolygon::~GeoPolygon( ) {
        PtrOperate::clear( pmPolygon );
    }

}
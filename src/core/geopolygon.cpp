//
// Created by omega on 14/12/2020.
//

#include "geopolygon.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

#include "../gui/symbolizer/polygonsymbolizer.h"
#include "../utils/ptroperate.h"

namespace GisL {

    GeoPolygon::GeoPolygon( OGRGeometry &poGeometry ) : Geometry( poGeometry ) {
        pmPolygonSymbolizer = nullptr;
        pmPolygon = dynamic_cast<OGRPolygon *>(pmGeometry);
    }

    void GeoPolygon::paint( ) {
        if ( nullptr == pmPolygonSymbolizer ) {
            pmPolygonSymbolizer->rand();
        }
        //TODO: paint symbol using opengl
//        glBegin(GL_POLYGON);
//        glColor3f(pmPolygonSymbolizer->polygonFillColor.redF(), pmPolygonSymbolizer->polygonFillColor.greenF(), pmPolygonSymbolizer->polygonFillColor.blueF());
//        for ( auto pRing : pmPolygon ) {
//            for ( const auto& point : pRing ) {
//                glVertex2f( point.getX(), point.getY() );
//            }
//        }
//        glEnd();
    }

    void GeoPolygon::paint( PolygonSymbolizer &symbol ) {
        setSymbol( symbol );
        paint();
    }

    GeoPolygon::~GeoPolygon( ) {
        PtrOperate::clear( pmPolygon );
    }

}
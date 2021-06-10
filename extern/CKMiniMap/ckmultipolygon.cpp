#include "ckmultipolygon.h"

CKMultiPolygon::CKMultiPolygon( ) {
    polygons = 0x00;
    plg_size = 0;
}

CKMultiPolygon::CKMultiPolygon( const QJsonArray &mplg ) {
    plg_size = mplg.size();
    polygons = new CKPolygon *[mplg.size()];

    for ( int i = 0; i < mplg.size(); i++ ) {
        polygons[i] = new CKPolygon( mplg[i].toArray());
    }
}

CKMultiPolygon::~CKMultiPolygon( ) {
    if ( polygons != 0x00 ) {
        for ( int i = 0; i < plg_size; i++ ) {
            if ( polygons[i] != 0x00 ) {
                delete polygons[i];
                polygons[i] = 0x00;
            }
        }
        delete[] polygons;
        polygons = 0x00;
    }
}

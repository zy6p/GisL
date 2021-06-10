#include "ckpolygon.h"

CKPolygon::CKPolygon( ) {
    pSegs = 0x00;
    seg_size = 0;
}

CKPolygon::CKPolygon( const QJsonArray &plg ) {
    seg_size = plg.size();
    pSegs = new CKPolygonSegment *[seg_size];
    for ( int i = 0; i < seg_size; i++ ) {
        pSegs[i] = new CKPolygonSegment( plg[i].toArray());
    }
}

CKPolygon::~CKPolygon( ) {
    if ( pSegs != 0x00 ) {
        for ( int i = 0; i < seg_size; i++ ) {
            if ( pSegs[i] != 0x00 ) {
                delete pSegs[i];
                pSegs[i] = 0x00;
            }
        }
        delete[] pSegs;
        pSegs = 0x00;
    }
}

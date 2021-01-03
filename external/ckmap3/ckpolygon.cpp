#include "ckpolygon.h"
#include "ckpolygonsymbolizer.h"
#include <QOpenGLFunctions_3_2_Core>
#include <GL/glu.h>

CKPolygon::CKPolygon( ) {
    pSegs = 0x00;
    seg_size = 0;
    envelop[0] = 999999999;
    envelop[1] = 999999999;
    envelop[2] = -999999999;
    envelop[3] = -999999999;
}

CKPolygon::CKPolygon( const QJsonArray &plg ) {
    seg_size = plg.size();
    pSegs = new CKLinearRing *[seg_size];
    for ( int i = 0; i < seg_size; i++ ) {
        pSegs[i] = new CKLinearRing( plg[i].toArray());
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

double *CKPolygon::getEnvelop( ) {
    double *te = 0x00;
    for ( int i = 0; i < this->seg_size; i++ ) {
        te = pSegs[i]->getEnvelop();
        envelop[0] = envelop[0] < te[0] ? envelop[0] : te[0];
        envelop[1] = envelop[1] < te[1] ? envelop[1] : te[1];
        envelop[2] = envelop[2] > te[2] ? envelop[2] : te[2];
        envelop[3] = envelop[3] > te[3] ? envelop[3] : te[3];
    }
    return envelop;
}

void CKPolygon::draw( CKSymbolizer *pSymb ) {
    for ( int i = 0; i < this->seg_size; i++ ) {
        this->pSegs[i]->draw( pSymb );
    }


}

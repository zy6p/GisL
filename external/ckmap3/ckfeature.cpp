#include "ckfeature.h"
#include "ckmultipolygon.h"
#include <QDebug>

CKFeature::CKFeature( ) {
    pGeom = 0X00;
}

CKFeature::CKFeature( const QJsonObject &feat ) {
    QJsonObject prop = feat["properties"].toObject();
    QJsonValue geom = feat["geometry"];

    //properties solution
    QJsonObject::const_iterator it = prop.begin();
    CKFieldDef *pfd = 0x00;
    for ( ; it != prop.end(); ++it ) {
        pfd = new CKFieldDef( it.key(), it.value());
        field_defs.push_back( pfd );
    }

    //geometry solution
    if ( geom["type"].toString().compare( "MultiPolygon" ) == 0 ) {
        this->pGeom = new CKMultiPolygon( geom["coordinates"].toArray());
    }
}

CKFeature::~CKFeature( ) {
    if ( pGeom != 0x00 ) {
        delete pGeom;
        pGeom = 0x00;
    }
}

bool CKFeature::equalTo( QString fn, QString fv ) {
    for ( int i = 0; i < field_defs.size(); i++ ) {
        if ( field_defs[i]->getField_name() == fn && field_defs[i]->getStrValue() == fv )
            return true;
    }
    return false;
}

double *CKFeature::getEnvelop( ) const {
    return pGeom->getEnvelop();
}

void CKFeature::draw( CKSymbolizer *pSymb ) {
    if ( pGeom != 0x00 )
        pGeom->draw( pSymb );
}

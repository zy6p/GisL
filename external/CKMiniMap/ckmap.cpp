#include "ckmap.h"
#include "string.h"
#include <QJsonDocument>
#include <qfile.h>
#include <iostream>
#include <qjsonarray.h>
#include "ckfeature.h"


using namespace std;

CKMap::CKMap( ) {

}

void CKMap::loadSLD( char *path ) {
    this->loadGeoJSON( path );
}

void CKMap::loadGeoJSON( char *path ) {
    if ( path == 0x00 || strlen( path ) == 0 )
        return;
    QFile file( path );
    if ( !file.open( QIODevice::ReadOnly | QIODevice::Text )) {
        return;//file open error
    }

    QJsonDocument doc = QJsonDocument::fromJson( file.readAll());
    QJsonArray feats;
    if ( !doc[ "features" ].isNull() && doc[ "features" ].isArray())
        feats = doc[ "features" ].toArray();

    for ( int i = 0; i < feats.size(); i++ ) {
        if ( feats[ i ].isObject() && !feats[ i ].isNull()) {
            QJsonValue fv = feats[ i ];
            if ( fv[ "type" ].toString().compare( "Feature" ) == 0 )
                CKFeature *pF = new CKFeature( feats[ i ].toObject());
        }

    }
}

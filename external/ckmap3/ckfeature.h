#ifndef CKFEATURE_H
#define CKFEATURE_H


#include <QJsonObject>
#include <vector>
#include "ckfielddef.h"
#include "cksymbolizer.h"
#include "ckgeometry.h"

using namespace std;

class CKFeature {
public:
    CKFeature( );

    CKFeature( const QJsonObject &feature );

    ~CKFeature( );

    bool equalTo( QString fn, QString fv );

    double *getEnvelop( ) const;

    void draw( CKSymbolizer * );

private:
    CKGeometry *pGeom;
    vector<CKFieldDef *> field_defs;
};

#endif // CKFEATURE_H

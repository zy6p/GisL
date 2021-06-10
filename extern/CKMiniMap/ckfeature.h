#ifndef CKFEATURE_H
#define CKFEATURE_H

#include "ckgeometry.h"
#include <QJsonObject>

class CKFeature {
public:
    CKFeature( );

    CKFeature( const QJsonObject &feature );

    ~CKFeature( );

private:
    CKGeometry *pGeom;
};

#endif // CKFEATURE_H

#ifndef CKGEOMETRY_H
#define CKGEOMETRY_H

#include "cksymbolizer.h"

class CKGeometry {
public:
    CKGeometry( );

    CKGeometry( int type );

    virtual ~CKGeometry( );

    virtual double *getEnvelop( ) = 0;

    virtual void draw( CKSymbolizer *pSymb ) = 0;

protected:
    int geo_type;
    double envelop[4];
};

#endif // CKGEOMETRY_H

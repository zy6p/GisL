#ifndef CKPOINT_H
#define CKPOINT_H

#include "ckgeometry.h"

class CKPoint : public CKGeometry {
public:
    CKPoint( );

    CKPoint( double, double );

    virtual ~CKPoint( );

private:
    double x, y, m;

    // CKGeometry interface
public:
    double *getEnvelop( ) override;

    double GetX( );

    double GetY( );

    // CKGeometry interface
public:
    void draw( CKSymbolizer *pSymb ) override;
};

#endif // CKPOINT_H

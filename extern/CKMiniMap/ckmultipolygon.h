#ifndef CKMULTIPOLYGON_H
#define CKMULTIPOLYGON_H

#include "ckgeometry.h"
#include "ckpolygon.h"
#include <QJsonArray>

class CKMultiPolygon : public CKGeometry {
public:
    CKMultiPolygon( );

    CKMultiPolygon( const QJsonArray &mplg );

    ~CKMultiPolygon( );

private:
    CKPolygon **polygons;
    int plg_size;
};

#endif // CKMULTIPOLYGON_H

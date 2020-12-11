#ifndef GEOPOLYGON_H
#define GEOPOLYGON_H

#include <QList>
#include "GeoPoint.h"
#include <qrect.h>

class GeoPolygon : public GeoGeometry {
public:
    GeoPolygon();

    ~GeoPolygon();

    void addPoint(GeoPoint *point);

    GeoPoint *getPointAt(int idx);

    GeoPoint *removeAt(int idx);

    QList<GeoPoint *> removeAll();

    int size();

    QRectF getRect();

private:
    QList<GeoPoint *> pts;
};

#endif // GEOPOLYGON_H

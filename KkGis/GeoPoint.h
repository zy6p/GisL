#ifndef GEOPOINT_H
#define GEOPOINT_H

#include "GeoGeometry.h"
#include <qrect.h>
#include "GeoFeature.h"

class GeoPoint : public GeoGeometry {
public:
    GeoPoint();

    GeoPoint(float xf, float yf);

    GeoPoint(QPointF point);

    ~GeoPoint();

    double getXf();

    void setXf(double x);

    double getYf();

    void setYf(double y);

    int getXd();

    void setXd(int x);

    int getYd();

    void setYd(int y);

    void setXYf(double x, double y);

    QRectF getRect();

    int size();

    double disToPoint(GeoPoint *pt);

    double nearestDisToPoints(QList<GeoPoint *> pts);

    GeoPoint *nearestPointToPoints(QList<GeoPoint *> pts, float threshole);

private:
    double x;
    double y;
};

#endif // GEOPOINT_H

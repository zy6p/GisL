#ifndef GEOOBJECT_H
#define GEOOBJECT_H

#include <qrect.h>

class GeoGeometry {
public:
    GeoGeometry();

    ~GeoGeometry();

    void setType(int t);

    int getType();

    virtual QRectF getRect() = 0;

    virtual int size() = 0;

protected:
    int type;

private:

};

#endif // GEOOBJECT_H

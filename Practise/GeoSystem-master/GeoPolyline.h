#pragma once

#include "GeoObject.h"
#include <qpolygon.h>

class CGeoPolyline :
        public CGeoObject {
public:
    CGeoPolyline(void);

    virtual ~CGeoPolyline(void);

    QPolygonF pts;

    void addPoint(QPointF pt);

    void paint(QPainter *paint);

    float *getVert(float *vert, int *count);

    float *getVert2(float *vert);

    QRectF getScope();

};


#pragma once

#include "geoobject.h"
#include <qlist.h>
#include <qpolygon.h>

class CGeoPolygon :
        public CGeoObject {
public:
    CGeoPolygon(void);

    virtual ~CGeoPolygon(void);

    QPolygonF pts;

    void addPoint(QPointF pt);

    void paint(QPainter *paint);

    float *getVert(float *vert, int *count);

    float *getVert2(float *vert);

    QRectF getScope();
};


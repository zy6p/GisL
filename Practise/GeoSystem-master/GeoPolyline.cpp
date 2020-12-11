#include "GeoPolyline.h"


CGeoPolyline::CGeoPolyline(void) {
}


CGeoPolyline::~CGeoPolyline(void) {
}

void CGeoPolyline::addPoint(QPointF pt) {
    pts.append(pt);
}

void CGeoPolyline::paint(QPainter *paint) {
    QPen pen;
    pen.setWidthF(0.3f);
    pen.setColor(QColor("#e16b15"));
    paint->setPen(pen);
    paint->drawPolyline(this->pts);
}


float *CGeoPolyline::getVert(float *vert, int *count) {
    // ���·����ڴ�
    vert = (float *) realloc(vert, sizeof(float) * (*count + 3 * pts.size()));

    for (int i = 0; i < pts.size(); i++) {
        vert[*count + i * 3] = pts[i].x();
        vert[*count + i * 3 + 1] = pts[i].y();
        vert[*count + i * 3 + 2] = 0.0f;
        //vert[*count+i*3+3] = strokeR;
        //vert[*count+i*3+4] = strokeG;
        //vert[*count+i*3+5] = strokeB;
    }

    *count = *count + 3 * pts.size();
    return vert;
}

float *CGeoPolyline::getVert2(float *vert) {
    // �ж�polygon
    // ���·����ڴ�
    vert = new float[3 * pts.size()];

    for (int i = 0; i < pts.size(); i++) {
        vert[i * 3] = pts[i].x();
        vert[i * 3 + 1] = pts[i].y();
        vert[i * 3 + 2] = 0.0f;
    }
    return vert;
}

QRectF CGeoPolyline::getScope() {
    QRectF rect;
    QPointF topleft;
    QPointF bottomright;
    float maxx = 0, minx = FLT_MAX, maxy = 0, miny = FLT_MAX;
    for (int i = 0; i < pts.size(); i++) {
        if (pts[i].x() > maxx) {
            maxx = pts[i].x();
        }
        if (pts[i].y() > maxy) {
            maxy = pts[i].y();
        }
        if (pts[i].x() < minx) {
            minx = pts[i].x();
        }
        if (pts[i].y() < miny) {
            miny = pts[i].y();
        }
    }
    topleft.setX(minx);
    topleft.setY(maxy);
    bottomright.setX(maxx);
    bottomright.setY(miny);
    rect.setBottomRight(bottomright);
    rect.setTopLeft(topleft);
    this->setRect(rect);
    return rect;
}
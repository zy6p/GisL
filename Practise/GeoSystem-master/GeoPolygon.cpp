#include "GeoPolygon.h"
#include <qdebug.h>

CGeoPolygon::CGeoPolygon(void) {
}


CGeoPolygon::~CGeoPolygon(void) {
}

void CGeoPolygon::addPoint(QPointF pt) {
    pts.append(pt);
}

void CGeoPolygon::paint(QPainter *paint) {
    // ��������״
    QPen pen;
    pen.setWidthF(0.3f);
    pen.setColor(QColor("#e16b15"));
    paint->setPen(pen);
    // �������
    paint->setBrush(QBrush(QColor("#ed9758"), Qt::SolidPattern));
    paint->drawPolygon(this->pts, Qt::WindingFill);
}

float *CGeoPolygon::getVert(float *vert, int *count) {
    // �ж�polygon
    // ���·����ڴ�
    vert = (float *) realloc(vert, sizeof(float) * (*count + 3 * pts.size()));

    for (int i = 0; i < pts.size(); i++) {
        vert[*count + i * 3] = pts[i].x();
        vert[*count + i * 3 + 1] = pts[i].y();
        vert[*count + i * 3 + 2] = 0.0f;
        //vert[*count+i*6+3] = fillR;
        //vert[*count+i*6+4] = fillG;
        //vert[*count+i*6+5] = fillB;
    }

    *count = *count + 3 * pts.size();
    return vert;
    /*
    vert = (float*)realloc(vert,sizeof(float)* (*count + 18));
    vert[*count] = 0.02f;
    vert[*count+1] =  0.9f;
    vert[*count+2] = 0.0f;
    vert[*count+3] = r;
    vert[*count+4] = g;
    vert[*count+5] = b;

    vert[*count+6] = 0.024f;
    vert[*count+7] =  0.92f;
    vert[*count+8] = 0.0f;
    vert[*count+9] = r;
    vert[*count+10] = g;
    vert[*count+11] = b;

    vert[*count+12] = 0.025f;
    vert[*count+13] =  0.9f;
    vert[*count+14] = 0.0f;
    vert[*count+15] = r;
    vert[*count+16] = g;
    vert[*count+17] = b;
    *count = *count + 18;
    return vert;
    */
}

float *CGeoPolygon::getVert2(float *vert) {
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

QRectF CGeoPolygon::getScope() {
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
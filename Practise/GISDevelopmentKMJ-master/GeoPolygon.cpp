#include "GeoPolygon.h"
#include "EnumType.h"

GeoPolygon::GeoPolygon() {
    this->type = EnumType::POLYGON;
}

GeoPolygon::~GeoPolygon() {
    for (int i = 0; i < size(); i++) {
        delete pts.at(i);
    }
}

void GeoPolygon::addPoint(GeoPoint *point) {
    pts.push_back(point);
}

GeoPoint *GeoPolygon::getPointAt(int idx) {
    return pts.at(idx);
}

GeoPoint *GeoPolygon::removeAt(int idx) {
    GeoPoint *p = pts.at(idx);
    pts.removeAt(idx);
    return p;
}

QList<GeoPoint *> GeoPolygon::removeAll() {
    pts.clear();
    return pts;
}

int GeoPolygon::size() {
    return pts.size();
}

QRectF GeoPolygon::getRect() {
    GeoPoint *firstPoint = getPointAt(0);
    float left = firstPoint->getXf();
    float top = firstPoint->getYf();
    float right = firstPoint->getXf();
    float bottom = firstPoint->getYf();
    for (int i = 0; i < size(); i++) {
        GeoPoint *p = getPointAt(i);
        if (p->getXf() < left) left = p->getXf();
        if (p->getYf() > top) top = p->getYf();
        if (p->getXf() > right) right = p->getXf();
        if (p->getYf() < bottom) bottom = p->getYf();
    }
    return QRectF(QPointF(left, top), QPointF(right, bottom));
}


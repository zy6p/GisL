#include "GeoObject.h"


CGeoObject::CGeoObject(void) {
}


CGeoObject::~CGeoObject(void) {
}

void CGeoObject::setRect(QRectF rect) {
    this->qRect = rect;
}

QRectF CGeoObject::getRect() {
    return this->qRect;
}

void CGeoObject::setType(QString type) {
    this->type = type;
}

QString CGeoObject::getType() {
    return this->type;
}

QMap<QString, QString> CGeoObject::getProps() {
    return this->properties;
}

void CGeoObject::setProps(QMap<QString, QString> props) {
    this->properties = props;
}

void CGeoObject::paint(QPainter *paint) {

}

float *CGeoObject::getVert(float *vert, int *count) {
    return 0;
}

float *CGeoObject::getVert2(float *vert) {
    return nullptr;
}

QRectF CGeoObject::getScope() {
    return QRectF();
}
#include "GeoMap.h"


CGeoMap::CGeoMap(void) : mapScale(mapScale) {

}


CGeoMap::~CGeoMap(void) {
    geoLayers.clear();
}

void CGeoMap::setName(QString mapName) {
    this->name = mapName;
}

QString CGeoMap::getName() {
    return this->name;
}

int CGeoMap::getMapScale() {
    return this->mapScale;
}

void CGeoMap::setRect(QRectF qRect) {
    this->qRect = qRect;
}

QRectF CGeoMap::getRect() {
    return this->qRect;
}

// ���layer
void CGeoMap::addLayer(CGeoLayer *layer) {
    geoLayers.append(layer);
}

// �Ƴ�layer
void CGeoMap::deleteLayerAt(int index) {
    geoLayers.removeAt(index);
}

// ȫ���Ƴ�
void CGeoMap::deleteLayerAll() {
    geoLayers.clear();
}

// ����layer�ɼ���
void CGeoMap::setLayerVisible(QString layerName, bool isVisible) {

}

void CGeoMap::paint(QPainter *paint) {
    for (int i = 0; i < geoLayers.size(); i++)
        geoLayers[i]->paint(paint);
}

float *CGeoMap::getVert(float *vert, int *count) {
    for (int i = 0; i < geoLayers.size(); i++)
        vert = geoLayers[i]->getVert(vert, count);
    return vert;
}

QRectF CGeoMap::getScope() {
    QRectF rect;
    float maxx = 0, minx = FLT_MAX, maxy = 0, miny = FLT_MAX;
    for (int i = 0; i < geoLayers.size(); i++) {
        QRectF r = geoLayers[i]->getScope();
        if (rect.width() == 0) {
            rect = r;
        }
        if (r.top() > maxy) {
            maxy = r.top();
        }
        if (r.right() > maxx) {
            maxx = r.right();
        }
        if (r.left() < minx) {
            minx = r.left();
        }
        if (r.bottom() < miny) {
            miny = r.bottom();
        }
        rect = QRectF(QPointF(minx, maxy), QPointF(maxx, miny));

    }
    this->qRect = rect;
    return rect;
}

QRectF CGeoMap::getScope(int i) {
    QRectF rect;
    float maxx = 0, minx = FLT_MAX, maxy = 0, miny = FLT_MAX;
    for (int i = 0; i < geoLayers.size(); i++) {
        QRectF r = geoLayers[i]->getRect();
        if (rect.width() == 0) {
            rect = r;
        }
        if (r.top() > maxy) {
            maxy = r.top();
        }
        if (r.right() > maxx) {
            maxx = r.right();
        }
        if (r.left() < minx) {
            minx = r.left();
        }
        if (r.bottom() < miny) {
            miny = r.bottom();
        }
        rect = QRectF(QPointF(minx, maxy), QPointF(maxx, miny));
    }
    this->qRect = rect;
    return rect;
}
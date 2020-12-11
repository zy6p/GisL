#pragma once

#include <qstring.h>
#include <qrect.h>
#include <qlist.h>
#include "GeoLayer.h"

#define FLT_MAX         3.402823466e+38F

class CGeoMap {
private:
    // ��ͼ����
    QString name;
    // ��ͼ������
    const int mapScale;
    // ��ͼ��Χ
    QRectF qRect;

public:
    // ���캯��
    CGeoMap(void);

    // ��������
    virtual ~CGeoMap(void);

    // ��ȡ��ͼ����
    QString getName();

    void setName(QString mapName);

    // ��ͼ������ͼ��
    QList<CGeoLayer *> geoLayers;

    // ��õ�ͼ������
    int getMapScale();

    QRectF getRect();

    void setRect(QRectF qRect);

    // ���layer
    void addLayer(CGeoLayer *layer);

    // �Ƴ�layer
    void deleteLayerAt(int index);

    // ȫ���Ƴ�
    void deleteLayerAll();

    // ����layer�ɼ���
    void setLayerVisible(QString layerName, bool isVisible);

    void paint(QPainter *paint);

    float *getVert(float *vert, int *count);

    // ��Χ
    QRectF getScope();

    QRectF getScope(int i);
};


#pragma once

#include<qrect.h>
#include"GeoFeature.h"

class QuadNode {
public:
    QuadNode();

    ~QuadNode();

    QRectF getNodeRect();

    void setNodeRect(QRectF rect);

    QList<GeoFeature *> getFeaturesAll();

    GeoFeature *getFeatureAt(int i);

    void addFeature(GeoFeature *feature);

    QuadNode *getChildrenAt(int i);

    void addChild(QuadNode *child);

    void splitRect4(QRectF NodeRect, QRectF Rect[]);//��һ�����η���Ϊ�ĸ���ȵľ���
private:
    QRectF NodeRect;//�ڵ�������ľ�������
    QList<GeoFeature *> features;//�ռ����ָ������
    QList<QuadNode *> childs;//ָ��ڵ���ĸ�����
};


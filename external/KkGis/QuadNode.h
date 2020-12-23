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

    void splitRect4(QRectF NodeRect, QRectF Rect[]);//将一个矩形分裂为四个相等的矩形
private:
    QRectF NodeRect;//节点所代表的矩形区域
    QList<GeoFeature *> features;//空间对象指针数组
    QList<QuadNode *> childs;//指向节点的四个孩子
};


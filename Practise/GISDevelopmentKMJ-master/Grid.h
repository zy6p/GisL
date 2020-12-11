#pragma once

#include"GeoFeature.h"
#include"qlist.h"

class Grid {
public:
    Grid();

    ~Grid();

    void addFeatures(GeoFeature *feature);

    void setGridRect(QRectF rect);

    QRectF getGridRect();

    int getFeatureNum();

    QList<GeoFeature *> getFeatureAll();

    GeoFeature *getFeatureAt(int i);

private:
    QList<GeoFeature *> features;//�ø����а����Ŀռ����
    QRectF gridRect;//�����ľ��η�Χ
};


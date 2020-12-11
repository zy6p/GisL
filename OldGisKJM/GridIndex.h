#pragma once

#include<qlist.h>
#include"Grid.h"
#include"Index.h"
#include"GeoFeature.h"
#include"GeoPoint.h"
#include"EnumType.h"
#include"GeoPolygon.h"
#include"GeoPolyline.h"
#include<qpolygon.h>
#include<qdebug.h>

class GridIndex : public Index {
public:
    GridIndex();

    ~GridIndex();

    void setGrid(QRectF layerRect, QList<GeoFeature *> features);

    int getGridNum();

    QList<Grid *> getGridsAll();

    Grid *getGridAt(int i);

    GeoFeature *searchGrid(GeoPoint *pt, float thresholed);//��ѯ
private:
    int row = 10;//Ĭ�����Ϊ10*10����һ������ݷ�Χ��Ҫ�ظ�������Ӧ���
    int col = 10;
    QList<Grid *> grids;//���еĸ���
};


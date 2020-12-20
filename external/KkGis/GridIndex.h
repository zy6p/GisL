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

class GridIndex : public Index
{
public:
	GridIndex();
	~GridIndex();
	void setGrid(QRectF layerRect, QList<GeoFeature*> features);
	int getGridNum();
	QList<Grid*> getGridsAll();
	Grid* getGridAt(int i);
	GeoFeature* searchGrid(GeoPoint *pt,float thresholed);//查询
private:
	int row = 10;//默认情况为10*10，下一步会根据范围与要素个数自适应宽高
	int col = 10;
	QList<Grid*> grids;//所有的格网
};


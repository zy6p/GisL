#pragma once
#include"GeoFeature.h"
#include"qlist.h"

class Grid
{
public:
	Grid();
	~Grid();
	void addFeatures(GeoFeature* feature);
	void setGridRect(QRectF rect);
	QRectF getGridRect();
	int getFeatureNum();
	QList<GeoFeature*> getFeatureAll();
	GeoFeature *getFeatureAt(int i);
private:
	QList<GeoFeature*> features;//该格网中包含的空间对象
	QRectF gridRect;//格网的矩形范围
};


#include "Grid.h"

Grid::Grid()
{
}

Grid::~Grid()
{
	for (int i = 0; i < features.size(); i++)
		delete features.at(i);
}

void Grid::addFeatures(GeoFeature * feature)
{
	features.append(feature);
}

void Grid::setGridRect(QRectF rect)
{
	gridRect = rect;
}

QRectF Grid::getGridRect()
{
	return gridRect;
}

int Grid::getFeatureNum()
{
	return features.size();
}

QList<GeoFeature*> Grid::getFeatureAll()
{
	return features;
}

GeoFeature * Grid::getFeatureAt(int i)
{
	return features.at(i);
}

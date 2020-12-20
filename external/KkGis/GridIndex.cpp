#include "GridIndex.h"

GridIndex::GridIndex()
{
	this->type = EnumType::indexMode::GRIDINDEX;
}

GridIndex::~GridIndex()
{
	for (int i = 0; i < grids.size(); i++)
		delete grids.at(i);

}


void GridIndex::setGrid(QRectF layerRect,QList<GeoFeature*> features)
{
	int featureNum = features.size();
	double dx, dy;//格网的长和宽
	
	double startx = layerRect.left();
	double starty = layerRect.top();

	dx = abs(layerRect.width() / row);
	dy = abs(layerRect.height() / col);

	double top, left, bottom, right;

	for (int j = 0; j < row; j++)
	{
		top = starty - dy * j;
		bottom = top - dy;
		for (int i = 0; i < col; i++)
		{
			left = startx + dx * i;
			right = left + dx;

			Grid *grid = new Grid();
			//储存每个格子的范围数据
			QRectF gridRect = QRectF(QPointF(left, top), QPointF(right, bottom));
			grid->setGridRect(gridRect);
			//对每个格子遍历每个要素，储存与其相交的要素
			for (int k = 0; k < featureNum; k++)
			{
				QRectF featureRect = features.at(k)->getGeometry()->getRect();
				if (featureRect.intersects(gridRect))
					grid->addFeatures(features.at(k));
			}
			grids.append(grid);
		}
	}
}

int GridIndex::getGridNum()
{
	return grids.size();
}

QList<Grid*> GridIndex::getGridsAll()
{
	return grids;
}

Grid * GridIndex::getGridAt(int i)
{
	return grids.at(i);
}

GeoFeature * GridIndex::searchGrid(GeoPoint *point,float thresholed)
{
	int gridNum = grids.size();

	//找到鼠标点击到的格网
	Grid *gridFound;
	for (int i = 0; i < gridNum; i++)//遍历所有格网
	{
		QRectF gridRect = grids.at(i)->getGridRect();//得到格网的矩形范围
		if (gridRect.contains(QPointF(point->getXf(), point->getYf())))//判断点是否落在格网矩形中
		{
			gridFound = grids.at(i);
			break;//每个矩形不相交，找到则跳出循环
		}
	}

	//找到格网中点击的要素
	GeoFeature* featureFound;
	int featureNum = gridFound->getFeatureNum();
	QList<GeoFeature*> features = gridFound->getFeatureAll();
	for (int i = 0; i < featureNum; i++)//遍历所有要素
	{
		GeoFeature *feature = features.at(i);//对每一种要素判断是否与point的缓冲区相交
		GeoGeometry *geometry = feature->getGeometry();
		//如果点击的点与要素点小于一定的距离阈值，则返回该点
		if (geometry->getType() == EnumType::POINT)
		{
			GeoPoint *pt = static_cast<GeoPoint*>(geometry);
			if (pt->disToPoint(point) < thresholed)//如果点到要素点的距离小于距离阈值，找到该要素
				featureFound = feature;
		}
		else if (geometry->getType() == EnumType::POLYLINE)
		{
			GeoPolyline *polyline = static_cast<GeoPolyline*>(geometry);
			if (polyline->disToPoint(point) < thresholed)//如果点到要素线的距离小于距离阈值，找到该要素
				featureFound = feature;
		}
		//如果点击的点在多边形内则返回该多边形
		else if (geometry->getType() == EnumType::POLYGON)
		{
			GeoPolygon* polygon = static_cast<GeoPolygon*>(geometry);
			QVector<QPointF> polygonPoints;
			int pointNum = polygon->size();
			for (int j = 0; j < pointNum; j++)//将数据存储为Qpolygon可用的形式
			{
				QPointF pt;
				pt.setX(polygon->getPointAt(j)->getXf());
				pt.setY(polygon->getPointAt(j)->getYf());
				polygonPoints.append(pt);
			}
			if (QPolygonF(polygonPoints).contains(QPointF(point->getXf(), point->getYf())))//如果点包含在多边形内，找到该要素
				featureFound = feature;
		}
		else
		{
			featureFound = NULL;
		}
	}
	return featureFound;
}


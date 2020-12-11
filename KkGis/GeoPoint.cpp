#include "geopoint.h"
#include "EnumType.h"
#include <qlist.h>

GeoPoint::GeoPoint()
{
    this->type = EnumType::POINT;
}

GeoPoint::GeoPoint(float xf, float yf)
{
	x = xf;
	y = yf;
}

GeoPoint::GeoPoint(QPointF point)
{
	x = point.x();
	y = point.y();
}

GeoPoint::~GeoPoint()
{
	
}

double GeoPoint::getXf()
{
	return x;
}

void GeoPoint::setXf(double x)
{
	this->x = x;
}

double GeoPoint::getYf()
{
	return y;
}

void GeoPoint::setYf(double y)
{
	this->y = y;
}

int GeoPoint::getXd()
{
	return (int)x;
}

void GeoPoint::setXd(int x)
{
	this->x = (double)x;
}

int GeoPoint::getYd()
{
	return (int)y;
}

void GeoPoint::setYd(int y)
{
	this->y = (double)y;
}

void GeoPoint::setXYf(double x, double y)
{
	this->x = x;
	this->y = y;
}

QRectF GeoPoint::getRect()
{
	return QRectF(x,y,0,0);
}

int GeoPoint::size()
{
	return 1;
}

double GeoPoint::disToPoint(GeoPoint* pt)
{
	double dx2 = pow(x - pt->getXf(), 2);
	double dy2 = pow(y - pt->getYf(), 2);
	return pow(dx2 + dy2, 0.5);
}

double GeoPoint::nearestDisToPoints(QList<GeoPoint*> pts)
{
	float dis = 999999999999999999;
	if (pts.size()) {
		GeoPoint* nearestPoint = pts.at(0);
		for (int i = 1; i < pts.size(); i++) {
			GeoPoint* p = pts.at(i);
			float edis = p->disToPoint(&GeoPoint(x, y));
			if (edis < dis) {
				dis = edis;
			}
		}
	}
	return dis;
}

GeoPoint * GeoPoint::nearestPointToPoints(QList<GeoPoint*> pts, float threshole)
{
	float dis = 999999999999999999;
	if (pts.size()) {
		GeoPoint* nearestPoint = pts.at(0);
		for (int i = 1; i < pts.size(); i++) {
			GeoPoint* p = pts.at(i);
			float edis = p->disToPoint(&GeoPoint(x, y));
			if (edis < dis) {
				nearestPoint = p;
				dis = edis;
			}
		}
		if (dis < threshole) {
			return nearestPoint;
		}
	}
	return NULL;
}


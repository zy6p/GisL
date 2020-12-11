#ifndef GEOPOLYLINE_H
#define GEOPOLYLINE_H
#include <QList>
#include "GeoPoint.h"
#include <qrect.h>

class GeoPolyline : public GeoGeometry
{
public:
    GeoPolyline();
	~GeoPolyline();
	void addPoint(GeoPoint* point);
	GeoPoint* getPointAt(int idx);
	GeoPoint* removeAt(int idx);
	QList<GeoPoint*> removeAll();
	int size();
	QRectF getRect();
	double disToPoint(GeoPoint *pt);//点到多线的距离，为最近距离
	GeoPoint* getMeanCenter();
private:
    QList<GeoPoint*> pts;
};

#endif // GEOPOLYLINE_H

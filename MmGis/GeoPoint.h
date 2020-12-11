#pragma once
#include "geoobject.h"

class CGeoPoint :
	public CGeoObject
{
private:
	QPointF pt;
public:
	CGeoPoint(void);
	virtual ~CGeoPoint(void);
	void setPoint(QPointF pt);
	QPointF getPoint();
	void paint(QPainter *paint);
	float* getVert(float *vert,int *count);
	float* getVert2(float *vert);
	QRectF getScope();
	QPolygonF pts;// 外接
};
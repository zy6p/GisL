#include "GeoPoint.h"


CGeoPoint::CGeoPoint(void)
{
}


CGeoPoint::~CGeoPoint(void)
{
}

void CGeoPoint::setPoint(QPointF pt)
{
	this->pt = pt;
}

QPointF CGeoPoint::getPoint(){
	return this->pt;
}

void CGeoPoint::paint(QPainter *paint){
	paint->drawPoint(this->pt);
}

float* CGeoPoint::getVert(float *vert,int *count){
	// 重新分配内存
	vert = (float*)realloc(vert,sizeof(float)* (*count+3));
	vert[*count] = pt.x();
	vert[*count+1] = pt.y();
	vert[*count+2] = 0.0f;
	//vert[*count+3] = strokeR;
	//vert[*count+4] = strokeG;
	//vert[*count+5] = strokeB;
	// 设置个数
	*count = *count+1*3;
	return vert;
}

float* CGeoPoint::getVert2(float *vert){
	// 重新分配内存
	vert = new float[3];
	vert[0] = pt.x();
	vert[1] = pt.y();
	vert[2] = 0.0f;
	return vert;
}

QRectF CGeoPoint::getScope(){
	return QRectF(pt.x(), pt.y(), pt.x(), pt.y());
}
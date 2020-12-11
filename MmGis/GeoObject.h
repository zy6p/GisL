#pragma once
#include <qstring.h>
#include <qrect.h>
#include <qpoint.h>
#include <qpainter.h>
#include <qtransform.h>
#include <qmap.h>
#define FLT_MAX         3.402823466e+38F

class CGeoObject
{
private:
	// 目标类型
	QString type;
	// 外接矩形 可能存在
	QRectF qRect;
	// 属性
	QMap<QString,QString> properties;
public:
	float fillR,fillG,fillB;
	float strokeR,strokeG,strokeB;
	float strokeWidth;
	float fillAlpha,strokeAlpha;
	QPointF centriod;

	CGeoObject(void);
	virtual ~CGeoObject(void);
	void setRect(QRectF rect);
	QRectF getRect();

	void setType(QString type);
	QString getType();

	QMap<QString,QString> getProps();
	void setProps(QMap<QString,QString> props);

	virtual void paint(QPainter *paint);

	virtual float* getVert(float *vert,int *count);
	virtual float* getVert2(float *vert);

	virtual QRectF getScope();
};


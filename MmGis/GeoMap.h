#pragma once
#include <qstring.h>
#include <qrect.h>
#include <qlist.h>
#include "GeoLayer.h"
#define FLT_MAX         3.402823466e+38F

class CGeoMap
{
private:
	// 地图名称
	QString name;
	// 地图比例尺
	const int mapScale;
	// 地图范围
	QRectF qRect;
	
public:
	// 构造函数
	CGeoMap(void);
	// 析构函数
	virtual ~CGeoMap(void);
	// 获取地图名称
	QString getName();
	void setName(QString mapName);
	// 地图包含的图层
	QList<CGeoLayer*> geoLayers;
	// 获得地图比例尺
	int getMapScale();
	QRectF getRect();
	void setRect(QRectF qRect);
	// 添加layer
	void addLayer(CGeoLayer* layer);
	// 移除layer
	void deleteLayerAt(int index);
	// 全部移除
	void deleteLayerAll();
	// 设置layer可见性
	void setLayerVisible(QString layerName,bool isVisible);

	void paint(QPainter *paint);

	float* getVert(float *vert,int *count);
	// 范围
	QRectF getScope();

	QRectF getScope(int i);
};


#pragma once
#include "COption.h"
#include "GeoPoint.h"
#include "GeoLayer.h"
#include "Option.h"
class AccessibilityOption: public Option
{
public:
	AccessibilityOption();
	~AccessibilityOption();
	void setOriLayer(GeoLayer* point);
	GeoLayer* getOriginPointLayer();
	void setDirPointLayer(GeoLayer* layer);
	GeoLayer* getDirPointLayer();
	void setArcLayer(GeoLayer* layer);
	GeoLayer* getArcLayer();
	void setNodeLayer(GeoLayer* layer);
	GeoLayer* getNodeLayer();
	QString getSaveField();
	void setSaveField(QString field);
	void setTimeLimit(float time);
	float getTimeLimit();
	bool getUseSelectedFeatures();
	void setUseSelectedFeatures(bool flag);
private:
	GeoLayer* oriPointLayer;   //od成本的出发点图层，也是计算可达性的点所在的图层
	GeoLayer* dirPointLayer;  //od成本的到达点图层
	GeoLayer* arcLayer;   //道路线表
	GeoLayer* nodeLayer;  //道路节点表
	QString saveField;
	float timeLimit;  //时间成本，到时候换算成距离成本
	bool useSelectedFeatures;
};


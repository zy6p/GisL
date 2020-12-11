#pragma once
#include"COption.h"
#include "GeoLayer.h"
#include "Option.h"
class GeoTool
{
public:
	GeoTool();
	~GeoTool();
	void setOption(Option * opt);
	Option* getOption();
	int getToolType();
	virtual int run_tool() = 0;  //任何计算都返回一个图层作为结果
protected:
	Option *option;
	int type;
	
};


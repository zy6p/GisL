#pragma once
#include "GeoTool.h"
#include "AccessibilityOption.h"
#include"ogrsf_frmts.h"
#include <qsqldatabase.h>
#include <libpq-fe.h>  //此为postgresql的include文件，里面声明了结构体和全局函数

class AccessibilityAnalysisTool :
	public GeoTool
{
public:
	AccessibilityAnalysisTool();
	~AccessibilityAnalysisTool(); 

	int run_tool();
private:
	QSqlDatabase db;
	QString dijkstraSql;

};


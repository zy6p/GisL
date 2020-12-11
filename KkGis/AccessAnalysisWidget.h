#pragma once

#include <QWidget>
#include "GeoMap.h"
#include "PostgisHelper.h"
namespace Ui { class AccessAnalysisWidget; };

class AccessAnalysisWidget : public QWidget
{
	Q_OBJECT

public:
	AccessAnalysisWidget(GeoMap* map, QWidget *parent = Q_NULLPTR);
	~AccessAnalysisWidget();
	void initWidget();  //重复开启时调用

	void connectDatabase(QString databaseUrl);
private:
	Ui::AccessAnalysisWidget *ui;
	GeoMap* map;
	bool isValid();  // 判断输入函数是否合法，如不合法，给予提示。TODO 这里使用的是可重用性较差的方式，合理的方式是通过配置和工具类实现检测，不过时间允许就不做了

	GDALDataset* dataset;
	QString oriBoxSelectHint;
public slots:
	void on_runTool();
};

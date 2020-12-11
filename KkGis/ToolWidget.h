#pragma once

#include <QWidget>
#include <qtreewidget.h>
#include <GeoMap.h>
#include "AccessAnalysisWidget.h"
#include "ogrsf_frmts.h"
namespace Ui { class ToolWidget; };

class ToolWidget : public QWidget
{
	Q_OBJECT

public:
	ToolWidget(GeoMap* map, QWidget *parent = Q_NULLPTR);
	~ToolWidget();

private:
	Ui::ToolWidget *ui;
	GeoMap* map;
	QTreeWidget* toolTree;
	void initToolTree();
	AccessAnalysisWidget* aaw;

	void initAccessibilityAnalysisWidget();
	void execKDEDiolog();

signals:
	void on_addNewLayerSignal(GeoLayer* layer);
public slots:
	void on_item_clicked(QTreeWidgetItem* item);
};

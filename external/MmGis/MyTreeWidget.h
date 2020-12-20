#pragma once
#include <qtreewidget.h>
#include "ui_MyTreeWidget.h"
#include "GeoLayer.h"
#include "GeoMap.h"
#include <QContextMenuEvent>
#include <qmenu.h>
#include "dialog.h"
#include "AttributeTable.h"
#include <qmessagebox.h>
#include "LayerColoursSet.h"
class MyTreeWidget:public QTreeWidget
{
	Q_OBJECT
public:
	MyTreeWidget(QWidget *parent = 0);
	virtual ~MyTreeWidget(void);
	QMenu* popMenu;
	QTreeWidgetItem* curItem;
private:
	Ui::Form2 ui;
	CGeoMap *map;
	Dialog *dialog;
	AttributeTable *attri;
	LayerColoursSet *layerColoursSet;
	void createActions();
	void createMenu();
	int loc,deletesize;

	//void contextMenuEvent ( QContextMenuEvent * event );
	private slots:
		void updateMyTreeWidgetSlot(CGeoMap *map);
		void itemClick();
		void viewIt();
		void deleteIt();
		void sltShowPopMenu(const QPoint&);
		void serProp();
		void openAttri();
		void getColorAndWidth(QColor fillColor,QColor strokeColor,float width);
		void showIndexGrids();
		void hideIndexGrids();
		void analyzeKDE();
		void layerColours();
		void getAttribute(int layerID,QString attribute);  // 得到用于分级设色的属性

signals:
		void updateTreeGLSignal(int mode,CGeoMap *map,int layerID,int size);
		void updateLayerIDSignal(int mode,int layerID);
		void updateColorAndWidth(float r,float g,float b,double width);
		void sendColorAndWidthData(int index,QColor fillColor,QColor strokeColor,float width);//重新渲染信号
		void showAttri(CGeoLayer* layer);
		void IndexGrids();
		void KDEAnalyze(int layerID);
		void setLayerClours(int layerID,QString layerNAME,QList<QString> propsKey);
		void setLayerCol(int layerID,QString attri); // 分级设色

};


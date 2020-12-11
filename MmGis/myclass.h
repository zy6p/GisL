#ifndef MYCLASS_H
#define MYCLASS_H

#include <QtWidgets/QMainWindow>
#include "ui_myclass.h"
#include <QPainter>
#include "GeoJsonTool.h"
#include "GeoMap.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <qjsonarray.h>
#include "MyGLWidget.h"
#include <qtreewidget.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "MyTreeWidget.h"
#include "Connect_Sql.h"
#include "MyWizard.h"
class MyClass : public QMainWindow
{
	Q_OBJECT

public:
	MyClass(QWidget *parent = 0);
	~MyClass();

private:
	Ui::MyClassClass ui;
	void createActions();
public:
	//MyTreeWidget *treeWidget;
	QString dbname, host, user, password, table,port; // postgresql配置

	MyGLWidget* gl; // 储存opengl
	MyWizard *mywizard;
	private slots:
		void readGeoJson();
		void readShape();
		void saveShapefile();
		void getDatabaseData();
		//void showIndexGrids();
		//void hideIndexGrids();
		void IndexGrids();
		void clearContent();
protected:
	//void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
signals:
	void updateMyGLSignal(int mode,const char* filename,int layerID);//重新渲染信号
	void updateMyGLPostgresqlSignal(int mode,int layerID,QString port,QString dbname,QString host,QString user,QString password,QString table); // 读取数据库，重新渲染
	void updateMyTreeWidgetSignal(CGeoMap *map);
	void updateData(int mode,CGeoMap *map,int layerID,int size);
	void updateLayerIDSignal(int mode,int layerID);
	void sendColorAndWidthData2(int layerID,QColor fillColor,QColor strokeColor,float width);//重新渲染信号
	void sendColorAndWidthData(vector<QString> names,QColor fillColor,QColor strokeColor,float width);//重新渲染信号
	void KDEAnaly(int layerID);
	void sendLayerClours(int layerID,QString attri);

	private slots:
		void updateTreeGLSlot(int mode,CGeoMap *map,int layerID,int size);
		void updateLayerIDSlot(int mode,int layerID);
		void getPostgresqlSlot(QString dbname,QString host,QString user,QString password,QString table,QString port);
		void getColorAndWidthData(int layerID,QColor fillColor,QColor strokeColor,float width);//重新渲染信号
		void search();
		void finishHTTP(QNetworkReply *reply);
		void KDEAnalyze(int layerID);
		void getLayerClours(int layerID,QString attri);

};

#endif // MYCLASS_H

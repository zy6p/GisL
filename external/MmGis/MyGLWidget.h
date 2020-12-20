#pragma once
#include "ui_MyGLWidget.h"
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>
#include <qopenglfunctions_4_5_core.h>
#include <QPainter>
#include "GeoJsonTool.h"
#include "GeoMap.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "GeoMap.h"
#include <qdebug.h>
#include "GdalTool.h"
#include <QWheelEvent>
#include "Connect_Sql.h"
#include <QGraphicsDropShadowEffect>
#include "SeekEleAttri.h"
#include "KernelWidget.h"
class MyGLWidget:public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
	Q_OBJECT
public:
	MyGLWidget(QWidget *parent = 0);
	virtual ~MyGLWidget(void);
	void readDataFromShape(const char* filename);
	void readDataFromGeoJSON(const char* filename);
	void readDataFromPostgresql();
	int mode; // 绘制模式0:geojson 1:shp 2:隐藏/显示 3:删除
	const char* filename; // 绘制数据
	CGeoMap *map;
	int layerID; // 要展示的layerID
	CGeoLayer *viewLayer; // 展示的layer
	CGeoLayer *coloursLayer; // 展示的layer
	QRectF rect; // 展示的layer的rect
	QRectF originWorldRect;
	CGeoObject *choosed;
	//bool showIndexGrid;

private:
	Ui::Form ui;
	GLuint* VBO, *VAO;
	GLuint ID;
	int *len;
	//float *vertices;
	//int *count;
	int size; // VAO size
	QMatrix4x4 modelTemp;
	QMatrix4x4 viewTemp;
	QMatrix4x4 orthoTemp; 
	QPointF beginRect; // 点击初始点
	QPointF endRect; // 点击末尾点
	QColor prevFillColor,prevStrokeColor; // 当前选择的颜色和之前的颜色
	float prevStrokeWidth;
	vector<int> objID;
	vector<QString> names;
	//QColor objFillColor,objStrokeColor; // 设置的颜色
	//float objStrokeWidth;
	QString dbname, host, user, password, table,port; // postgresql配置
	bool layerColours; // 分层设色标识
	
	SeekEleAttri *seek;
	KernelWidget *kernel;
	void createShader(const char* vertexPath, const char* fragmentPath);
	void checkCompileErrors(unsigned int shader, std::string type);
	void loadData();
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	//QPointF screenToWorld(QPointF screenPoint);
	QPointF screenToWorld3(QPointF screenPoint);
	QPointF screenToNormalizedPos(QPointF screenPoint);
	void Scale(QPoint originScreen, float scale);
protected:
	// 绘制opengl
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w,int h) override;
	public slots:
		void updateMyGLSlot(int mode,const char* filename,int layerID);
		void updateMyGLPostgresqlSlot(int mode,int layerID,QString port,QString dbname,QString host,QString user,QString password,QString table); // 读取数据库，重新渲染
		void updateData(int mode,CGeoMap *map,int layerID,int size);
		void updateLayerID(int mode,int LayerID);
		void getColorAndWidthData2(int layerID,QColor fillColor,QColor strokeColor,float width);//重新渲染信号
		void getColorAndWidthOneObj(int objID,QColor fillColor,QColor strokeColor,float width);//重新渲染一个object
		void getColorAndWidthObjs(vector<QString> names,QColor fillColor,QColor strokeColor,float width);//重新渲染查找到的object
		void restore(int objID);
		void KDEAnaly(int layerID);
		void setLayerClours(int layerID,QString attribute); // 分层设色
signals:
		void showAttriTable(CGeoObject *object,int objID);
		void KDEAnalyze(float bandWidth,float **loc,float maxLoc,float minLoc);

};
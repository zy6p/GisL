#pragma once
#include <qopenglwidget.h>
#include <qopenglfunctions.h>
#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>
#include <qopenglfunctions_4_5_core.h>
#include "ui_KernelWidget.h"
#include <QMouseEvent>
class KernelWidget:public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core
{
	Q_OBJECT
public:
	KernelWidget(QWidget *parent = 0);
	~KernelWidget(void);

private:
	Ui::Form10 ui;
	// 核密度
	float bandWidth;
	float **loc;
	float maxLoc;
	float minLoc;
	bool finished;

	public slots:
		void KDEAnalyze(float bandWidth,float **loc,float maxLoc,float minLoc);

protected:
	// 绘制opengl
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w,int h) override;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent *event);
	double mouseX, mouseY, offsetX, offsetY, newOffsetX , newOffsetY ;
	double scale;
signals:
};


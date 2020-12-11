#pragma once
#include <qtablewidget.h>
#include "GeoObject.h"
#include <ui_SeekEleAttri.h>
#include "XColorMaster.h"
#include <qlineedit.h>
class SeekEleAttri:public QWidget
{
	Q_OBJECT
public:
	SeekEleAttri(QWidget *parent = 0);
	virtual ~SeekEleAttri(void);
private:
	Ui::Form9 ui;
	XColorMaster *fillColorXM;
	XColorMaster *strokeColorXM;
	QLineEdit *lineEdit;
	int objID;
	private slots:
		void showAttri(CGeoObject *obj,int objID);
		void continueClick();
		void cancelClick();
signals:
		void sendColorAndWidthData(int objID,QColor fillColor,QColor strokeColor,float width);//重新渲染信号
		void restore(int objID);
};


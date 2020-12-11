#pragma once
#include <qwidget.h>
#include "ui_MyWizard.h"
class MyWizard:public QWidget
{
	Q_OBJECT
public:
	MyWizard(QWidget *parent = 0);
	virtual ~MyWizard(void);
	QString dbname, host, user, password, table,port; // postgresql配置
private:
	Ui::Form4 ui;
	private slots:
		void continueClick();
		void cancelClick();
signals:
		void sendPostgresqlData(QString dbname,QString host,QString user,QString password,QString table,QString port);//重新渲染信号
};


#pragma once

#include <QWidget>
#include "GeoMap.h"
#include "PostgisHelper.h"

namespace Ui { class AccessAnalysisWidget; };

class AccessAnalysisWidget : public QWidget {
Q_OBJECT

public:
    AccessAnalysisWidget(GeoMap *map, QWidget *parent = Q_NULLPTR);

    ~AccessAnalysisWidget();

    void initWidget();  //�ظ�����ʱ����

    void connectDatabase(QString databaseUrl);

private:
    Ui::AccessAnalysisWidget *ui;
    GeoMap *map;

    bool
    isValid();  // �ж����뺯���Ƿ�Ϸ����粻�Ϸ���������ʾ��TODO ����ʹ�õ��ǿ������Խϲ�ķ�ʽ������ķ�ʽ��ͨ�����ú͹�����ʵ�ּ�⣬����ʱ������Ͳ�����

    GDALDataset *dataset;
    QString oriBoxSelectHint;
public slots:

    void on_runTool();
};

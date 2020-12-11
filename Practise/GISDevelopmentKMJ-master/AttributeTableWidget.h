#pragma once

#include <QWidget>
#include <qtablewidget.h>
#include "GeoLayer.h"

namespace Ui { class AttributeTableWidget; };

class AttributeTableWidget : public QWidget {
Q_OBJECT

public:
    AttributeTableWidget(GeoLayer *layer, QWidget *parent = Q_NULLPTR);

    ~AttributeTableWidget();

protected:
    void closeEvent(QCloseEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::AttributeTableWidget *ui;
    QTableWidget *table;
    GeoLayer *layer;
    QList<GeoFeature *> originFeatures; //����layer�е�feature�˼������Ƶ�˳����select֮���ı�˳�򣬹��ڴ˱���һ������tableʱ��features����
    QMap<GeoFeature *, int> featureRowMap;

    void initTable();

    int startRow;
    int endRow;
    int keyPressed;

    QMenu *itemMenu;

    void initRightedMenu();

signals:

    void closeSignal(QCloseEvent *event);

    void updateMapSignal();

    void zoomToFeatureSignal(GeoFeature *feature);

    void transToFeatureSignal(GeoFeature *feature);

public slots:

    void on_item_clicked(QTableWidgetItem *item);

    void on_zoomToFeature_action_triggered();

    void on_transToFeature_action_triggered();

    void on_fileTree_contextMenu_request(const QPoint &pos);

    void on_glFeatureSelected(GeoFeature *feature);
};

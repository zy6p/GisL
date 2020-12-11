#pragma once

#include <QWidget>
#include "ui_SearchWidget.h"
#include "GeoLayer.h"

namespace Ui {
    class SearchWidget;
}

class SearchWidget : public QWidget {
Q_OBJECT

public:
    SearchWidget(GeoLayer *layer, QWidget *parent = nullptr);

    ~SearchWidget();

protected:
    void closeEvent(QCloseEvent *event);


private:
    Ui::SearchWidget *ui;
    GeoLayer *layer;
    QMap<int, GeoFeature *> rowFeatureMap;
    QMenu *itemMenu;

    void initRightedMenu();

signals:

    void closeSignal();

    void renderSelectedFeatures(QList<GeoFeature *> features);

    void zoomToFeatureSignal(GeoFeature *feature);

    void transToFeatureSignal(GeoFeature *feature);

    void selectFeatureSignal(GeoFeature *feature);

public slots:

    void on_search_button_clicked();

    void on_zoomToFeature_action_triggered();

    void on_transToFeature_action_triggered();

    void on_fileTree_contextMenu_request(const QPoint &pos);

    void on_item_doubleClicked(QListWidgetItem *item);

};

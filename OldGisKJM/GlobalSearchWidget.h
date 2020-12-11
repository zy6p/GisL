#pragma once

#include <QWidget>
#include <GeoMap.h>
#include "QListWidgetItem"

namespace Ui { class GlobalSearchWidget; };

class GlobalSearchWidget : public QWidget {
Q_OBJECT

public:
    GlobalSearchWidget(GeoMap *map, QWidget *parent = Q_NULLPTR);

    ~GlobalSearchWidget();

private:
    Ui::GlobalSearchWidget *ui;
    GeoMap *map;
    QMap<int, GeoFeature *> rowFeatureMap;
    QMenu *itemMenu;

    void initRightedMenu();

signals:

    void zoomToFeatureSignal(GeoFeature *feature);

    void transToFeatureSignal(GeoFeature *feature);

    void selectFeatureSignal(GeoFeature *feature);

private slots:

    void on_searchButton_clicked();

    void on_zoomToFeature_action_triggered();

    void on_transToFeature_action_triggered();

    void on_fileTree_contextMenu_request(const QPoint &pos);

    void on_item_doubleClicked(QListWidgetItem *item);
};

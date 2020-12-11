#pragma once

#include <qwidget.h>
#include "ui_LayerColoursSet.h"
#include <qlist.h>

class LayerColoursSet : public QWidget {
Q_OBJECT
public:
    LayerColoursSet(QWidget *parent = 0);

    ~LayerColoursSet(void);

private:
    Ui::Form11 ui;
    int layerID;
    QString layerNAME;
    QList<QString> propsKey;
private slots:

    void setAttribute(int layerID, QString layerNAME, QList<QString> propsKey);

    void continueClick();

    void cancelClick();

signals:

    void setLayerClours(int layerID, QString attribute);
};


#pragma once

#include <qtablewidget.h>
#include <ui_AttributeTable.h>
#include "GeoLayer.h"

class AttributeTable : public QTableWidget {
Q_OBJECT
public:
    AttributeTable(QWidget *parent = 0);

    virtual ~AttributeTable(void);

private:
    Ui::Form8 ui;
private slots:

    void showAttri(CGeoLayer *layer);
};


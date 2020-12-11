#include "AttributeTable.h"


AttributeTable::AttributeTable(QWidget *parent)
        : QTableWidget(parent) {
    ui.setupUi(this);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


AttributeTable::~AttributeTable(void) {
}

void AttributeTable::showAttri(CGeoLayer *layer) {
    this->setRowCount(layer->geoObjects.size());
    this->setColumnCount(layer->getPropsKey().size() + 1);
    QStringList header;
    header << "FID";
    for (int i = 0; i < layer->getPropsKey().size(); i++) {
        header << layer->getPropsKey().at(i);
    }
    this->setHorizontalHeaderLabels(header);
    int count = 0;
    for (int i = 0; i < layer->geoObjects.size(); i++) {
        for (int j = 0; j < layer->getPropsKey().size() + 1; j++) {
            if (j == 0)
                this->setItem(count, j, new QTableWidgetItem(QString::number(count)));
            else
                this->setItem(count, j,
                              new QTableWidgetItem(layer->geoObjects[i]->getProps()[layer->getPropsKey().at(j - 1)]));
        }
        count++;
    }
    this->show();
}
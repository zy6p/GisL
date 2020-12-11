#include "SeekEleAttri.h"


SeekEleAttri::SeekEleAttri(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    fillColorXM = new XColorMaster(this);
    QLabel *label = new QLabel("fillcolor:");
    QFont font;
    font.setFamily(QStringLiteral("Arial Narrow:"));
    font.setPointSize(9);
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);
    label->setTextFormat(Qt::AutoText);
    label->setAlignment(Qt::AlignTop);
    ui.horizontalLayout_2->addWidget(label);
    ui.horizontalLayout_2->addWidget(fillColorXM);

    strokeColorXM = new XColorMaster(this);
    QLabel *label2 = new QLabel("strokeColor:");
    label2->setFont(font);
    label2->setTextFormat(Qt::AutoText);
    label2->setAlignment(Qt::AlignTop);
    ui.horizontalLayout_2->addWidget(label2);
    ui.horizontalLayout_2->addWidget(strokeColorXM);

    QLabel *label3 = new QLabel("strokeWidth:");
    label3->setFont(font);
    label3->setTextFormat(Qt::AutoText);
    label3->setAlignment(Qt::AlignCenter);
    ui.horizontalLayout_4->addWidget(label3);
    lineEdit = new QLineEdit();
    ui.horizontalLayout_4->addWidget(lineEdit);

}


SeekEleAttri::~SeekEleAttri(void) {
}

void SeekEleAttri::showAttri(CGeoObject *object, int objID) {
    this->objID = objID;
    ui.tableWidget->setRowCount(object->getProps().size() + 1);
    ui.tableWidget->setColumnCount(1);
    QStringList header;
    header << "TYPE";
    for (int i = 0; i < object->getProps().size(); i++) {
        header << object->getProps().keys().at(i);
    }
    ui.tableWidget->setVerticalHeaderLabels(header);
    for (int i = 0; i < object->getProps().size() + 1; i++) {
        if (i == 0)
            ui.tableWidget->setItem(i, 0, new QTableWidgetItem(object->getType()));
        else
            ui.tableWidget->setItem(i, 0,
                                    new QTableWidgetItem(object->getProps()[object->getProps().keys().at(i - 1)]));
    }
    this->show();
}

void SeekEleAttri::continueClick() {
    bool ok;
    float width = lineEdit->displayText().toFloat(&ok);
    emit sendColorAndWidthData(objID, fillColorXM->color, strokeColorXM->color, width);
}

void SeekEleAttri::cancelClick() {
    emit restore(objID);
}
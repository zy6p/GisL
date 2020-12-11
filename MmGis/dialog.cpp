#include "dialog.h"
#include "XColorMaster.h"
#include "XGradientSlider.h"
#include "XColorPreview.h"
#include "XColorDialog.h"
#include <QLayout>

Dialog::Dialog(QWidget *parent) :
        QDialog(parent) {
    ui.setupUi(this);
    //    XColorSquare* colorSquare = new XColorSquare(this);
    //    colorSquare->setColor(Qt::red);
    //    colorSquare->setCheckedColor('H');
    //    XColorPreview *color = new XColorPreview(this);
    //    color->setColor(Qt::red);

    //    XColorDialog *dialog = new XColorDialog(this);

    fillColorXM = new XColorMaster(this);
    QLabel *label = new QLabel("fillcolor:");
    QFont font;
    font.setFamily(QStringLiteral("Arial Narrow:"));
    font.setPointSize(9);
    font.setBold(true);
    font.setWeight(75);
    label->setFont(font);
    label->setTextFormat(Qt::AutoText);
    label->setAlignment(Qt::AlignCenter);
    ui.horizontalLayout_3->addWidget(label);
    ui.horizontalLayout_3->addWidget(fillColorXM);

    strokeColorXM = new XColorMaster(this);
    QLabel *label2 = new QLabel("strokeColor:");
    label2->setFont(font);
    label2->setTextFormat(Qt::AutoText);
    label2->setAlignment(Qt::AlignCenter);
    ui.horizontalLayout_3->addWidget(label2);
    ui.horizontalLayout_3->addWidget(strokeColorXM);
    //    XGradientSlider *slider = new XGradientSlider(this);
    //    slider->setFirstColor(Qt::red);
    //    slider->setLastColor(Qt::green);
    //    QVBoxLayout *hLayout = new QVBoxLayout;
    //    hLayout->addWidget(sc);
    //    hLayout->addWidget(slider);
    //    hLayout->addWidget(dialog);
    //    this->setLayout(hLayout);
    //    hLayout->addWidget(color);
    //    hLayout->addWidget(sc);
    //    setLayout(hLayout);
}

Dialog::~Dialog() {

}

void Dialog::continueClick() {
    bool ok;
    float width = ui.lineEdit->displayText().toFloat(&ok);
    emit sendColorAndWidthData(fillColorXM->color, strokeColorXM->color, width);
    this->close();
}

void Dialog::cancelClick() {
    this->close();
}
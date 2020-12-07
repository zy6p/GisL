//
// Created by omega on 7/12/2020.
//

#include <QtWidgets/QLabel>
#include <QtWidgets/QApplication>
#include <QString>

#include "mainwindow.h"
#include "dadecoder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    char filepath[] = "../practise_1/Encode3.da";
    DaDecoder decoder(filepath);
    QLabel *label = new QLabel;
    QString qDecodeText = QString::fromStdString(decoder.meaning);
    label->setText(qDecodeText);
    label->show();

    return app.exec();
}


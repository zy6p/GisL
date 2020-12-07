//
// Created by omega on 7/12/2020.
//


#include <QtWidgets/QApplication>
#include <QString>

#include "mainwindow.h"
//#include "dadecoder.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    char filepath[] = "../practise_1/Encode3.da";
//    DaDecoder decoder(filepath);
    MainWindow w;
    w.show();


    return app.exec();
}


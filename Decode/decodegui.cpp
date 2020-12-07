//
// Created by omega on 7/12/2020.
//


#include <QtWidgets/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.show();


    return app.exec();
}


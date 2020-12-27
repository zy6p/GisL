#include "mainwindow.h"

#include <QApplication>
#include "ckmap.h"
#include "ckpoint.h"

int main( int argc, char *argv[] ) {

    QApplication a( argc, argv );
    MainWindow w;
    w.show();

    CKMap map;
    char *path = "D:\\workstation\\teaching\\course\\oop gis\\practice\\practise_6\\data\\qu.geojson";
    path = "D:\\workstation\\teaching\\course\\oop gis\\practice\\practise_6\\data\\qu-style.sld";

    map.loadSLD( path );
    return a.exec();
}

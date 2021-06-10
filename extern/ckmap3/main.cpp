#include "mainwindow.h"

#include "ckmap.h"
#include "ckpoint.h"
#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);
  MainWindow w(0);
  w.show();

  //    CKMap map;
  //    char* path="D:\\workstation\\teaching\\course\\oop
  //    gis\\practice\\practise_6\\data\\qu.geojson";
  //    path="D:\\workstation\\teaching\\course\\oop
  //    gis\\practice\\practise_6\\data\\qu-style.sld";

  //    map.loadSLD(path);
  return a.exec();
}

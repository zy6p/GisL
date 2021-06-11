//
// Created by omega on 6/11/21.
//

#include <iostream>

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <src/core/layer/layertree.h>

#include "openrastercommand.h"

void gisl::OpenRasterCommand::testExecute(QWidget* parent) {
  fileName = "/home/km/mss/lfs/downloads/mcm2021b/gadm36_AUS_shp/freq.tif";
  this->pProvider = new gisl::RasterProvider();
  qDebug("the %s", fileName.c_str());
  for (int i = 0; i < 20; ++i) {
    qDebug("%i: %c", i, fileName.c_str()[i]);
  }
  pProvider->loadData(fileName);
  if (pProvider->hasError()) {
    Log* log = Log::getLog();
    QMessageBox::warning(
        parent,
        QObject::tr("RasterProvider Warning!"),
        log->getLast());
    return;
  }
}
void gisl::OpenRasterCommand::execute(QWidget* parent) {
  QString openFileName = QFileDialog::getOpenFileName(
      parent,
      QObject::tr("open an raster file."),
      "../",
      QObject::tr("all raster(*.*);;GeoTiff(*.tif)"),
      nullptr,
      QFileDialog::DontUseNativeDialog);
  if (openFileName.isEmpty()) {
    QMessageBox::warning(
        parent,
        QObject::tr("empty file Warning!"),
        QObject::tr("Cancel to open the file!"));
  } else {
    fileName = openFileName.toStdString();
    pProvider = new gisl::RasterProvider();
    pProvider->loadData(fileName);
    if (pProvider->hasError()) {
      Log* log = Log::getLog();
      QMessageBox::warning(
          parent,
          QObject::tr("RasterProvider Warning!"),
          log->getLast());
      return;
    }
  }
}
const std::string& gisl::OpenRasterCommand::output() {
  return this->mErrorMessage;
}
void gisl::OpenRasterCommand::reverse() {}
gisl::OpenRasterCommand::~OpenRasterCommand() {
  delete pProvider;
  pProvider = nullptr;
}
void gisl::OpenRasterCommand::getUi(Ui_MainWindow& p) { ui = &p; }

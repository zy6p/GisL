//
// Created by omega on 6/11/21.
//

#include <QFileDialog>
#include <QMessageBox>
#include <QObject>
#include <iostream>

#include "core/layer/layertree.h"
#include "gisl_config.h"
#include "gui/render/chooserasterrgbwidget.h"
#include "openrastercommand.h"

void gisl::OpenRasterCommand::testExecute(QWidget* parent) {
    fileName = "/home/km/dev/gisl/tests/data/rs/1/combination/gaojing_subset.tif";
    this->pProvider = new gisl::RasterProvider();
    qDebug("the %s", fileName.c_str());
    pProvider->loadData(fileName);
    if (pProvider->hasError()) {
        Log* log = Log::getLog();
        QMessageBox::warning(
            parent,
            QObject::tr("RasterProvider Warning!"),
            log->getLast());
        return;
    }
    LayerTree* layerTree = gisl::LayerTree::getLayerTree();
    layerTree->append(pProvider->getFid(), pProvider);
    ui->layerTreeWidget->updateLayerTree();
    auto* uiRasterChooseRgb = new ChooseRasterRgbWidget(parent);
    uiRasterChooseRgb->show();
    uiRasterChooseRgb->setPRasterProvider(pProvider);
}
void gisl::OpenRasterCommand::execute(QWidget* parent) {
    QString openFileName = QFileDialog::getOpenFileName(
                               parent,
                               QObject::tr("open an raster file."),
                               QString::fromStdString(STRINGIFY(TEST_DATA_DIR)),
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
        LayerTree* layerTree = gisl::LayerTree::getLayerTree();
        layerTree->append(pProvider->getFid(), pProvider);
        ui->layerTreeWidget->updateLayerTree();
        auto* uiRasterChooseRgb = new ChooseRasterRgbWidget(parent);
        uiRasterChooseRgb->show();
        uiRasterChooseRgb->setPRasterProvider(pProvider);
    }
}
const std::string& gisl::OpenRasterCommand::output() {
    return this->_errorMessage;
}
void gisl::OpenRasterCommand::reverse() {}
gisl::OpenRasterCommand::~OpenRasterCommand() {
    delete pProvider;
    pProvider = nullptr;
}
void gisl::OpenRasterCommand::getUi(Ui_MainWindow& p) {
    ui = &p;
}

#include <QFileDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "gui/command/command.h"
#include "gui/command/commandhistory.h"
#include "gui/command/openrastercommand.h"
#include "gui/command/opensldcommand.h"
#include "gui/command/openvectorcommand.h"
#include "utils/ptroperate.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  pCommandHistory = gisl::CommandHistory::getCommandHistory();
  ui->setupUi(this);
  setWindowTitle(tr("gisl"));

  setEnabled(true);
  initAction();
  initFileTree();
  setStatusMessage(tr("yes"));
  //  manualConnect();
#ifdef WITH_ANALYSIS
  this->registerAnalysis();
#endif
}

void MainWindow::initAction() {
  ui->actionCodecvtDecodeDecode->setEnabled(false);
  ui->actionCodecvtEncodeEncode->setEnabled(false);
  ui->actionCodecvtDecodeSave->setEnabled(false);
  ui->actionCodecvtEncodeSave->setEnabled(false);

  ui->actionVectorSave->setEnabled(false);
  ui->actionVectorSldSave->setEnabled(false);

  ui->actionRasterSave->setEnabled(false);
}

void MainWindow::initFileTree() {
  auto* model = new QFileSystemModel;
  model->setRootPath(QDir::currentPath());
  ui->fileTreeView->setModel(model);
}

void MainWindow::manualConnect() {
  QObject::connect(
      ui->actionVectorOpen,
      &QAction::triggered,
      this,
      &MainWindow::on_actionVectorOpen_triggered);
  QObject::connect(
      ui->actionVectorSldOpen,
      &QAction::triggered,
      this,
      &MainWindow::on_actionVectorSldOpen_triggered);
  QObject::connect(
      ui->actionRasterOpen,
      &QAction::triggered,
      this,
      &MainWindow::on_actionRasterOpen_triggered);
  QObject::connect(
      ui->actionCodecvtDecodeOpen,
      &QAction::triggered,
      this,
      &MainWindow::on_actionCodecvtDecodeOpen_triggered);
  QObject::connect(
      ui->actionCodecvtDecodeDecode,
      &QAction::triggered,
      this,
      &MainWindow::on_actionCodecvtDecodeDecode_triggered);
  QObject::connect(
      ui->actionCodecvtDecodeSave,
      &QAction::triggered,
      this,
      &MainWindow::on_actionCodecvtDecodeSave_triggered);
  QObject::connect(
      ui->actionCodecvtEncodeOpen,
      &QAction::triggered,
      this,
      &MainWindow::on_actionCodecvtEncodeOpen_triggered);
  QObject::connect(
      ui->actionCodecvtEncodeEncode,
      &QAction::triggered,
      this,
      &MainWindow::on_actionCodecvtEncodeEncode_triggered);
  QObject::connect(
      ui->actionCodecvtEncodeSave,
      &QAction::triggered,
      this,
      &MainWindow::on_actionCodecvtEncodeSave_triggered);
  QObject::connect(
      ui->actionUndo,
      &QAction::triggered,
      this,
      &MainWindow::on_actionUndo_triggered);
  QObject::connect(
      ui->actionRedo,
      &QAction::triggered,
      this,
      &MainWindow::on_actionRedo_triggered);
}

void MainWindow::on_actionUndo_triggered() { pCommandHistory->rollBack(1); }

void MainWindow::on_actionRedo_triggered() {}

void MainWindow::on_actionVectorOpen_triggered() {
  auto* p = new gisl::OpenVectorCommand;
  p->getUi(*ui);
  p->execute(this);
  pCommandHistory->push(p, tr("Open ").toStdString() + p->output());
  setStatusMessage(tr("Open ") + QString::fromStdString(p->output()));
  ui->actionVectorSave->setEnabled(true);
  ui->actionVectorSldSave->setEnabled(true);
}

void MainWindow::on_actionVectorSldOpen_triggered() {
  gisl::Command* p = new gisl::OpenSldCommand;
  p->execute(this);
  pCommandHistory->push(p, tr("Open ").toStdString() + p->output());
  ui->actionVectorSldSave->setEnabled(true);
}

void MainWindow::on_actionCodecvtDecodeOpen_triggered() {
  QString openFileName = QFileDialog::getOpenFileName(
      nullptr,
      tr("open an decode file."),
      "",
      tr("Decode File(*.da);;All files(*.*)"));
  if (openFileName.isEmpty()) {
    QMessageBox::warning(
        nullptr,
        tr("Warning!"),
        tr("Cancel to open the file!"));
  } else {
    gisl::PtrOperate::clear(pDecoder);
    pDecoder = new gisl::DaDecoder(openFileName.toStdString());
    ui->actionCodecvtDecodeDecode->setEnabled(true);
    ui->actionCodecvtDecodeSave->setEnabled(true);
  }
}

void MainWindow::on_actionCodecvtDecodeDecode_triggered() {
  pDecoder->decode();
  QString qDecodeText = QString::fromStdString(pDecoder->getTextInOrder());
  QMessageBox::information(this, "text", qDecodeText);
}

void MainWindow::on_actionCodecvtDecodeSave_triggered() {
  QString outFilename = QFileDialog::getSaveFileName(
      this,
      tr("Save File as txt"),
      "",
      tr("Text(*.txt);;all(*.*)"));
  if (outFilename.isEmpty()) {
    QMessageBox::warning(this, tr("Warning!"), tr("Cancel to open the file!"));
  } else {
    pDecoder->writeTextFile(outFilename.toStdString());
  }
}

void MainWindow::on_actionCodecvtEncodeOpen_triggered() {
  QString openFileName = QFileDialog::getOpenFileName(
      this,
      tr("open an decode file."),
      "",
      tr("Decode File(*.da);;All files(*.*)"));
  if (openFileName.isEmpty()) {
    QMessageBox::warning(this, tr("Warning!"), tr("Cancel to open the file!"));
  } else {
    gisl::PtrOperate::clear(pDecoder);
    pDecoder = new gisl::DaDecoder(openFileName.toStdString());
    ui->actionCodecvtDecodeDecode->setEnabled(true);
    ui->actionCodecvtDecodeSave->setEnabled(true);
  }
}

void MainWindow::on_actionCodecvtEncodeEncode_triggered() {
  QString qText = QString::fromStdString(pEncoder->getTextInOrder());
  QMessageBox::information(this, "text", qText);
  pEncoder->encode();
}

void MainWindow::on_actionCodecvtEncodeSave_triggered() {
  QString outFilename = QFileDialog::getSaveFileName(
      this,
      tr("Save File as decode"),
      "",
      tr("decode(*.da);;all(*.*)"));
  if (outFilename.isEmpty()) {
    QMessageBox::warning(this, tr("Warning!"), tr("Cancel to open the file!"));
  } else {
    pEncoder->writeBinaryFile(outFilename.toStdString());
  }
}

void MainWindow::paintEvent(QPaintEvent* event) {
  //    QWidget::paintEvent( event );
  //    QPainter painter(this);
  //
  //    painter.setPen(Qt::black);
  //    for ( auto pLayer : ui->openGLWidget->mLayer ) {
  //        for ( int i = 0; i < pLayer->getFeatureCount(); ++i ) {
  //            auto labelPosF = ui->openGLWidget->projMatrix.map(
  //            pLayer->getFeature()[i]->boundary()->center()); labelPosF =
  //            ui->openGLWidget->scaleMatrix.map( labelPosF ); labelPosF.setX((
  //            labelPosF.x() + 1 ) * this->size().width()); labelPosF.setY((
  //            labelPosF.y() + 1 ) * this->size().height());
  //            painter.drawText(labelPosF.toPoint(), QString((
  //            pLayer->getFeature()[i]->getFieldAsString(
  //            ui->openGLWidget->pmSld->getPropertyName()).c_str())));
  //        }
  //    }
}

void MainWindow::setStatusMessage(const QString& s, int timeout) {
  ui->statusBar->showMessage(s, timeout);
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {

  setStatusMessage(tr("Pos at (")
                       .append(QString::number(event->x()))
                       .append(", ")
                       .append(QString::number(event->y())));
}
void MainWindow::on_actionRasterOpen_triggered() {
  auto* p = new gisl::OpenRasterCommand();
  p->getUi(*ui);
  p->execute(this);
  pCommandHistory->push(p, tr("Open ").toStdString() + p->output());
  setStatusMessage(tr("Open ") + QString::fromStdString(p->output()));
  ui->actionRasterSave->setEnabled(true);
}
#ifdef WITH_ANALYSIS
void MainWindow::registerAnalysis() {
  auto* analysisMenu = this->ui->menubar->addMenu(tr("Analysis"));
  for (const auto& [algEnum, algStr] : *this->pAnalysis->registerAll()) {
    const QAction* pAction = analysisMenu->addAction(algStr);
    QObject::connect(
        pAction,
        &QAction::triggered,
        this->pAnalysis->buildAlg(
            gisl::Analysis::AnalysisAlgEnum(algEnum),
            this),
        &gisl::AnalysisAlg::initGui);
  }
}
#endif

MainWindow::~MainWindow() = default;

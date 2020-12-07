#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets/QLabel>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    createMenu();
}

void MainWindow::createMenu() {

    QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openDecodeFile);
    QObject::connect(ui->actionDecode, &QAction::triggered, this, &MainWindow::decodeMessage);
    QObject::connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::saveTextFile);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openDecodeFile() {
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("open an encode file."),
            "../",
            tr("Encode File(*.da);;All files(*.*)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
    } else {
        this->openFileName = fileName;
    }
}

void MainWindow::decodeMessage() {
    QByteArray openFilenameByteArray = openFileName.toLatin1();
    daDecoder.getFilename(openFilenameByteArray.data());
    auto *label = new QLabel;
    qDecodeText = QString::fromStdString(daDecoder.meaning);
    label->setText(qDecodeText);
    label->show();
}

void MainWindow::saveTextFile() {
    QString outFilename = QFileDialog::getSaveFileName(
            this,
            tr("Save Decode File as txt"),
            "../",
            tr("Decode Text(*.txt);;all(*.*)")
    );
    QByteArray outFilenameByteArray = openFileName.toLatin1();
    daDecoder.writeIntoFile(outFilenameByteArray.data());
}

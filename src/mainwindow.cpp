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

    QObject::connect(ui->actionMFileDecodeOpen, &QAction::triggered, this, &MainWindow::aFileDecodeOpen);
    QObject::connect(ui->actionMFileDecodeDecode, &QAction::triggered, this, &MainWindow::aFileDecodeDecode);
    QObject::connect(ui->actionMFileDecodeSave, &QAction::triggered, this, &MainWindow::aFileDecodeSave);
    QObject::connect(ui->actionMFileEncodeOpen, &QAction::triggered, this, &MainWindow::aFileEncodeOpen);
    QObject::connect(ui->actionMFileEncodeEncode, &QAction::triggered, this, &MainWindow::aFileEncodeEncode);
    QObject::connect(ui->actionMFileEncodeSave, &QAction::triggered, this, &MainWindow::aFileEncodeSave);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::aFileDecodeOpen() {
    QString openFileName = QFileDialog::getOpenFileName(
            this,
            tr("open an decode file."),
            "../",
            tr("Decode File(*.da);;All files(*.*)"));
    if (openFileName.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
    } else {
        daDecoder.clear();
        daDecoder.loadBinaryFile(openFileName.toStdString());
    }
}

void MainWindow::aFileDecodeDecode() {
    auto *label = new QLabel;
    daDecoder.decode();
    QString qDecodeText = QString::fromStdString(daDecoder.getTextInOrder());
    label->setText(qDecodeText);
    label->show();
}

void MainWindow::aFileDecodeSave() {
    QString outFilename = QFileDialog::getSaveFileName(
            this,
            tr("Save File as txt"),
            "../",
            tr("Text(*.txt);;all(*.*)"));
    if (outFilename.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
    } else {
        daDecoder.writeTextFile(outFilename.toStdString());
    }
}

void MainWindow::aFileEncodeOpen() {
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("open an encode file."),
            "../",
            tr("Encode File(*.txt);;All files(*.*)"));
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
    } else {
        daEncoder.clear();
        daEncoder.loadTextFile2Text(fileName.toStdString());
    }
}

void MainWindow::aFileEncodeEncode() {
    auto *label = new QLabel;
    QString qText = QString::fromStdString(daEncoder.getTextInOrder());
    label->setText(qText);
    label->show();
    daEncoder.encode();
}

void MainWindow::aFileEncodeSave() {
    QString outFilename = QFileDialog::getSaveFileName(
            this,
            tr("Save File as decode"),
            "../",
            tr("decode(*.da);;all(*.*)"));
    if (outFilename.isEmpty()) {
        QMessageBox::warning(this, "Warning!", "Failed to open the file!");
    } else {
        daEncoder.writeBinaryFile(outFilename.toStdString());
    }
}


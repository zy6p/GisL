/*!
 * @file manubar.cpp.cc
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details 
 * @verbatim
 *
 */

#include "./ui_mainwindow.h"
#include <QtWidgets/QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include "menubar.h"

namespace GisL {


    MenuBar::MenuBar( QMenuBar &poMenuBar ) : GisLObject() {
        pmMenuBar = &poMenuBar;

    }


    void MenuBar::connectMenu() {

        QObject::connect(ui->actionMFileDecodeOpen, &QAction::triggered, this, &MenuBar::aFileDecodeOpen);
        QObject::connect(ui->actionMFileDecodeDecode, &QAction::triggered, this, &MenuBar::aFileDecodeDecode);
        QObject::connect(ui->actionMFileDecodeSave, &QAction::triggered, this, &MenuBar::aFileDecodeSave);
        QObject::connect(ui->actionMFileEncodeOpen, &QAction::triggered, this, &MenuBar::aFileEncodeOpen);
        QObject::connect(ui->actionMFileEncodeEncode, &QAction::triggered, this, &MenuBar::aFileEncodeEncode);
        QObject::connect(ui->actionMFileEncodeSave, &QAction::triggered, this, &MenuBar::aFileEncodeSave);
    }


    void MenuBar::aFileDecodeOpen() {
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

    void MenuBar::aFileDecodeDecode() {
        auto *label = new QLabel;
        daDecoder.decode();
        QString qDecodeText = QString::fromStdString(daDecoder.getTextInOrder());
        label->setText(qDecodeText);
        label->show();
    }

    void MenuBar::aFileDecodeSave() {
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

    void MenuBar::aFileEncodeOpen() {
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

    void MenuBar::aFileEncodeEncode() {
        auto *label = new QLabel;
        QString qText = QString::fromStdString(daEncoder.getTextInOrder());
        label->setText(qText);
        label->show();
        daEncoder.encode();
    }

    void MenuBar::aFileEncodeSave() {
        QString outFilename = QFileDialog::getSaveFileName(
                this,
                tr( "Save File as decode" ),
                "../",
                tr( "decode(*.da);;all(*.*)" ));
        if ( outFilename.isEmpty()) {
            QMessageBox::warning( this, "Warning!", "Failed to open the file!" );
        } else {
            daEncoder.writeBinaryFile( outFilename.toStdString());
        }
    }
}
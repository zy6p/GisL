/*!
 * @file manubar.cpp
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details
 *
 */

#include "./ui_mainwindow.h"

#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include "menubar.h"

namespace GisL {


    MenuBar::MenuBar( Ui_MainWindow &poUi, QWidget &poWidget ) : GisLObject() {
        pmUi = &poUi;
        pmMenuBar = pmUi->menubar;
        pmWidget = &poWidget;

        pDecoder = nullptr;
        pEncoder = nullptr;

        connectMenu();
    }

    void MenuBar::connectMenu( ) {

        QObject::connect( pmUi->actionMFileDecodeOpen, &QAction::triggered, this, &MenuBar::aFileDecodeOpen );
        QObject::connect( pmUi->actionMFileDecodeDecode, &QAction::triggered, this, &MenuBar::aFileDecodeDecode );
        QObject::connect( pmUi->actionMFileDecodeSave, &QAction::triggered, this, &MenuBar::aFileDecodeSave );
        QObject::connect( pmUi->actionMFileEncodeOpen, &QAction::triggered, this, &MenuBar::aFileEncodeOpen );
        QObject::connect( pmUi->actionMFileEncodeEncode, &QAction::triggered, this, &MenuBar::aFileEncodeEncode );
        QObject::connect( pmUi->actionMFileEncodeSave, &QAction::triggered, this, &MenuBar::aFileEncodeSave );
    }


    void MenuBar::aFileDecodeOpen() {
        QString openFileName = QFileDialog::getOpenFileName(
                this,
                tr("open an decode file."),
                "../",
                tr("Decode File(*.da);;All files(*.*)"));
        if (openFileName.isEmpty()) {
            QMessageBox::warning( pmWidget, "Warning!", "Failed to open the file!" );
        } else {
            if ( nullptr != pDecoder ) {
                delete pDecoder;
                pDecoder = nullptr;
            }
            pDecoder = new DaDecoder( openFileName.toStdString());
        }
    }

    void MenuBar::aFileDecodeDecode() {
        auto *label = new QLabel;
        pDecoder->decode();
        QString qDecodeText = QString::fromStdString( pDecoder->getTextInOrder());
        label->setText( qDecodeText );
        label->show();
    }

    void MenuBar::aFileDecodeSave() {
        QString outFilename = QFileDialog::getSaveFileName(
                this,
                tr("Save File as txt"),
                "../",
                tr("Text(*.txt);;all(*.*)"));
        if (outFilename.isEmpty()) {
            QMessageBox::warning( pmWidget, "Warning!", "Failed to open the file!" );
        } else {
            pDecoder->writeTextFile( outFilename.toStdString());
        }
    }

    void MenuBar::aFileEncodeOpen() {
        QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("open an encode file."),
                "../",
                tr("Encode File(*.txt);;All files(*.*)"));
        if (fileName.isEmpty()) {
            QMessageBox::warning( pmWidget, "Warning!", "Failed to open the file!" );
        } else {
            if ( nullptr != pEncoder ) {
                delete pEncoder;
                pEncoder = nullptr;
            }

            pEncoder = new DaEncoder;
            pEncoder->loadTextFile2Text( fileName.toStdString());
        }
    }

    void MenuBar::aFileEncodeEncode() {
        auto *label = new QLabel;
        QString qText = QString::fromStdString( pEncoder->getTextInOrder());
        label->setText(qText);
        label->show();
        pEncoder->encode();
    }

    void MenuBar::aFileEncodeSave() {
        QString outFilename = QFileDialog::getSaveFileName(
                this,
                tr( "Save File as decode" ),
                "../",
                tr( "decode(*.da);;all(*.*)" ));
        if ( outFilename.isEmpty()) {
            QMessageBox::warning( pmWidget, "Warning!", "Failed to open the file!" );
        } else {
            pEncoder->writeBinaryFile( outFilename.toStdString());
        }
    }
}
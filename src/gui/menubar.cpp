/*!
 * @file menubar.cpp
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief
 * @details
 *
 */

#include "menubar.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "command/commandhistory.h"
#include "glcanvas.h"
#include "command/command.h"
#include "command/openvectorcommand.h"
#include "../utils/ptroperate.h"


MenuBar::MenuBar( QWidget *parent ) : QMenuBar( parent ) {

    pmWidget = parent;
    connectMenu();

    pDecoder = nullptr;
    pEncoder = nullptr;
    pVector = nullptr;
    pSld = nullptr;


//    pmUi->actionCodecvtDecodeDecode->setEnabled( false );
//    pmUi->actionCodecvtEncodeEncode->setEnabled( false );
//    pmUi->actionCodecvtDecodeSave->setEnabled( false );
//    pmUi->actionCodecvtEncodeSave->setEnabled( false );
//
//    pmUi->actionVectorSave->setEnabled( false );
//    pmUi->actionVectorSldSave->setEnabled( false );
//
//    pmUi->actionRasterSave->setEnabled( false );

}

void MenuBar::connectMenu( ) {
//    QObject::connect( pmUi->actionVectorOpen, &QAction::triggered, this, &MenuBar::aVectorOpen );
//    QObject::connect( pmUi->actionVectorSldOpen, &QAction::triggered, this, &MenuBar::aVectorSldOpen );
//    QObject::connect( pmUi->actionCodecvtDecodeOpen, &QAction::triggered, this,
//                      &MenuBar::aCodecvtDecodeOpen );
//    QObject::connect( pmUi->actionCodecvtDecodeDecode, &QAction::triggered, this,
//                      &MenuBar::aCodecvtDecodeDecode );
//    QObject::connect( pmUi->actionCodecvtDecodeSave, &QAction::triggered, this,
//                      &MenuBar::aCodecvtDecodeSave );
//    QObject::connect( pmUi->actionCodecvtEncodeOpen, &QAction::triggered, this,
//                      &MenuBar::aCodecvtEncodeOpen );
//    QObject::connect( pmUi->actionCodecvtEncodeEncode, &QAction::triggered, this,
//                      &MenuBar::aCodecvtEncodeEncode );
//    QObject::connect( pmUi->actionCodecvtEncodeSave, &QAction::triggered, this,
//                      &MenuBar::aCodecvtEncodeSave );
}

void MenuBar::aVectorOpen( ) {
    GisL::Command *p = new GisL::OpenVectorCommand;
    p->execute();
    GisL::CommandHistory::append( *p );

//    pmUi->actionVectorSave->setEnabled( true );
//    pmUi->actionVectorSldSave->setEnabled( true );

}

void MenuBar::aVectorSldOpen( ) {
    QString openFileName = QFileDialog::getOpenFileName(
            pmWidget,
            QString( "open an sld file." ),
            "../",
            QString( "Sld(*.sld);;All files(*.*)" ));
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( pmWidget, "Warning!", "Cancel to open the file!" );
    } else {
        GisL::PtrOperate::clear( pSld );
        pSld = new GisL::Sld( openFileName.toStdString());
//        pmUi->actionVectorSldSave->setEnabled( true );
    }
}

void MenuBar::aCodecvtDecodeOpen( ) {
    QString openFileName = QFileDialog::getOpenFileName(
            pmWidget,
            QString( "open an decode file." ),
            "../",
            QString( "Decode File(*.da);;All files(*.*)" ));
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( pmWidget, "Warning!", "Cancel to open the file!" );
    } else {
        GisL::PtrOperate::clear( pDecoder );
        pDecoder = new GisL::DaDecoder( openFileName.toStdString());
//        pmUi->actionCodecvtDecodeDecode->setEnabled( true );
//        pmUi->actionCodecvtDecodeSave->setEnabled( true );
    }
}

void MenuBar::aCodecvtDecodeDecode( ) {
//        auto *label = new QLabel;
    pDecoder->decode();
    QString qDecodeText = QString::fromStdString( pDecoder->getTextInOrder());
//        label->setText( qDecodeText );
//        label->show();
    QMessageBox::information( pmWidget, "text", qDecodeText );
}

void MenuBar::aCodecvtDecodeSave( ) {
    QString outFilename = QFileDialog::getSaveFileName(
            pmWidget,
            QString( "Save File as txt" ),
            "../",
            QString( "Text(*.txt);;all(*.*)" ));
    if ( outFilename.isEmpty()) {
        QMessageBox::warning( pmWidget, "Warning!", "Cancel to open the file!" );
    } else {
        pDecoder->writeTextFile( outFilename.toStdString());
    }
}

void MenuBar::aCodecvtEncodeOpen( ) {
    QString fileName = QFileDialog::getOpenFileName(
            pmWidget,
            QString( "open an encode file." ),
            "../",
            QString( "Encode File(*.txt);;All files(*.*)" ));
    if ( fileName.isEmpty()) {
        QMessageBox::warning( pmWidget, "Warning!", "Cancel to open the file!" );
    } else {
        GisL::PtrOperate::clear( pEncoder );

        pEncoder = new GisL::DaEncoder;
        pEncoder->loadTextFile2Text( fileName.toStdString());
//        pmUi->actionCodecvtEncodeEncode->setEnabled( true );
//        pmUi->actionCodecvtEncodeSave->setEnabled( true );
    }
}

void MenuBar::aCodecvtEncodeEncode( ) {
//        auto *label = new QLabel;
    QString qText = QString::fromStdString( pEncoder->getTextInOrder());
//        label->setText(qText);
//        label->show();
    QMessageBox::information( pmWidget, "text", qText );
    pEncoder->encode();
}

void MenuBar::aCodecvtEncodeSave( ) {
    QString outFilename = QFileDialog::getSaveFileName(
            pmWidget,
            QString( "Save File as decode" ),
            "../",
            QString( "decode(*.da);;all(*.*)" ));
    if ( outFilename.isEmpty()) {
        QMessageBox::warning( pmWidget, "Warning!", "Cancel to open the file!" );
    } else {
        pEncoder->writeBinaryFile( outFilename.toStdString());
    }
}

MenuBar::~MenuBar( ) {
    GisL::PtrOperate::clear( pEncoder );
    GisL::PtrOperate::clear( pDecoder );
    GisL::PtrOperate::clear( pVector );
    GisL::PtrOperate::clear( pSld );
}

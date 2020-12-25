#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QAction>

#include "menubar.h"
#include "canvas.h"

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );

    pmMenuBar = new GisL::MenuBar( *ui, *this );
//    connectMenu();

    pmCanvas = new GisL::Canvas( *ui );

}

//void MainWindow::connectMenu( ) {
////    QObject::connect( ui->actionMFileDecodeOpen, &QAction::triggered, this, SLOT(GisL::MenuBar::aCodecvtDecodeOpen));
////    QObject::connect( ui->actionMFileDecodeOpen, &QAction::triggered, pmMenuBar, &GisL::MenuBar::aCodecvtDecodeOpen );
////    QObject::connect( ui->actionMFileDecodeDecode, &QAction::triggered, pmMenuBar, &GisL::MenuBar::aCodecvtDecodeDecode );
////    QObject::connect( ui->actionMFileDecodeSave, &QAction::triggered, pmMenuBar, &GisL::MenuBar::aCodecvtDecodeSave );
////    QObject::connect( ui->actionMFileEncodeOpen, &QAction::triggered, pmMenuBar, &GisL::MenuBar::aCodecvtEncodeOpen );
////    QObject::connect( ui->actionMFileEncodeEncode, &QAction::triggered, pmMenuBar, &GisL::MenuBar::aCodecvtEncodeEncode );
////    QObject::connect( ui->actionMFileEncodeSave, &QAction::triggered, pmMenuBar, &GisL::MenuBar::aCodecvtEncodeSave );
//    QObject::connect( ui->actionMFileDecodeOpen, &QAction::triggered, this, SLOT(&GisL::MenuBar::aCodecvtDecodeOpen ));
//    QObject::connect( ui->actionMFileDecodeDecode, &QAction::triggered, this, SLOT(&GisL::MenuBar::aCodecvtDecodeDecode ));
//    QObject::connect( ui->actionMFileDecodeSave, &QAction::triggered, this, SLOT(&GisL::MenuBar::aCodecvtDecodeSave ));
//    QObject::connect( ui->actionMFileEncodeOpen, &QAction::triggered, this, SLOT(&GisL::MenuBar::aCodecvtEncodeOpen ));
//    QObject::connect( ui->actionMFileEncodeEncode, &QAction::triggered, this, SLOT(&GisL::MenuBar::aCodecvtEncodeEncode ));
//    QObject::connect( ui->actionMFileEncodeSave, &QAction::triggered, this, SLOT(&GisL::MenuBar::aCodecvtEncodeSave ));
//}

MainWindow::~MainWindow( ) {
    if ( nullptr != pmMenuBar ) {
        delete pmMenuBar;
        pmMenuBar = nullptr;
    }

    if ( nullptr != pmCanvas ) {
        delete pmCanvas;
        pmCanvas = nullptr;
    }

    if ( nullptr != ui ) {
        delete ui;
        ui = nullptr;
    }

}


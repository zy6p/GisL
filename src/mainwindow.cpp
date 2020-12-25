#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gui/menubar.h"
#include "gui/canvas.h"

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );


    pmMenuBar = new GisL::MenuBar( *ui, *this );

    pmCanvas = new GisL::Canvas( *ui );

}

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


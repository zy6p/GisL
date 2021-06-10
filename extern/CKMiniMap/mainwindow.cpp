#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <iostream>
#include <QFileDialog>
#include <QDebug>

using namespace std;

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );
    pMap = 0x00;
}

MainWindow::~MainWindow( ) {
    if ( pMap != 0x00 ) {
        delete pMap;
        pMap = 0x00;
    }
    delete ui;
}


void MainWindow::on_action_open_sld_triggered( ) {
    file_name = QFileDialog::getOpenFileName( this, "打开Styled Layer Description文件", "d:/", tr( "SLD(*.sld)" ));
    qDebug() << file_name << endl;
    if ( pMap == 0x00 )
        pMap = new CKMap;


    pMap->loadSLD( file_name.toStdString().c_str());
}

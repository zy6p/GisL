#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGridLayout>

#include "menubar.h"
#include "glcanvas.h"
#include "../utils/ptroperate.h"

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );

    pCanvas = new GisL::GlCanvas( this );
    ui->openGLWidget = pCanvas;

    ui->menubar = new GisL::MenuBar( *ui, *this, *pCanvas);

    pmGeoInfo = new QLabel( tr( "GeoInfo" ));


//    auto *layout = new QGridLayout;
//    layout->addWidget(ui->openGLWidget, 0, 0);
//    layout->addWidget(pmGeoInfo, 1, 0);
//    setLayout(layout);

    setWindowIcon( QIcon( ":../../docs/kfc.png" ));
    setWindowTitle( tr( "GisL" ));

}

MainWindow::~MainWindow( ) {
//    GisL::PtrOperate::clear( pCanvas );
//    GisL::PtrOperate::clear( ui->menubar );
//    GisL::PtrOperate::clear( ui->openGLWidget );
//    GisL::PtrOperate::clear( ui );

}


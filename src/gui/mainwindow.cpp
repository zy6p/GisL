#include "mainwindow.h"
#include "../ui/ui_mainwindow.h"
//#include "../ui/ui_backup.h"

#include <src/gui/command/command.h>
#include <src/gui/command/commandhistory.h>
#include <src/gui/command/openvectorcommand.h>
//#include "glcanvas.h"
#include "../utils/ptroperate.h"

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent ), ui( new Ui::MainWindow ) {
    ui->setupUi( this );
    setWindowTitle( tr( "GisL" ));
}

void MainWindow::manualConnect() {
//    connect(ui->actionVectorOpen, &QAction::triggered, this, &MainWindow::on_actionVectorOpen_triggered);
}

void MainWindow::on_actionVectorOpen_triggered( ) {
    GisL::Command *p = new GisL::OpenVectorCommand;
    p->execute();
    GisL::CommandHistory::append( *p );

    ui->actionVectorSave->setEnabled( true );
    ui->actionVectorSldSave->setEnabled( true );

}

MainWindow::~MainWindow( ) = default;


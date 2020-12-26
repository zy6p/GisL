#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "glcanvas.h"
#include "menubar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = nullptr );

    ~MainWindow( ) override;

private:
    Ui::MainWindow *ui;

//    GisL::MenuBar *pmMenuBar;

//    void connectMenu( );
};

#endif // MAINWINDOW_H

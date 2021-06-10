#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ckmap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow( QWidget *parent = nullptr );

    ~MainWindow( );

private slots:

    void on_action_open_sld_triggered( );//打开sld文件

private:
    Ui::MainWindow *ui;

    //created by kmj 2020/12/27
    QString file_name;
    CKMap *pMap;
};

#endif // MAINWINDOW_H

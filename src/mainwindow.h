#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gui/canvas.h"
#include "gui/menubar.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MainWindow *ui;

    GisL::DaDecoder daDecoder;
    GisL::DaEncoder daEncoder;

    GisL::Canvas *pmCanvas;
    GisL::MenuBar *pmMenuBar;

};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QtWidgets/QLabel>
#include <QFileDialog>
#include <QMessageBox>

#include "gui/menubar.h"
#include "gui/canvas.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);


    pmCanvas = new GisL::Canvas(*ui->openGLWidget);

}

}


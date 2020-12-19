#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/Codecvt/dadecoder.h"
#include "src/Codecvt/daencoder.h"

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
//    QString inDecodeFilename;
//    QString qDecodeText;
    GisL::DaDecoder daDecoder;
    GisL::DaEncoder daEncoder;

    void createMenu();

    void aFileDecodeOpen();

    void aFileDecodeDecode();

    void aFileDecodeSave();

    void aFileEncodeOpen();

    void aFileEncodeEncode();

    void aFileEncodeSave();
};

#endif // MAINWINDOW_H

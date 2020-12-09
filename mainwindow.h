#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dadecoder.h"

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
    QString openFileName;
    QString qDecodeText;
    DaDecoder daDecoder;

    void openDecodeFile();

    void decodeMessage();

    void createMenu();

    void saveTextFile();
};

#endif // MAINWINDOW_H

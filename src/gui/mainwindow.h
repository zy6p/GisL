#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>

#include "../codecvt/dadecoder.h"
#include "../codecvt/daencoder.h"
#include "command/commandhistory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);

  void setStatusMessage(const QString &s, int timeout = 0);

  ~MainWindow() override;

public slots:

  void on_actionVectorOpen_triggered();

  void on_actionVectorSldOpen_triggered();

  void on_actionCodecvtDecodeSave_triggered();

  void on_actionCodecvtEncodeOpen_triggered();

  void on_actionCodecvtDecodeOpen_triggered();

  void on_actionCodecvtDecodeDecode_triggered();

  void on_actionCodecvtEncodeEncode_triggered();

  void on_actionCodecvtEncodeSave_triggered();

private:
protected:
  void mouseMoveEvent(QMouseEvent *event) override;

  void paintEvent(QPaintEvent *event) override;

private:
  gisl::CommandHistory *pCommandHistory;

  Ui::MainWindow *ui;

  gisl::DaDecoder *pDecoder = nullptr;
  gisl::DaEncoder *pEncoder = nullptr;

  void manualConnect();

  void initAction();

  void on_actionUndo_triggered();

  void on_actionRedo_triggered();

  void initFileTree();
};

#endif // MAINWINDOW_H

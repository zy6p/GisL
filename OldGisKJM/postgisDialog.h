#ifndef POSTGISDIALOG_H
#define POSTGISDIALOG_H

#include <QDialog>
#include<QVector>
#include<QDebug>
#include"ogrsf_frmts.h"

namespace Ui {
    class postgisDialog;
}

class PostgisDialog : public QDialog {
Q_OBJECT

public:
    explicit PostgisDialog(QWidget *parent = nullptr);

    ~PostgisDialog();

    //获取对话框中的信息
    QString getUsername();

    QString getPassword();

    QString getLocalhost();

    QString getPort();

    QString getDatabase();

    QString getLayername();

    QString getPath();

private slots:

    void on_Ok_clicked();

    void on_Cancel_clicked();

    void on_pushButton_clicked();

private:
    Ui::postgisDialog *ui;
    QVector<QString> Layernames;
    QString dbname;
    QString host;
    QString port;
    QString user;
    QString password;
    QString selectedLayer;
};

#endif // POSTGISDIALOG_H

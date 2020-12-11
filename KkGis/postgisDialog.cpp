#ifndef POSTGISDIALOG_H
#define POSTGISDIALOG_H

#include <QDialog>
#include<QVector>
#include<QDebug>
#include"ogrsf_frmts.h"

namespace Ui {
class postgisDialog;
}

class PostgisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PostgisDialog(QWidget *parent = nullptr);
    ~PostgisDialog();

    //
#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "XColorMaster.h"
#include "ui_dialog.h"

namespace Ui {
    class Dialog;
}

class Dialog : public QDialog {
Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);

    ~Dialog();

    enum CheckedColor {
        H, S, V, R, G, B
    } checkedColor;
    XColorMaster *fillColorXM;
    XColorMaster *strokeColorXM;
private:
    Ui::Form7 ui;

private slots:

    void continueClick();

    void cancelClick();

signals:

    void sendColorAndWidthData(QColor fillColor, QColor strokeColor, float width);//������Ⱦ�ź�
};

#endif // DIALOG_H

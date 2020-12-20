/********************************************************************************
** Form generated from reading UI file 'StretchStyleDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STRETCHSTYLEDIALOG_H
#define UI_STRETCHSTYLEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StretchStyleDialog
{
public:

    void setupUi(QWidget *StretchStyleDialog)
    {
        if (StretchStyleDialog->objectName().isEmpty())
            StretchStyleDialog->setObjectName(QString::fromUtf8("StretchStyleDialog"));
        StretchStyleDialog->resize(400, 300);

        retranslateUi(StretchStyleDialog);

        QMetaObject::connectSlotsByName(StretchStyleDialog);
    } // setupUi

    void retranslateUi(QWidget *StretchStyleDialog)
    {
        StretchStyleDialog->setWindowTitle(QCoreApplication::translate("StretchStyleDialog", "StretchStyleDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StretchStyleDialog: public Ui_StretchStyleDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STRETCHSTYLEDIALOG_H

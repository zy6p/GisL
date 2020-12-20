/********************************************************************************
** Form generated from reading UI file 'AccessAnalysisDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCESSANALYSISDIALOG_H
#define UI_ACCESSANALYSISDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccessAnalysisDialog
{
public:

    void setupUi(QWidget *AccessAnalysisDialog)
    {
        if (AccessAnalysisDialog->objectName().isEmpty())
            AccessAnalysisDialog->setObjectName(QString::fromUtf8("AccessAnalysisDialog"));
        AccessAnalysisDialog->resize(400, 300);

        retranslateUi(AccessAnalysisDialog);

        QMetaObject::connectSlotsByName(AccessAnalysisDialog);
    } // setupUi

    void retranslateUi(QWidget *AccessAnalysisDialog)
    {
        AccessAnalysisDialog->setWindowTitle(QCoreApplication::translate("AccessAnalysisDialog", "AccessAnalysisDialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccessAnalysisDialog: public Ui_AccessAnalysisDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCESSANALYSISDIALOG_H

/********************************************************************************
** Form generated from reading UI file 'ToolWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOOLWIDGET_H
#define UI_TOOLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ToolWidget
{
public:

    void setupUi(QWidget *ToolWidget)
    {
        if (ToolWidget->objectName().isEmpty())
            ToolWidget->setObjectName(QString::fromUtf8("ToolWidget"));
        ToolWidget->resize(400, 300);

        retranslateUi(ToolWidget);

        QMetaObject::connectSlotsByName(ToolWidget);
    } // setupUi

    void retranslateUi(QWidget *ToolWidget)
    {
        ToolWidget->setWindowTitle(QCoreApplication::translate("ToolWidget", "ToolWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ToolWidget: public Ui_ToolWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOOLWIDGET_H

/********************************************************************************
** Form generated from reading UI file 'TextOutWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXTOUTWIDGET_H
#define UI_TEXTOUTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TextOutWidget {
public:

    void setupUi(QWidget *TextOutWidget) {
        if (TextOutWidget->objectName().isEmpty())
            TextOutWidget->setObjectName(QString::fromUtf8("TextOutWidget"));
        TextOutWidget->resize(400, 300);

        retranslateUi(TextOutWidget);

        QMetaObject::connectSlotsByName(TextOutWidget);
    } // setupUi

    void retranslateUi(QWidget *TextOutWidget) {
        TextOutWidget->setWindowTitle(QCoreApplication::translate("TextOutWidget", "TextOutWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TextOutWidget : public Ui_TextOutWidget {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXTOUTWIDGET_H

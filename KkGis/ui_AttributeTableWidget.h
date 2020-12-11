/********************************************************************************
** Form generated from reading UI file 'AttributeTableWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTRIBUTETABLEWIDGET_H
#define UI_ATTRIBUTETABLEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AttributeTableWidget {
public:

    void setupUi(QWidget *AttributeTable) {
        if (AttributeTable->objectName().isEmpty())
            AttributeTable->setObjectName(QString::fromUtf8("AttributeTable"));
        AttributeTable->resize(867, 634);

        retranslateUi(AttributeTable);

        QMetaObject::connectSlotsByName(AttributeTable);
    } // setupUi

    void retranslateUi(QWidget *AttributeTable) {
        AttributeTable->setWindowTitle(QCoreApplication::translate("AttributeTable", "AttributeTable", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AttributeTableWidget : public Ui_AttributeTableWidget {
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTRIBUTETABLEWIDGET_H

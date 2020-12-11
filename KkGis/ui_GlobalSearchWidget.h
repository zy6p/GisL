/********************************************************************************
** Form generated from reading UI file 'GlobalSearchWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLOBALSEARCHWIDGET_H
#define UI_GLOBALSEARCHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GlobalSearchWidget
{
public:
    QLabel *GlobalLabel;
    QLineEdit *searchInputTextEdit;
    QPushButton *searchButton;
    QListWidget *resultList;

    void setupUi(QWidget *GlobalSearchWidget)
    {
        if (GlobalSearchWidget->objectName().isEmpty())
            GlobalSearchWidget->setObjectName(QString::fromUtf8("GlobalSearchWidget"));
        GlobalSearchWidget->resize(694, 523);
        GlobalLabel = new QLabel(GlobalSearchWidget);
        GlobalLabel->setObjectName(QString::fromUtf8("GlobalLabel"));
        GlobalLabel->setGeometry(QRect(50, 50, 72, 15));
        searchInputTextEdit = new QLineEdit(GlobalSearchWidget);
        searchInputTextEdit->setObjectName(QString::fromUtf8("searchInputTextEdit"));
        searchInputTextEdit->setGeometry(QRect(130, 40, 351, 31));
        searchButton = new QPushButton(GlobalSearchWidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(520, 40, 91, 31));
        resultList = new QListWidget(GlobalSearchWidget);
        resultList->setObjectName(QString::fromUtf8("resultList"));
        resultList->setGeometry(QRect(60, 110, 561, 371));

        retranslateUi(GlobalSearchWidget);

        QMetaObject::connectSlotsByName(GlobalSearchWidget);
    } // setupUi

    void retranslateUi(QWidget *GlobalSearchWidget)
    {
        GlobalSearchWidget->setWindowTitle(QCoreApplication::translate("GlobalSearchWidget", "GlobalSearchWidget", nullptr));
        GlobalLabel->setText(QCoreApplication::translate("GlobalSearchWidget", "Input", nullptr));
        searchButton->setText(QCoreApplication::translate("GlobalSearchWidget", "search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GlobalSearchWidget: public Ui_GlobalSearchWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLOBALSEARCHWIDGET_H

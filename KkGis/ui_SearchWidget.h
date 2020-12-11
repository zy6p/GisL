/********************************************************************************
** Form generated from reading UI file 'SearchWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHWIDGET_H
#define UI_SEARCHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchWidget
{
public:
    QLabel *layerNameLabel;
    QListWidget *searchResultList;
    QPushButton *searchButton;
    QLabel *attributeValueLabel;
    QComboBox *attriNameComboBox;
    QLineEdit *attributeValueInputLine;
    QLabel *resultNumLabel;

    void setupUi(QWidget *SearchWidget)
    {
        if (SearchWidget->objectName().isEmpty())
            SearchWidget->setObjectName(QString::fromUtf8("SearchWidget"));
        SearchWidget->resize(669, 473);
        layerNameLabel = new QLabel(SearchWidget);
        layerNameLabel->setObjectName(QString::fromUtf8("layerNameLabel"));
        layerNameLabel->setGeometry(QRect(20, 40, 91, 20));
        searchResultList = new QListWidget(SearchWidget);
        searchResultList->setObjectName(QString::fromUtf8("searchResultList"));
        searchResultList->setGeometry(QRect(50, 120, 571, 311));
        searchButton = new QPushButton(SearchWidget);
        searchButton->setObjectName(QString::fromUtf8("searchButton"));
        searchButton->setGeometry(QRect(510, 80, 93, 28));
        attributeValueLabel = new QLabel(SearchWidget);
        attributeValueLabel->setObjectName(QString::fromUtf8("attributeValueLabel"));
        attributeValueLabel->setGeometry(QRect(20, 80, 141, 16));
        attriNameComboBox = new QComboBox(SearchWidget);
        attriNameComboBox->setObjectName(QString::fromUtf8("attriNameComboBox"));
        attriNameComboBox->setGeometry(QRect(180, 40, 291, 21));
        attributeValueInputLine = new QLineEdit(SearchWidget);
        attributeValueInputLine->setObjectName(QString::fromUtf8("attributeValueInputLine"));
        attributeValueInputLine->setGeometry(QRect(180, 80, 291, 21));
        resultNumLabel = new QLabel(SearchWidget);
        resultNumLabel->setObjectName(QString::fromUtf8("resultNumLabel"));
        resultNumLabel->setGeometry(QRect(50, 440, 271, 21));

        retranslateUi(SearchWidget);

        QMetaObject::connectSlotsByName(SearchWidget);
    } // setupUi

    void retranslateUi(QWidget *SearchWidget)
    {
        SearchWidget->setWindowTitle(QCoreApplication::translate("SearchWidget", "SearchWidget", nullptr));
        layerNameLabel->setText(QCoreApplication::translate("SearchWidget", "Layer Name", nullptr));
        searchButton->setText(QCoreApplication::translate("SearchWidget", "search", nullptr));
        attributeValueLabel->setText(QCoreApplication::translate("SearchWidget", "Attribute Value", nullptr));
        resultNumLabel->setText(QCoreApplication::translate("SearchWidget", "\345\205\261\346\237\245\350\257\242\345\207\272 0 \346\235\241\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SearchWidget: public Ui_SearchWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHWIDGET_H

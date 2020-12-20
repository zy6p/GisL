/********************************************************************************
** Form generated from reading UI file 'LinewidthDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEWIDTHDIALOG_H
#define UI_LINEWIDTHDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LinewidthDialog
{
public:
    QPushButton *okButton;
    QPushButton *cancelButton;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *widthLabel;
    QLabel *rangeLabel;

    void setupUi(QDialog *LinewidthDialog)
    {
        if (LinewidthDialog->objectName().isEmpty())
            LinewidthDialog->setObjectName(QString::fromUtf8("LinewidthDialog"));
        LinewidthDialog->resize(409, 128);
        okButton = new QPushButton(LinewidthDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(300, 30, 93, 28));
        okButton->setStyleSheet(QString::fromUtf8("QPushButton{//\345\270\270\350\247\204\345\261\236\346\200\247\350\256\276\347\275\256\n"
"\n"
"       font-size: 12px;\n"
"       background-repeat:no-repeat;//\345\233\276\347\211\207\350\276\203\345\260\217\346\227\266\357\274\214\344\270\215\346\230\276\347\244\272\344\270\252\343\200\202\n"
"       border-style: flat;//\346\211\201\345\271\263\n"
"\n"
"       border-left:1px solid #CCCCCC;//\350\276\271\346\241\206\347\272\277\346\235\241\347\262\227\347\273\206\343\200\201\350\231\232\345\256\236\343\200\201\351\242\234\350\211\262\n"
"}\n"
"QPushButton:hover{//\346\214\211\351\222\256\351\253\230\344\272\256\345\261\236\346\200\247\350\256\276\347\275\256\n"
"\n"
"       background-repeat:no-repeat;\n"
"\n"
"       border-style: flat;\n"
"\n"
"       border-left:1px solid #CCCCCC;\n"
"\n"
"}\n"
"\n"
" \n"
"\n"
"QPushButton:pressed{//\346\214\211\351\222\256\346\214\211\344\270\213\346\227\266\347\232\204\345\261\236\346\200\247\350\256\276\347\275\256\n"
"\n"
"       border-style: flat;\n"
"\n"
"       "
                        "border-left:1px solid #CCCCCC;\n"
"\n"
"}"));
        cancelButton = new QPushButton(LinewidthDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(300, 70, 93, 28));
        cancelButton->setStyleSheet(QString::fromUtf8("QPushButton{//\345\270\270\350\247\204\345\261\236\346\200\247\350\256\276\347\275\256\n"
"\n"
"       font-size: 12px;\n"
"       background-repeat:no-repeat;//\345\233\276\347\211\207\350\276\203\345\260\217\346\227\266\357\274\214\344\270\215\346\230\276\347\244\272\344\270\252\343\200\202\n"
"       border-style: flat;//\346\211\201\345\271\263\n"
"\n"
"       border-left:1px solid #CCCCCC;//\350\276\271\346\241\206\347\272\277\346\235\241\347\262\227\347\273\206\343\200\201\350\231\232\345\256\236\343\200\201\351\242\234\350\211\262\n"
"}\n"
"QPushButton:hover{//\346\214\211\351\222\256\351\253\230\344\272\256\345\261\236\346\200\247\350\256\276\347\275\256\n"
"\n"
"       background-repeat:no-repeat;\n"
"\n"
"       border-style: flat;\n"
"\n"
"       border-left:1px solid #CCCCCC;\n"
"\n"
"}\n"
"\n"
" \n"
"\n"
"QPushButton:pressed{//\346\214\211\351\222\256\346\214\211\344\270\213\346\227\266\347\232\204\345\261\236\346\200\247\350\256\276\347\275\256\n"
"\n"
"       border-style: flat;\n"
"\n"
"       "
                        "border-left:1px solid #CCCCCC;\n"
"\n"
"}"));
        doubleSpinBox = new QDoubleSpinBox(LinewidthDialog);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(20, 40, 261, 31));
        doubleSpinBox->setStyleSheet(QString::fromUtf8("font: 25 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        widthLabel = new QLabel(LinewidthDialog);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));
        widthLabel->setGeometry(QRect(20, 10, 151, 21));
        widthLabel->setContextMenuPolicy(Qt::NoContextMenu);
        widthLabel->setStyleSheet(QString::fromUtf8("font: 12pt \"\351\273\221\344\275\223\";"));
        rangeLabel = new QLabel(LinewidthDialog);
        rangeLabel->setObjectName(QString::fromUtf8("rangeLabel"));
        rangeLabel->setGeometry(QRect(20, 80, 151, 20));

        retranslateUi(LinewidthDialog);
        QObject::connect(okButton, SIGNAL(clicked()), LinewidthDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), LinewidthDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LinewidthDialog);
    } // setupUi

    void retranslateUi(QDialog *LinewidthDialog)
    {
        LinewidthDialog->setWindowTitle(QCoreApplication::translate("LinewidthDialog", "LinewidthDialog", nullptr));
        okButton->setText(QCoreApplication::translate("LinewidthDialog", "ok", nullptr));
        cancelButton->setText(QCoreApplication::translate("LinewidthDialog", "cancel", nullptr));
        widthLabel->setText(QCoreApplication::translate("LinewidthDialog", "LineWidth", nullptr));
        rangeLabel->setText(QCoreApplication::translate("LinewidthDialog", "range 0.01-99.99", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LinewidthDialog: public Ui_LinewidthDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEWIDTHDIALOG_H

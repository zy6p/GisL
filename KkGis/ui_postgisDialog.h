/********************************************************************************
** Form generated from reading UI file 'postgisDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSTGISDIALOG_H
#define UI_POSTGISDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_postgisDialog
{
public:
    QPushButton *Ok;
    QPushButton *Cancel;
    QLabel *Username;
    QLabel *Password;
    QLabel *ServerHost;
    QLabel *Database;
    QLabel *Layername;
    QLineEdit *eUsername;
    QLineEdit *ePassword;
    QLineEdit *eServerHost;
    QLineEdit *eServerHost1;
    QLineEdit *eDatabase;
    QComboBox *comeLayername;
    QPushButton *pushButton;

    void setupUi(QDialog *postgisDialog)
    {
        if (postgisDialog->objectName().isEmpty())
            postgisDialog->setObjectName(QString::fromUtf8("postgisDialog"));
        postgisDialog->resize(418, 261);
        Ok = new QPushButton(postgisDialog);
        Ok->setObjectName(QString::fromUtf8("Ok"));
        Ok->setGeometry(QRect(150, 200, 111, 31));
        Cancel = new QPushButton(postgisDialog);
        Cancel->setObjectName(QString::fromUtf8("Cancel"));
        Cancel->setGeometry(QRect(270, 200, 101, 31));
        Username = new QLabel(postgisDialog);
        Username->setObjectName(QString::fromUtf8("Username"));
        Username->setGeometry(QRect(50, 40, 101, 16));
        QFont font;
        font.setPointSize(9);
        Username->setFont(font);
        Password = new QLabel(postgisDialog);
        Password->setObjectName(QString::fromUtf8("Password"));
        Password->setGeometry(QRect(50, 70, 91, 16));
        Password->setFont(font);
        ServerHost = new QLabel(postgisDialog);
        ServerHost->setObjectName(QString::fromUtf8("ServerHost"));
        ServerHost->setGeometry(QRect(40, 100, 121, 16));
        ServerHost->setFont(font);
        Database = new QLabel(postgisDialog);
        Database->setObjectName(QString::fromUtf8("Database"));
        Database->setGeometry(QRect(50, 130, 91, 16));
        Database->setFont(font);
        Layername = new QLabel(postgisDialog);
        Layername->setObjectName(QString::fromUtf8("Layername"));
        Layername->setGeometry(QRect(50, 160, 91, 20));
        Layername->setFont(font);
        eUsername = new QLineEdit(postgisDialog);
        eUsername->setObjectName(QString::fromUtf8("eUsername"));
        eUsername->setGeometry(QRect(150, 40, 211, 21));
        eUsername->setFont(font);
        ePassword = new QLineEdit(postgisDialog);
        ePassword->setObjectName(QString::fromUtf8("ePassword"));
        ePassword->setGeometry(QRect(150, 70, 211, 21));
        ePassword->setFont(font);
        eServerHost = new QLineEdit(postgisDialog);
        eServerHost->setObjectName(QString::fromUtf8("eServerHost"));
        eServerHost->setGeometry(QRect(150, 100, 131, 21));
        eServerHost->setFont(font);
        eServerHost1 = new QLineEdit(postgisDialog);
        eServerHost1->setObjectName(QString::fromUtf8("eServerHost1"));
        eServerHost1->setGeometry(QRect(290, 100, 71, 21));
        eServerHost1->setFont(font);
        eDatabase = new QLineEdit(postgisDialog);
        eDatabase->setObjectName(QString::fromUtf8("eDatabase"));
        eDatabase->setGeometry(QRect(150, 130, 211, 21));
        eDatabase->setFont(font);
        comeLayername = new QComboBox(postgisDialog);
        comeLayername->setObjectName(QString::fromUtf8("comeLayername"));
        comeLayername->setGeometry(QRect(150, 160, 211, 21));
        pushButton = new QPushButton(postgisDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 200, 111, 31));

        retranslateUi(postgisDialog);

        QMetaObject::connectSlotsByName(postgisDialog);
    } // setupUi

    void retranslateUi(QDialog *postgisDialog)
    {
        postgisDialog->setWindowTitle(QCoreApplication::translate("postgisDialog", "Dialog", nullptr));
        Ok->setText(QCoreApplication::translate("postgisDialog", "Draw", nullptr));
        Cancel->setText(QCoreApplication::translate("postgisDialog", "Cancel", nullptr));
        Username->setText(QCoreApplication::translate("postgisDialog", "Username:", nullptr));
        Password->setText(QCoreApplication::translate("postgisDialog", "Password:", nullptr));
        ServerHost->setText(QCoreApplication::translate("postgisDialog", "Server Host:", nullptr));
        Database->setText(QCoreApplication::translate("postgisDialog", "Database:", nullptr));
        Layername->setText(QCoreApplication::translate("postgisDialog", "Layername:", nullptr));
        pushButton->setText(QCoreApplication::translate("postgisDialog", "Get Layers", nullptr));
    } // retranslateUi

};

namespace Ui {
    class postgisDialog: public Ui_postgisDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSTGISDIALOG_H

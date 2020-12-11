#include "MyWizard.h"


MyWizard::MyWizard(QWidget *parent)
        : QWidget(parent) {
    ui.setupUi(this);
    ui.lineEdit->setText("127.0.0.1");
    ui.lineEdit_3->setText("postgres");
    ui.lineEdit_4->setText("husen");
    ui.lineEdit_2->setText("5432");

    ui.lineEdit->setPlaceholderText("host");
    ui.lineEdit_3->setPlaceholderText("user");
    ui.lineEdit_4->setPlaceholderText("password");
    ui.lineEdit_2->setPlaceholderText("port");
    ui.lineEdit_5->setPlaceholderText("dbname");
    ui.lineEdit_6->setPlaceholderText("table");
}


MyWizard::~MyWizard(void) {
}

void MyWizard::continueClick() {
    this->dbname = ui.lineEdit_5->displayText();
    this->host = ui.lineEdit->displayText();
    this->user = ui.lineEdit_3->displayText();
    this->password = ui.lineEdit_4->displayText();
    this->table = ui.lineEdit_6->displayText();
    this->port = ui.lineEdit_2->displayText();
    emit sendPostgresqlData(dbname, host, user, password, table, port);
    this->close();
}

void MyWizard::cancelClick() {
    this->close();
}
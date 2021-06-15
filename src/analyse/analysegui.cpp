//
// Created by km on 6/14/21.
//

#include "analysegui.h"
#include "ui_analyseform.h"

AnalyseGui::AnalyseGui(QWidget* parent) : ui(new Ui::AnalyseForm) {
  ui->setupUi(this);
  setEnabled(true);
}
void AnalyseGui::setAlgName(std::string_view sv) noexcept {
  this->setWindowTitle(QString::fromStdString(sv.data()));
}
void AnalyseGui::addItemToUi(const QString& s, QWidget* w) noexcept {
  this->ui->formLayout->addRow(s, w);
}

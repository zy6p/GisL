//
// Created by km on 6/14/21.
//

#include "analysisgui.h"
#include "ui_analyseform.h"

AnalysisGui::AnalysisGui(QWidget* parent) : ui(new Ui::AnalyseForm) {
  ui->setupUi(this);
  setEnabled(true);
}
void AnalysisGui::setAlgName(std::string_view sv) noexcept {
  this->setWindowTitle(QString::fromStdString(sv.data()));
}
void AnalysisGui::addItemToUi(const QString& s, QWidget* w) noexcept {
  this->ui->formLayout->addRow(s, w);
}

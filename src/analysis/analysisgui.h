//
// Created by km on 6/14/21.
//

#ifndef GISL_ANALYSEGUI_H
#define GISL_ANALYSEGUI_H

#include <QWidget>

#include "analysis.h"

namespace Ui {
class AnalyseForm;
}

class AnalysisGui : public QWidget {
  Q_OBJECT
public:
  explicit AnalysisGui(QWidget* parent);
  void setAlgName(std::string_view sv) noexcept;
  void addItemToUi(const QString& s, QWidget* w) noexcept;

protected:
  Ui::AnalyseForm* ui;

  friend class gisl::AnalysisAlg;
};

#endif // GISL_ANALYSEGUI_H
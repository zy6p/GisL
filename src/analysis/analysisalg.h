//
// Created by km on 6/14/21.
//

#ifndef GISL_ANALYSISALG_H
#define GISL_ANALYSISALG_H

#include <QComboBox>

#include "gui/command/command.h"

class AnalysisGui;
namespace gisl {
class AnalysisAlg : public Command {
public:
  enum class AnalyseErr {
    NoErr = 0,
    DataSourceErr = 1,
    AlgorithmErr = 2,
  };
  enum class InputArgType {
    Layer = 0,
    Provider = 1,
    FileName = 2,
    IntValue = 3,
    DoubleValue = 4,
  };

  void execute(QWidget* parent) override;
  virtual void initGui();

  void getInputComboBox(std::string_view sv, InputArgType t) noexcept;

  ~AnalysisAlg() override;

public slots:
  virtual void execAlg();

protected:
  AnalysisAlg() = default;
  AnalysisGui* gui;

  std::string _algName = "analyse";
};
} // namespace gisl
#endif // GISL_ANALYSISALG_H

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

  /**
   * be called when construct, and do nothing
   * @param parent
   */
  void execute(QWidget* parent) override;

  ~AnalysisAlg() override;
  void getInputComboBox(std::string_view sv, InputArgType t) noexcept;

public slots:
  /**
   * to init input and output args in gui
   */
  virtual void initGui();

  /**
   * be called when gui's exec push button clicked, pass some args to the alg
   */
  virtual void execAlg() = 0;

protected:
  AnalysisAlg() = default;
  AnalysisGui* gui = nullptr;

  std::string _algName = "analyse";
};
} // namespace gisl
#endif // GISL_ANALYSISALG_H

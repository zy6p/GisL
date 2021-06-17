//
// Created by km on 6/14/21.
//

#ifndef GISL_GEOREFERENCE_H
#define GISL_GEOREFERENCE_H

#include <QComboBox>

#include "analysisalg.h"

namespace gisl {
class GeoReference final : public AnalysisAlg {
public:
  void execute(QWidget* parent) override;
  ~GeoReference() override;
  void initGui() override;
  void reverse() override;
  const std::string& output() override;
  void execAlg() override;

private:
  QComboBox* pProviderBox1 = nullptr;
  QComboBox* pProviderBox2 = nullptr;
};
} // namespace gisl
#endif // GISL_GEOREFERENCE_H

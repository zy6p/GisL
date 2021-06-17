//
// Created by km on 6/14/21.
//

#ifndef GISL_GEOREFERENCE_H
#define GISL_GEOREFERENCE_H

#include "analysisalg.h"

namespace gisl {
class GeoReference final : public AnalysisAlg {
public:
  void execute(QWidget* parent) override;
  ~GeoReference() override;
  void execAlg() override;
  void reverse() override;
  const std::string& output() override;
  void initGui() override;
};
} // namespace gisl
#endif // GISL_GEOREFERENCE_H

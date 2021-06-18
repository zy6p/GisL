//
// Created by km on 6/16/21.
//

#ifndef GISL_ANALYSIS_H
#define GISL_ANALYSIS_H

#include <memory>

#include "analysisalg.h"

namespace gisl {
class Analysis {
public:
  enum class AnalysisAlgEnum {
    Test = 0,
    GeoReference = 1,
    RsIndex = 2,
  };
  using AnalysisAlgNameMap = std::map<uint8_t, std::string>;
  /**
   * Returns a pointer to the singleton instance.
   */
  static std::shared_ptr<Analysis> instance();
  [[nodiscard]] std::shared_ptr<AnalysisAlgNameMap> registerAll() noexcept;
  [[nodiscard]] AnalysisAlg*
  buildAlg(AnalysisAlgEnum m, QWidget* parent) const noexcept;

private:
  Analysis();
  static std::shared_ptr<Analysis> _analysis;
  std::shared_ptr<gisl::Analysis::AnalysisAlgNameMap> pAlgNameMap =
      std::make_shared<gisl::Analysis::AnalysisAlgNameMap>(
          gisl::Analysis::AnalysisAlgNameMap{
              {0, "Test"},
              {1, "GeoReference"},
              {2, "RsIndex"}});
};
} // namespace gisl

#endif // GISL_ANALYSIS_H

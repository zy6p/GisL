//
// Created by km on 6/16/21.
//

#include "analysis.h"
#include "analysisalg.h"
#include "georeference.h"
std::shared_ptr<gisl::Analysis> gisl::Analysis::_analysis = nullptr;
std::shared_ptr<gisl::Analysis> gisl::Analysis::instance() {
  if (nullptr == gisl::Analysis::_analysis) {
    Analysis::_analysis = std::make_unique<Analysis>(Analysis{});
  }
  return Analysis::_analysis;
}
std::shared_ptr<gisl::Analysis::AnalysisAlgNameMap>
gisl::Analysis::registerAll() noexcept {
  return pAlgNameMap;
}
gisl::AnalysisAlg*
gisl::Analysis::buildAlg(AnalysisAlgEnum m, QWidget* parent) const noexcept {
  switch (m) {
  case AnalysisAlgEnum::Test:
    return nullptr;
  case AnalysisAlgEnum::GeoReference: {
    auto* p = new GeoReference();
    p->execute(parent);
    return p;
  }
  case AnalysisAlgEnum::Classify:
    return nullptr;
  default:
    return nullptr;
  }
}
gisl::Analysis::Analysis() = default;

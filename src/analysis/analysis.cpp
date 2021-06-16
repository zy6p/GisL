//
// Created by km on 6/16/21.
//

#include "analysis.h"
std::shared_ptr<gisl::Analysis> gisl::Analysis::_analysis = nullptr;
std::shared_ptr<gisl::Analysis> gisl::Analysis::instance() {
  if (nullptr == gisl::Analysis::_analysis) {
    Analysis::_analysis = std::make_unique<Analysis>(Analysis{});
  }
  return Analysis::_analysis;
}
gisl::Analysis::Analysis() = default;

//
// Created by km on 6/16/21.
//

#ifndef GISL_ANALYSIS_H
#define GISL_ANALYSIS_H

#include <memory>

namespace gisl {
class Analysis {
public:
  /**
   * Returns a pointer to the singleton instance.
   */
  static std::shared_ptr<Analysis> instance();

private:
  Analysis();
  static std::shared_ptr<Analysis> _analysis;
};
} // namespace gisl

#endif // GISL_ANALYSIS_H

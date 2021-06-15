/*!
 * @author tau
 * @date 12/30/20
 */

#include "command.h"

std::string_view gisl::Command::errorMessage() const { return _errorMessage; }

gisl::Command::~Command() = default;
constexpr bool gisl::Command::hasError() const noexcept {
  return _mErr != CommandErr::NoErr;
}

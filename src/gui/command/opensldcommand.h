/*!
 * @author tau
 * @date 12/30/20
 */

#ifndef GISL_OPENSLDCOMMAND_H
#define GISL_OPENSLDCOMMAND_H

#include "command.h"

#include <string>

#include "sld.h"

namespace gisl {
class OpenSldCommand : public Command {
public:
  void execute(QWidget* parent) override;

  const std::string& output() override;

  void reverse() override;

  ~OpenSldCommand() override;

private:
  std::string sldName;

  Sld* pSld;
};
} // namespace gisl

#endif // GISL_OPENSLDCOMMAND_H

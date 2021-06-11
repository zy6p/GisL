//
// Created by omega on 6/11/21.
//

#ifndef GISL_OPENRASTERCOMMAND_H
#define GISL_OPENRASTERCOMMAND_H

#include "command.h"
namespace gisl {
class OpenRasterCommand final : public Command {
public:
  void execute(QWidget *parent) override;
  const std::string &output() override;
  void reverse() override;
  ~OpenRasterCommand() override;
};
} // namespace gisl
#endif // GISL_OPENRASTERCOMMAND_H

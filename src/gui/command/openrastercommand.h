//
// Created by omega on 6/11/21.
//

#ifndef GISL_OPENRASTERCOMMAND_H
#define GISL_OPENRASTERCOMMAND_H

#include <string>

#include "command.h"

#include "core/provider/rasterprovider.h"
#include "ui_mainwindow.h"

namespace gisl {
class OpenRasterCommand final : public Command {
public:
  void execute(QWidget* parent) override;
  const std::string& output() override;
  void reverse() override;
  ~OpenRasterCommand() override;
  void getUi(Ui_MainWindow& p);
  void testExecute(QWidget* parent);

protected:
  std::string fileName;

  RasterProvider* pProvider;

  Ui_MainWindow* ui;
};
} // namespace gisl
#endif // GISL_OPENRASTERCOMMAND_H

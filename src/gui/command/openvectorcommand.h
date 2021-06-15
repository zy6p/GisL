/*!
 * @author tau
 * @date 12/30/20
 */

#ifndef GISL_OPENVECTORCOMMAND_H
#define GISL_OPENVECTORCOMMAND_H

#include "command.h"

#include <string>

#include "core/provider/vectorprovider.h"
#include "ui_mainwindow.h"

namespace gisl {
class OpenVectorCommand : public Command {
public:
    void execute(QWidget* parent) override;

    const std::string& output() override;

    void reverse() override;

    void getUi(Ui_MainWindow& p);

    ~OpenVectorCommand() override;

protected:
    std::string vectorName;

    DataProvider* pProvider;

    Ui_MainWindow* ui;
};
} // namespace gisl

#endif // GISL_OPENVECTORCOMMAND_H

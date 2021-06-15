//
// Created by km on 6/14/21.
//

#ifndef GISL_ANALYSE_H
#define GISL_ANALYSE_H

#include <QComboBox>

#include "src/gui/command/command.h"

class AnalyseGui;
namespace gisl {
class Analyse : public Command {
public:
    enum class AnalyseErr {
        NoErr = 0,
        DataSourceErr = 1,
        AlgorithmErr = 2,
    };
    enum class InputArgType {
        Layer = 0,
        Provider = 1,
        FileName = 2,
        IntValue = 3,
        DoubleValue = 4,
    };

    void execute(QWidget* parent) override;
    virtual void execAlg() = 0;

    void getInputComboBox(std::string_view sv, InputArgType t) noexcept;

    ~Analyse() override;

protected:
    Analyse() = default;
    AnalyseGui* gui;

    std::string _algName = "analyse";
};
} // namespace gisl
#endif // GISL_ANALYSE_H

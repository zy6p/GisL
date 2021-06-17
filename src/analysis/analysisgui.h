//
// Created by km on 6/14/21.
//

#ifndef GISL_ANALYSEGUI_H
#define GISL_ANALYSEGUI_H

#include <QWidget>

#include "analysisalg.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AnalysisForm;
}
QT_END_NAMESPACE

class AnalysisGui : public QWidget {
    Q_OBJECT
public:
    enum class InputArgType {
        Layer = 0,
        Provider = 1,
        FileName = 2,
        IntValue = 3,
        DoubleValue = 4,
    };
    explicit AnalysisGui(QWidget* parent);
    void setAlgName(std::string_view sv) noexcept;
    void addItemToUi(const QString& s, QWidget* w) noexcept;
    void bindAlg(const gisl::AnalysisAlg& alg) const noexcept;
    template <typename Input>
    void addItemToUi(const QString& s, InputArgType t, Input& i) {
        switch (t) {
        case InputArgType::Layer:
            i = (Input)103;
            break;
        case InputArgType::Provider:
            i = (Input)1;
            break;
        case InputArgType::FileName:
            i = (Input) "s";
            break;
        case InputArgType::IntValue:
            i = (Input)1;
            break;
        case InputArgType::DoubleValue:
            i = (Input)3.0;
            break;
        default:
            break;
        }
    }

protected:
    Ui::AnalysisForm* ui;

protected slots:
    void buttonCancleTriggered();

    friend class gisl::AnalysisAlg;
};

#endif // GISL_ANALYSEGUI_H

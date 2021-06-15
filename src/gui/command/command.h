/*!
 * @author tau
 * @date 12/30/20
 */

#ifndef GISL_COMMAND_H
#define GISL_COMMAND_H

#include <QWidget>
#include <string>

namespace gisl {
class Command {
public:
    enum class CommandErr {
        NoErr = 0,
        InputErr = 1,
        OutputErr = 2,
    };

    virtual void execute(QWidget* parent) = 0;
    virtual void reverse() = 0;

    virtual const std::string& output() = 0;

    virtual ~Command();

    [[nodiscard]] constexpr bool hasError() const noexcept;
    [[nodiscard]] std::string_view errorMessage() const;

protected:
    Command() = default;

    CommandErr _mErr = CommandErr::NoErr;
    std::string _errorMessage;
};
} // namespace gisl

#endif // GISL_COMMAND_H

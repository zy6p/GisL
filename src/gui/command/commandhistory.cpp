/*!
 * @author tau
 * @date 12/30/20
 */

#include <QString>

#include "commandhistory.h"

gisl::CommandHistory* gisl::CommandHistory::_commandHistory = nullptr;

void gisl::CommandHistory::push(Command* c, const std::string& s) {

    if (nullptr != c) {
        auto* p = new CommandLink;
        p->pCommand = c;
        p->name = s;
        p->previous = currentCommand;
        currentCommand->next = p;

        currentCommand = p;
        count++;
    }
}

void gisl::CommandHistory::push(gisl::Command* c, const QString& s) {
    push(c, s.toStdString());
}

gisl::CommandHistory* gisl::CommandHistory::getCommandHistory() {
    if (nullptr == _commandHistory) {
        _commandHistory = new CommandHistory;
    }
    return _commandHistory;
}

gisl::CommandHistory::CommandHistory() {
    firstCommand = new CommandLink;
    firstCommand->pCommand = nullptr;
    firstCommand->previous = nullptr;
    firstCommand->next = nullptr;

    currentCommand = firstCommand;
}

bool gisl::CommandHistory::isEmpty() {
    return (firstCommand == nullptr);
}

void gisl::CommandHistory::rollBack(int step) {
    if (nullptr == currentCommand) {
        return;
    }
    for (int i = 0; i < step; ++i) {
        currentCommand->pCommand->reverse();
        currentCommand = currentCommand->previous;
        delete currentCommand->next->pCommand;
        currentCommand->next->pCommand = nullptr;
        delete currentCommand->next;
        currentCommand->next = nullptr;
        count--;
    }
}

void gisl::CommandHistory::destroy() {
    rollBack(count);
}

/*!
 * @author tau 
 * @date 12/30/20
*/

#include <QString>

#include "commandhistory.h"

GisL::CommandHistory *GisL::CommandHistory::_commandHistory = nullptr;

void GisL::CommandHistory::push( Command *c, const std::string &s ) {

    if ( nullptr != c ) {
        auto *p = new CommandLink;
        p->pCommand = c;
        p->name = s;
        p->previous = currentCommand;
        currentCommand->next = p;

        currentCommand = p;
        count++;
    }
}

void GisL::CommandHistory::push( GisL::Command *c, const QString &s ) {
    push( c, s.toStdString());
}

GisL::CommandHistory *GisL::CommandHistory::getCommandHistory( ) {
    if ( nullptr == _commandHistory ) {
        _commandHistory = new CommandHistory;
    }
    return _commandHistory;
}

GisL::CommandHistory::CommandHistory( ) {
    firstCommand = new CommandLink;
    firstCommand->pCommand = nullptr;
    firstCommand->previous = nullptr;
    firstCommand->next = nullptr;

    currentCommand = firstCommand;
}

bool GisL::CommandHistory::isEmpty( ) {
    return ( firstCommand == nullptr );
}

void GisL::CommandHistory::rollBack( int step ) {
    if ( nullptr == currentCommand ) {
        return;
    }
    for ( int i = 0; i < step; ++i ) {
        currentCommand->pCommand->reverse();
        currentCommand = currentCommand->previous;
        delete currentCommand->next->pCommand;
        currentCommand->next->pCommand = nullptr;
        delete currentCommand->next;
        currentCommand->next = nullptr;
        count--;
    }
}

void GisL::CommandHistory::destroy( ) {
    rollBack( count );
}


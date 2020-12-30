/*!
 * @author tau 
 * @date 12/30/20
*/

#include "commandhistory.h"

GisL::CommandHistory *GisL::CommandHistory::_commandHistory = nullptr;

std::vector<GisL::Command *> GisL::CommandHistory::mCommandVector;

void GisL::CommandHistory::append( const GisL::Command &c ) {

}

GisL::CommandHistory *GisL::CommandHistory::getCommandHistory( ) {
    if ( nullptr == _commandHistory ) {
        _commandHistory = new CommandHistory;
    }
    return nullptr;
}

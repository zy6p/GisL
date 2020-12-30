/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_COMMANDHISTORY_H
#define GISL_COMMANDHISTORY_H

#include <vector>

#include "command.h"

namespace GisL {
    class CommandHistory {
    public:
        static void append( const Command &c );

        static CommandHistory *getCommandHistory( );

    protected:
        CommandHistory( ) = default;

        static std::vector<Command *> mCommandVector;

    private:
        static CommandHistory *_commandHistory;

    };
}

#endif //GISL_COMMANDHISTORY_H

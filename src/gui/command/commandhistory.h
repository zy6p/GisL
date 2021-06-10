/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_COMMANDHISTORY_H
#define GISL_COMMANDHISTORY_H

#include <vector>

#include "command.h"

namespace gisl {

    /*!
     * @brief command history, easy to undo, realization by firstCommand
     */
    class CommandHistory {
        struct CommandLink {
            Command *pCommand;
            std::string name;
            CommandLink *next;
            CommandLink *previous;
        };

    public:
        bool isEmpty( );

        void push( Command *c, const std::string &s );

        void push( Command *c, const QString &s );

        void rollBack( int step );

        static CommandHistory *getCommandHistory( );

        void destroy( );


    protected:
        CommandHistory( );

        CommandLink *firstCommand;
        CommandLink *currentCommand;

        int count = 0;

    private:
        static CommandHistory *_commandHistory;

    };
}

#endif //GISL_COMMANDHISTORY_H

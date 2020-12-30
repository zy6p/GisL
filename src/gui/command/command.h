/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_COMMAND_H
#define GISL_COMMAND_H

#include <string>

namespace GisL {
    class Command {
    public:
        virtual void execute( ) = 0;

        virtual void reverse( ) = 0;

        ~Command( ) = default;

        const std::string &getMErrorMessage( ) const;

    protected:
        Command( ) = default;

        std::string mErrorMessage;

    };
}

#endif //GISL_COMMAND_H

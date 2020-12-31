/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_COMMAND_H
#define GISL_COMMAND_H

#include <string>
#include <QWidget>

namespace GisL {
    class Command {
    public:
        virtual void execute( QWidget *parent ) = 0;

        virtual const std::string &output( ) = 0;

        virtual void reverse( ) = 0;

        virtual ~Command( );

        const std::string &getMErrorMessage( ) const;

    protected:
        Command( ) = default;

        std::string mErrorMessage;

    };
}

#endif //GISL_COMMAND_H

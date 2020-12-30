/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_OPENVECTORCOMMAND_H
#define GISL_OPENVECTORCOMMAND_H

#include "command.h"

#include "../../core/vector.h"

namespace GisL {
    class OpenVectorCommand : public Command {
    public:
        virtual void execute( );

        virtual void reverse( );

    private:
        Vector *pVector;
    };
}

#endif //GISL_OPENVECTORCOMMAND_H

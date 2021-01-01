/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_OPENVECTORCOMMAND_H
#define GISL_OPENVECTORCOMMAND_H

#include "command.h"

#include <string>

#include "../../core/vectorprovider.h"

namespace GisL {
    class OpenVectorCommand : public Command {
    public:
        void execute( QWidget *parent ) override;

        const std::string &output( ) override;

        void reverse( ) override;

        ~OpenVectorCommand( ) override;

    private:
        std::string vectorName;

        VectorProvider *pVector;
    };
}

#endif //GISL_OPENVECTORCOMMAND_H

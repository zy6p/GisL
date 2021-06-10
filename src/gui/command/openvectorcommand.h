/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_OPENVECTORCOMMAND_H
#define GISL_OPENVECTORCOMMAND_H

#include "command.h"

#include <string>
#include <../../ui/ui_mainwindow.h>

#include "src/core/provider/vectorprovider.h"

namespace gisl {
    class OpenVectorCommand : public Command {
    public:
        void execute( QWidget *parent ) override;

        const std::string &output( ) override;

        void reverse( ) override;

        void getUi( Ui_MainWindow &p );

        ~OpenVectorCommand( ) override;

    protected:
        std::string vectorName;

        VectorProvider *pVector;

        Ui_MainWindow *ui;

    };
}

#endif //GISL_OPENVECTORCOMMAND_H

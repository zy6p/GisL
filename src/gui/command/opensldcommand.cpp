/*!
 * @author tau 
 * @date 12/30/20
*/

#include "opensldcommand.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QObject>

#include "../sld.h"
#include "../../utils/ptroperate.h"

void GisL::OpenSldCommand::execute( QWidget *parent ) {
    QString openFileName = QFileDialog::getOpenFileName(
            parent,
            QObject::tr( "open an sld file." ),
            "../",
            QObject::tr( "Sld(*.sld);;All files(*.*)" ),
            nullptr,
            QFileDialog::DontUseNativeDialog );
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( parent, QObject::tr( "Warning!" ), QObject::tr( "Cancel to open the file!" ));
    } else {
        pSld = new GisL::Sld( openFileName.toStdString());
        //todo sld do what

    }
}

const std::string &GisL::OpenSldCommand::output( ) {
    return sldName;
}

void GisL::OpenSldCommand::reverse( ) {

    PtrOperate::clear( pSld );
}

GisL::OpenSldCommand::~OpenSldCommand( ) {
    PtrOperate::clear( pSld );
}

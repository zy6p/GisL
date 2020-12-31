/*!
 * @author tau 
 * @date 12/30/20
*/

#include "openvectorcommand.h"

#include <QFileDialog>
#include <QObject>
#include <QMessageBox>

#include "../../utils/ptroperate.h"
#include "../../utils/log.h"
#include "../../core/vector.h"

void GisL::OpenVectorCommand::execute( QWidget *parent ) {
    int i = 0;
    QString openFileName = QFileDialog::getOpenFileName(
            parent,
            QObject::tr( "open an vector file." ),
            "../",
            QObject::tr( "GeoJSON(*.geojson);;ESRI Shapefile(*.shp);;All files(*.*)" ),
            nullptr,
            QFileDialog::DontUseNativeDialog );
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( parent, QObject::tr( "Vector Warning!" ), QObject::tr( "Cancel to open the file!" ));
    } else {
        vectorName = openFileName.toStdString();
        pVector = new GisL::Vector( vectorName );
        if ( pVector->hasError()) {
            Log *log = Log::getLog();
            QMessageBox::warning( parent, QObject::tr( "Vector Warning!" ), log->getLast());
            return;
        }
        //todo draw command

    }
}

void GisL::OpenVectorCommand::reverse( ) {
    //todo dont draw vector

    PtrOperate::clear( pVector );
    vectorName = nullptr;
}

const std::string &GisL::OpenVectorCommand::output( ) {
    return vectorName;
}

GisL::OpenVectorCommand::~OpenVectorCommand( ) {
    PtrOperate::clear( pVector );
}

/*!
 * @author tau 
 * @date 12/30/20
*/

#include "openvectorcommand.h"

#include <QFileDialog>
#include <QWidget>
#include <QObject>
#include <QMessageBox>

#include "../../utils/log.h"
#include "../../core/vector.h"

void GisL::OpenVectorCommand::execute( ) {
    auto *pWidget = new QWidget;
    QString openFileName = QFileDialog::getOpenFileName(
            pWidget,
            QObject::tr( "open an vector file." ),
            "../",
            QObject::tr( "GeoJSON(*.geojson);;ESRI Shapefile(*.shp);;All files(*.*)" ));
    if ( openFileName.isEmpty()) {
        QMessageBox::warning( pWidget, QObject::tr( "Vector Warning!" ), QObject::tr( "Cancel to open the file!" ));
    } else {
        pVector = new GisL::Vector( openFileName.toStdString());
        if ( pVector->hasError()) {
            QMessageBox::warning( pWidget, QObject::tr( "Vector Warning!" ), GisL::Log::getLast());
            return;
        }
        //todo draw command

    }
}

void GisL::OpenVectorCommand::reverse( ) {
    int i = 0;
}

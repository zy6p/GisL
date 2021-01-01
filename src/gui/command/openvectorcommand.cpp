/*!
 * @author tau 
 * @date 12/30/20
*/

#include "openvectorcommand.h"

#include <QFileDialog>
#include <QObject>
#include <QMessageBox>

#include "../painter/glpainterfactory.h"
#include "../../core/layertree.h"
#include "../../utils/ptroperate.h"
#include "../../utils/log.h"
#include "../../core/vectorprovider.h"

void GisL::OpenVectorCommand::execute( QWidget *parent ) {

    auto openFileName = QString( "../resource/mydata/hubei_center_202004.shp" );

//    QString openFileName = QFileDialog::getOpenFileName(
//            parent,
//            QObject::tr( "open an vector file." ),
//            "../",
//            QObject::tr( "GeoJSON(*.geojson);;ESRI Shapefile(*.shp);;All files(*.*)" ),
//            nullptr,
//            QFileDialog::DontUseNativeDialog );
//    if ( openFileName.isEmpty()) {
//        QMessageBox::warning( parent, QObject::tr( "VectorProvider Warning!" ), QObject::tr( "Cancel to open the file!" ));
//    } else {
    vectorName = openFileName.toStdString();
    pVector = new GisL::VectorProvider( vectorName );
    if ( pVector->hasError()) {
        Log *log = Log::getLog();
        QMessageBox::warning( parent, QObject::tr( "VectorProvider Warning!" ), log->getLast());
        return;
    }
    LayerTree *layerTree = LayerTree::getLayerTree();
    VectorLayer *layer = layerTree->getLayer( "hubei_center_202004" );

    PainterFactory *gl = new GlPainterFactory;
    gl->getEnvelope( *layer->getEnvelope());
    layer->draw( *gl );

//    }
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

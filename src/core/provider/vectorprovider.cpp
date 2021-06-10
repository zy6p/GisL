//
// Created by omega on 14/12/2020.
//

#include "vectorprovider.h"

#include <string>
#include <ogrsf_frmts.h>
#include <QObject>

#include "src/core/layertree.h"
#include "src/utils/log.h"
#include "src/utils/stringoperate.h"
#include "src/core/vectorlayer.h"
#include "src/utils/ptroperate.h"

namespace gisl {

    int gisl::DataProvider::fidSeed = 0;
    void VectorProvider::loadData( std::string_view theFileName, const std::string &theFileEncoding ) {
        if ( theFileName.empty()) {
            this->mErr = DataProviderErr::ErrDataSource;
            log->append( QObject::tr( "<ERROR>: Empty filename given" ));
            return;
        }

        CPLSetConfigOption( "SHAPE_ENCODING", "" );
        poDS = ( GDALDataset * ) GDALOpenEx( theFileName.data(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr );
        if ( nullptr == poDS ) {
            mErr = DataProviderErr::ErrDataSource;
            log->append( QObject::tr( "<ERROR>: Could not open the geojson file" ));
            return;
        }

        LayerTree *layerTree = LayerTree::getLayerTree();

        VectorLayer::seed( fid );
        layerCount = poDS->GetLayerCount();
        pmVectorLayer = new VectorLayer *[layerCount];
        for ( int i = 0; i < layerCount; ++i ) {
//            OGRLayer *pds = poDS->GetLayer( i );
            pmVectorLayer[i] = new VectorLayer( *poDS->GetLayer( i ));
            layerTree->append( poDS->GetLayer( i )->GetName(), pmVectorLayer[i] );
        }
        GDALClose( poDS );
    }

    VectorProvider::~VectorProvider( ) {
        PtrOperate::clear( pmVectorLayer, layerCount );

    }

}
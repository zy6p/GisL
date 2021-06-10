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

    int VectorProvider::fidInVector = 0;

    VectorProvider::VectorProvider( ) {
        log = Log::getLog();
        fid = ++VectorProvider::fidInVector;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
    }

    VectorProvider::VectorProvider( const std::string &vectorFileName, const std::string &theFileEncoding ) {
        log = Log::getLog();
        fid = ++VectorProvider::fidInVector;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
        loadVector( vectorFileName, theFileEncoding );
    }

    void VectorProvider::loadData( std::string_view theFileName, const std::string &theFileEncoding ) {
        if ( theFileName.empty()) {
            mErr = DataProviderErr::ErrDataSource;
            log->append( QObject::tr( "<ERROR>: Empty filename given" ));
            return;
        } else if ( StringOperate::isEndWith<std::string>( theFileName, ".shp", ".dbf", "." )) {

        } else if ( StringOperate::isEndWith( theFileName, ".geojson" )) {

        } else {
            mErr = ErrDataSource;
            log->append( QObject::tr( "<ERROR>: not .shp or .dbf of .geojson" ));
            return;
        }
        loadDataSource( theFileName, theFileEncoding );
    }

    void VectorProvider::loadDataSource( const std::string &theVectorName, const std::string &theFileEncoding ) {
        CPLSetConfigOption( "SHAPE_ENCODING", "" );
        poDS = ( GDALDataset * ) GDALOpenEx( theVectorName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr );
        if ( nullptr == poDS ) {
            mErr = ErrDataSource;
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

    int VectorProvider::getLayerCount( ) const {
        return layerCount;
    }


    VectorProvider::~VectorProvider( ) {
        PtrOperate::clear( pmVectorLayer, layerCount );

    }

    bool VectorProvider::hasError( ) {
        return mErr;
    }


}
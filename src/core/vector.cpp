//
// Created by omega on 14/12/2020.
//

#include "vector.h"

#include <string>
#include <ogrsf_frmts.h>
#include <QObject>

#include "layertree.h"
#include "../utils/log.h"
#include "../utils/stringoperate.h"
#include "vectorlayer.h"
#include "../utils/ptroperate.h"

namespace GisL {

    int Vector::fidInVector = 0;

    void Vector::registerOGRDriver( ) {
        GDALAllRegister();
    }

    Vector::Vector( ) {
        log = Log::getLog();
        fid = ++Vector::fidInVector;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
    }

    Vector::Vector( const std::string &vectorFileName, const std::string &theFileEncoding ) {
        fid = ++Vector::fidInVector;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
        loadVector( vectorFileName, theFileEncoding );
    }

    void Vector::loadVector( const std::string &theVectorFileName, const std::string &theFileEncoding ) {
        if ( theVectorFileName.empty()) {
            mErr = ErrDataSource;
            log->append( QObject::tr( "<ERROR>: Empty filename given" ));
            return;
        } else if ( StringOperate::isEndWith<std::string>( theVectorFileName, ".shp", ".dbf", "." )) {

        } else if ( StringOperate::isEndWith( theVectorFileName, ".geojson" )) {

        } else {
            mErr = ErrDataSource;
            log->append( QObject::tr( "<ERROR>: not .shp or .dbf of .geojson" ));
            return;
        }
        loadDataSource( theVectorFileName, theFileEncoding );
    }

    void Vector::loadDataSource( const std::string &theVectorName, const std::string &theFileEncoding ) {
        CPLSetConfigOption( "SHAPE_ENCODING", "" );
        poDS = ( GDALDataset * ) GDALOpenEx( theVectorName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr );
        if ( nullptr == poDS ) {
            mErr = ErrDataSource;
            log->append( QObject::tr( "<ERROR>: Could not open the geojson file" ));
            return;
        }
        VectorLayer::seed( fid );
        layerCount = poDS->GetLayerCount();
        pmVectorLayer = new VectorLayer *[layerCount];
        for ( int i = 0; i < layerCount; ++i ) {
//            OGRLayer *pds = poDS->GetLayer( i );
            pmVectorLayer[i] = new VectorLayer( *poDS->GetLayer( i ));
            LayerTree::append( poDS->GetLayer( i )->GetName(), pmVectorLayer[i] );
        }
        GDALClose( poDS );
    }

    int Vector::getLayerCount( ) const {
        return layerCount;
    }


    Vector::~Vector( ) {
        PtrOperate::clear( pmVectorLayer, layerCount );

    }

    bool Vector::hasError( ) {
        return mErr;
    }


}
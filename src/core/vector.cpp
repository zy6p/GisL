//
// Created by omega on 14/12/2020.
//

#include "vector.h"

#include <string>
#include <ogrsf_frmts.h>

#include "../utils/stringoperate.h"
#include "vectorlayer.h"
#include "../utils/ptroperate.h"

namespace GisL {

    int Vector::fidInVector = 0;

    void Vector::registerOGRDriver( ) {
        GDALAllRegister();
    }

    Vector::Vector( ) : GisLObject() {
        fid = ++Vector::fidInVector;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
    }

    Vector::Vector( const std::string &vectorFileName, const std::string &theFileEncoding ) : GisLObject() {
        fid = ++Vector::fidInVector;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
        loadVector( vectorFileName, theFileEncoding );
    }

    void Vector::loadVector( const std::string &theVectorFileName, const std::string &theFileEncoding ) {
        if ( theVectorFileName.empty()) {
            mError = MError::GisLError::ErrDataSource;
            mErrorMessage = "Empty filename given";
            return;
        } else if ( StringOperate::isEndWith<std::string>( theVectorFileName, ".shp", ".dbf", "." )) {

        } else if ( StringOperate::isEndWith( theVectorFileName, ".geojson" )) {

        } else {
            mError = MError::GisLError::ErrDataSource;
            mErrorMessage = "not .shp or .dbf of .geojson";
            return;
        }
        loadDataSource( theVectorFileName, theFileEncoding );
    }

    void Vector::loadDataSource( const std::string &theVectorName, const std::string &theFileEncoding ) {
        CPLSetConfigOption( "SHAPE_ENCODING", "" );
        poDS = ( GDALDataset * ) GDALOpenEx( theVectorName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr );
        if ( nullptr == poDS ) {
            mError = MError::GisLError::ErrDataSource;
            mErrorMessage = "Could not open the geojson file";
            return;
        }
        VectorLayer::seed( fid );
        layerCount = poDS->GetLayerCount();
        pmVectorLayer = new VectorLayer *[layerCount];
        for ( int i = 0; i < layerCount; ++i ) {
//            OGRLayer *pds = poDS->GetLayer( i );
            pmVectorLayer[i] = new VectorLayer( *poDS->GetLayer( i ));
        }
        GDALClose( poDS );
    }

    int Vector::getLayerCount( ) const {
        return layerCount;
    }


    Vector::~Vector( ) {
        PtrOperate::clear( pmVectorLayer, layerCount );

    }


}
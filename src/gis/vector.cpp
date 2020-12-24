//
// Created by omega on 14/12/2020.
//

#include "vector.h"

#include <string>
#include <ogrsf_frmts.h>

#include "../utils/stringoperate.h"
#include "vectorlayer.h"
#include "../utils/merror.h"


namespace GisL {

    int Vector::fidInVector = 0;

    void Vector::registerOGRDriver() {
        GDALAllRegister();
    }

    Vector::Vector() {
        fid = ++Vector::fidInVector;
        mError = MError::GisLError::NoError;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
    }

    Vector::Vector(const std::string &vectorFileName, const std::string &theFileEncoding) {
        fid = ++Vector::fidInVector;
        mError = MError::GisLError::NoError;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
        loadVector(vectorFileName, theFileEncoding);
    }

    void Vector::loadVector(const std::string &theVectorFileName, const std::string &theFileEncoding) {
        if (theVectorFileName.empty()) {
            mError = MError::GisLError::ErrDataSource;
            mErrorMessage = "Empty filename given";
            return;
        } else if (StringOperate::isEndWith(theVectorFileName.c_str(), ".shp") ||
                   StringOperate::isEndWith(theVectorFileName.c_str(), ".dbf")) {

        } else if (StringOperate::isEndWith(theVectorFileName.c_str(), ".geojson")) {

        } else {
            mError = MError::GisLError::ErrDataSource;
            mErrorMessage = "not .shp or .dbf of .geojson";
            return;
        }
        loadDataSource(theVectorFileName, theFileEncoding);
    }

    void Vector::loadDataSource(const std::string &theVectorName, const std::string &theFileEncoding) {
        CPLSetConfigOption("SHAPE_ENCODING", "");
        poDS = (GDALDataset *) GDALOpenEx(theVectorName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
        if (nullptr == poDS) {
            mError = MError::GisLError::ErrDataSource;
            mErrorMessage = "Could not open the geojson file";
            return;
        }
        VectorLayer::seed(fid);
        layerCount = poDS->GetLayerCount();
        pmVectorLayer = new VectorLayer *[layerCount];
        for (int i = 0; i < layerCount; ++i) {
//            OGRLayer *pds = poDS->GetLayer( i );
            pmVectorLayer[i] = new VectorLayer(*poDS->GetLayer(i));
        }
        GDALClose(poDS);
    }

    bool Vector::hasError() {
        return mError == MError::GisLError::NoError;
    }

    std::string Vector::errorMessage() {
        return mErrorMessage;
    }

    int Vector::getLayerCount() const {
        return layerCount;
    }


    Vector::~Vector() {
        if (nullptr == pmVectorLayer) {
            for (int i = layerCount - 1; i >= 0; --i) {
                if (nullptr == pmVectorLayer[i]) {
                    delete pmVectorLayer[i];
                    pmVectorLayer = nullptr;
                }
            }
            delete[] pmVectorLayer;
            pmVectorLayer = nullptr;
        }

//        if (nullptr != poDS) {
//            delete poDS;
//            poDS = nullptr;
//        }

    }


}
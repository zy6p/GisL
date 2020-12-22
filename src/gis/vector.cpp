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

    void Vector::seed() {
        fidInVector = 100;
    }

    void Vector::registerOGRDriver() {
        GDALAllRegister();
    }

    Vector::Vector() {
        fid = ++fidInVector;
        mError = MError::GisLError::NoError;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
    }

    Vector::Vector(const std::string &vectorFileName, const std::string &theFileEncoding) {
        fid = ++fidInVector;
        mError = MError::GisLError::NoError;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
        loadVector(vectorFileName, theFileEncoding);
    }

    void Vector::loadVector(const std::string &theVectorFileName, const std::string &theFileEncoding) {
        if (theVectorFileName.empty()) {
            mError = MError::GisLError::ErrCreateDataSource;
            mErrorMessage = "Empty filename given";
            return;
        } else if (StringOperate::isEndWith(theVectorFileName, ".shp") ||
                   StringOperate::isEndWith(theVectorFileName, ".dbf")) {

        } else if (theVectorFileName.length() >= 8 && StringOperate::isEndWith(theVectorFileName, ".geojson")) {

        } else {
            mError = MError::GisLError::ErrCreateDataSource;
            mErrorMessage = "not .shp or .dbf of .geojson";
            return;
        }
        loadDataSource(theVectorFileName, theFileEncoding);
    }

    void Vector::loadDataSource(const std::string &theVectorName, const std::string &theFileEncoding) {
        CPLSetConfigOption("SHAPE_ENCODING", "");
        poDS = (GDALDataset *) GDALOpenEx(theVectorName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
        if (nullptr == poDS) {
            mError = MError::GisLError::ErrCreateDataSource;
            mErrorMessage = "Could not open the geojson file";
            return;
        }
        VectorLayer::seed(fid);
        layerCount = poDS->GetLayerCount();
        pmVectorLayer = new VectorLayer*[layerCount];
        for (int i = 0; i < layerCount; ++i) {
            pmVectorLayer[i] = new VectorLayer(poDS->GetLayer(i));
        }
        GDALClose(poDS);
    }

    MError::GisLError Vector::hasError() {
        return mError;
    }

    std::string Vector::errorMessage() {
        return mErrorMessage;
    }

    int Vector::getLayerCount() const {
        return layerCount;
    }


    Vector::~Vector() {
        if (nullptr == pmVectorLayer) {
            delete[] pmVectorLayer;
            for (int i = layerCount; i >= 0; ++i) {
                if (nullptr == pmVectorLayer[i]) {
                    delete pmVectorLayer[i];
                }
            }
        }
    }


}
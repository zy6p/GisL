//
// Created by omega on 14/12/2020.
//

#include "vector.h"

#include <string>

#include <ogrsf_frmts.h>

#include "src/utils/stringoperate.h"
#include "src/gis/vectorlayer.h"
#include "src/utils/merror.h"


namespace GisL {

    void Vector::registerOGRDriver() {
        GDALAllRegister();
    }

    Vector::Vector() {
        mError = MError::VectorError::NoError;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
    }

    Vector::Vector(const std::string &vectorFileName, const std::string &theFileEncoding) {
        mError = MError::VectorError::NoError;
        layerCount = 0;
        pmVectorLayer = nullptr;
        poDS = nullptr;
        registerOGRDriver();
        loadVector(vectorFileName, theFileEncoding);
    }

    void Vector::loadVector(const std::string &theVectorFileName, const std::string &theFileEncoding) {
        if (theVectorFileName.empty()) {
            mError = MError::VectorError::ErrCreateDataSource;
            mErrorMessage = "Empty filename given";
            return;
        } else if (StringOperate::isEndWith(theVectorFileName, ".shp") ||
                   StringOperate::isEndWith(theVectorFileName, ".dbf")) {

        } else if (theVectorFileName.length() >= 8 && StringOperate::isEndWith(theVectorFileName, ".geojson")) {

        } else {
            mError = MError::VectorError::ErrCreateDataSource;
            mErrorMessage = "not .shp or .dbf of .geojson";
            return;
        }
        loadDataSource(theVectorFileName, theFileEncoding);
    }

    void Vector::loadDataSource(const std::string &theVectorName, const std::string &theFileEncoding) {
        CPLSetConfigOption("SHAPE_ENCODING", "");
        poDS = (GDALDataset *) GDALOpenEx(theVectorName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
        if (nullptr == poDS) {
            mError = MError::VectorError::ErrCreateDataSource;
            mErrorMessage = "Could not open the geojson file";
            return;
        }
        layerCount = poDS->GetLayerCount();
        pmVectorLayer = new VectorLayer*[layerCount];
        for (int i = 0; i < layerCount; ++i) {
            pmVectorLayer[i] = new VectorLayer(poDS->GetLayer(i));
        }
        GDALClose(poDS);
    }

    MError::VectorError Vector::hasError() {
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
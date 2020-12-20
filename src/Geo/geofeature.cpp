//
// Created by omega on 14/12/2020.
//

#include "geofeature.h"

#include <string>

#include <ogr_api.h>
#include <ogrsf_frmts.h>

#include "src/utils/stringoperate.h"


namespace GisL {

    void GeoFeature::registerOGRDriver() {
        GDALAllRegister();
    }

    GeoFeature::GeoFeature() {
        mError = NoError;
        registerOGRDriver();
    }

    GeoFeature::GeoFeature(const std::string &vectorFileName, const std::string &theFileEncoding) {
        mError = NoError;
        registerOGRDriver();
        loadVector(vectorFileName, theFileEncoding);
    }

    void GeoFeature::loadVector(const std::string &theVectorFileName, const std::string &theFileEncoding) {
        if (theVectorFileName.empty()) {
            mError = ErrCreateDataSource;
            mErrorMessage = "Empty filename given";
            return;
        } else if (StringOperate::isEndWith(theVectorFileName, ".shp") ||
                   StringOperate::isEndWith(theVectorFileName, "dbf")) {
            loadShp(theVectorFileName, theFileEncoding);
        } else if (StringOperate::isEndWith(theVectorFileName, ".geojson")) {
            loadGeoJSON(theVectorFileName, theFileEncoding);
        } else {
            return;
        }
    }

    void GeoFeature::loadShp(const std::string &theShpFileName, const std::string &theFileEncoding) {
        const std::string shpFileHeader = theShpFileName.substr(theShpFileName.length() - 3, 4);
//        poDriver = OGRGetDriverByName("ESRI Shapefile");
//        OGRLayer *mLayer = OGR_DS_CreateLayer();

    }

    void GeoFeature::loadGeoJSON(const std::string &theGeoJsonFileName, const std::string &theFileEncoding) {
        //! ERROR 10: Pointer 'hDriver' is NULL in 'OGRRegisterDriver'.
//        poDriver = OGRGetDriverByName("GeoJSON");
        CPLSetConfigOption("SHAPE_ENCODING", "");
        poDS = (GDALDataset *) GDALOpenEx(theGeoJsonFileName.c_str(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr);
//        poDS = GDALOpen(theGeoJsonFileName.c_str(), GA_ReadOnly);
        if (nullptr == poDS) {
            mError = ErrCreateDataSource;
            mErrorMessage = "Could not open the geojson file";
            return;
        }
        layerCount = poDS->GetLayerCount();
        poLayers = new OGRLayer*[layerCount];
        for (int i = 0; i < layerCount; ++i) {
            poLayers[i] = poDS->GetLayer(i);
        }

    }

    GeoFeature::LoadError GeoFeature::hasError() {
        return mError;
    }

    std::string GeoFeature::errorMessage() {
        return mErrorMessage;
    }


    GeoFeature::~GeoFeature() = default;


}
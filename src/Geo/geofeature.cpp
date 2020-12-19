//
// Created by omega on 14/12/2020.
//

#include "geofeature.h"

#include <string>

#include <gdal.h>
#include <ogr_api.h>

#include "src/utils/stringoperate.h"


namespace GisL {

    void GeoFeature::registerOGRDriver() {
        OGRRegisterDriver(OGRGetDriverByName("ESRI Shapefile"));
        OGRRegisterDriver(OGRGetDriverByName("GeoJSON"));
    }

    GeoFeature::GeoFeature() {
        mError = NoError;
        registerOGRDriver();
    }

    GeoFeature::GeoFeature(const std::string &vectorFileName, const std::string &theFileEncoding) {
        mError = NoError;
        loadVector(vectorFileName, theFileEncoding);
        registerOGRDriver();
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
        poDriver = OGRGetDriverByName("ESRI Shapefile");
        mDS = OGR_Dr_CreateDataSource(poDriver, shpFileHeader.c_str(), nullptr);
//        OGRLayer *mLayer = OGR_DS_CreateLayer();

    }

    void GeoFeature::loadGeoJSON(const std::string &theGeoJsonFileName, const std::string &theFileEncoding) {
        poDriver = OGRGetDriverByName("GeoJSON");
        mDS = OGR_Dr_CreateDataSource(poDriver, theGeoJsonFileName.c_str(), nullptr);
    }

    GeoFeature::LoadError GeoFeature::hasError() {
        return mError;
    }

    std::string GeoFeature::errorMessage() {
        return mErrorMessage;
    }


    GeoFeature::~GeoFeature() = default;


}
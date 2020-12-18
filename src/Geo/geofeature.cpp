//
// Created by omega on 14/12/2020.
//

#include "geofeature.h"

#include <string>

#include <gdal/ogrsf_frmts.h>
#include <gdal/gdal.h>


namespace GisL {

    GeoFeature::GeoFeature() {
        OGRSFDriverH poDriver;
        poDriver = OGRGetDriverByName("ESRI Shapefile");
        OGRRegisterDriver(poDriver);
        poDriver = OGRGetDriverByName("GeoJSON");
        OGRRegisterDriver(poDriver);
    }

    void GeoFeature::loadVector(const std::string& theVectorFileName, const std::string& theFileEncoding) {
        std::string vectorFileName = theVectorFileName;
        if (!vectorFileName.compare(".shp") && !vectorFileName.compare("dbf")) {
            loadShp(vectorFileName, theFileEncoding);
        }
        if (!vectorFileName.compare(".shx")) {
            vectorFileName = vectorFileName.append(".shp");
            loadShp(vectorFileName, theFileEncoding);
        }
        if (!vectorFileName.compare(".geojson")) {

        }
    }

    void GeoFeature::loadShp(const std::string &theVectorFileName, const std::string &theFileEncoding) {

    }


    GeoFeature::~GeoFeature() = default;


}
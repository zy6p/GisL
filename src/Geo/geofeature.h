//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOFEATURE_H
#define GISL_GEOFEATURE_H

#include <string>

#include <ogrsf_frmts.h>

namespace GisL {

    /*!
     * @brief basic unit of geo features
     */
    class GeoFeature {
    public:

        /*!
         * @brief load vector file error
         */
        enum LoadError {
            NoError = 0,
            ErrInFileName,
            ErrDriverNotFound,
            ErrCreateDataSource,
            ErrCreateLayer,
            ErrAttributeTypeUnsupported,
            ErrAttributeCreationFailed,
            ErrProjection,
            ErrFeatureWriteFailed,
            ErrInvalidLayer,
            Canceled, //!< Opening was interrupted by manual cancellation
        };

        LoadError hasError();

        std::string errorMessage();

        GeoFeature();

        explicit GeoFeature(const std::string &vectorFileName, const std::string &theFileEncoding = "utf-8");

        void loadVector(const std::string &theVectorFileName, const std::string &theFileEncoding = "utf-8");

        ~GeoFeature();


    protected:
        LoadError mError;
        std::string mErrorMessage;

        GDALDataset *poDS = nullptr;
        OGRLayer **poLayers;
        int layerCount;

        void loadShp(const std::string &theShpFileName, const std::string &theFileEncoding);

        void loadGeoJSON(const std::string &theGeoJsonFileName, const std::string &theFileEncoding);

        static void registerOGRDriver();
    };

}

#endif //GISL_GEOFEATURE_H

/*!
 * @file featureproperty.h
 * @author omega 
 * @date 24/12/2020
 * 
 * @brief property of feature
 * @details 
 * @verbatim
 *
 */

#ifndef GISL_FEATUREPROPERTY_H
#define GISL_FEATUREPROPERTY_H

#include <string>
#include <gdal/ogr_feature.h>

#include "../utils/merror.h"

namespace GisL {
    class FeatureProperty {
    public:
        explicit FeatureProperty(OGRFeature &poFeature);

        ~FeatureProperty();

        bool hasError( );

        std::string errorMessage( );


    private:
        MError::GisLError mError;
        std::string mErrorMessage;

        OGRFeature *pmFeature;

        int propertyCount;
        OGRFieldDefn **pmPropertyDefn;
        std::string **pmPropertyValue;

    };
}

#endif //GISL_FEATUREPROPERTY_H

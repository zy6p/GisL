/*!
 * @file featureproperty.h
 * @author omega 
 * @date 24/12/2020
 * 
 * @brief property of feature
 * @details 
 *
 *
 */

#ifndef GISL_FEATUREPROPERTY_H
#define GISL_FEATUREPROPERTY_H

#include <string>
#include <gdal/ogr_feature.h>

#include "../utils/gislobject.h"

namespace GisL {
    class FeatureProperty : public GisLObject {
    public:
        explicit FeatureProperty(OGRFeature &poFeature);

        ~FeatureProperty();


    private:

        OGRFeature *pmFeature;

        int propertyCount;
        OGRFieldDefn **pmPropertyDefn;
        std::string **pmPropertyValue;

    };
}

#endif //GISL_FEATUREPROPERTY_H

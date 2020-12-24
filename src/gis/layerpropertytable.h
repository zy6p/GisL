/*!
 * @file layerpropertytable.h
 * @author omega 
 * @date 24/12/2020
 * 
 * @brief layer attribute table
 * @details 
 * @verbatim
 *
 */

#ifndef GISL_LAYERPROPERTYTABLE_H
#define GISL_LAYERPROPERTYTABLE_H

#include <string>
#include <gdal/ogr_feature.h>

#include "featureproperty.h"
#include "../utils/merror.h"

namespace GisL {
    class LayerPropertyTable {
    public:
        explicit LayerPropertyTable(int fidOfLayer);

        void getFeatureCount( int count );

        void append( int fidOfFeature, FeatureProperty &poFeatureProperty);

        ~LayerPropertyTable();

        bool hasError( );

        std::string errorMessage( );

    private:
        MError::GisLError mError;
        std::string mErrorMessage;

        int fid;
        int featureCount;
        FeatureProperty **pmFeatureProperty;



    };
}

#endif //GISL_LAYERPROPERTYTABLE_H

/*!
 * @file layerpropertytable.cpp.cc
 * @author omega 
 * @date 24/12/2020
 * 
 * @brief layer attribute table
 * @details 
 * @verbatim
 *
 */

#include "layerpropertytable.h"

namespace GisL {

    LayerPropertyTable::LayerPropertyTable( int fidOfLayer ) {
        mError = MError::GisLError::NoError;
        mErrorMessage = "";
        fid = fidOfLayer;
        featureCount = 0;
        pmFeatureProperty = nullptr;
    }

    void LayerPropertyTable::getFeatureCount(int count) {
        this->featureCount = count;
        pmFeatureProperty = new FeatureProperty*[featureCount];
    }

    void LayerPropertyTable::append( int fidOfFeature, FeatureProperty &poFeatureProperty ) {
        pmFeatureProperty[fidOfFeature - fid * 100 - 1] = &poFeatureProperty;
    }






    bool LayerPropertyTable::hasError() {
        return mError == MError::GisLError::NoError;
    }

    std::string LayerPropertyTable::errorMessage() {
        return mErrorMessage;
    }

    LayerPropertyTable::~LayerPropertyTable( ) {
        if ( nullptr != pmFeatureProperty ) {
            for ( int i = 0; i < featureCount; ++i ) {
                if ( nullptr != pmFeatureProperty[i] ) {
                    delete pmFeatureProperty[i];
                    pmFeatureProperty[i] = nullptr;
                }
            }
            delete[] pmFeatureProperty;
            pmFeatureProperty = nullptr;
        }


    }


}
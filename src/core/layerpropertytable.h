/*!
 * @file layerpropertytable.h
 * @author omega 
 * @date 24/12/2020
 * 
 * @brief layer StdStringMap table
 * @details 
 *
 *
 */

#ifndef GISL_LAYERPROPERTYTABLE_H
#define GISL_LAYERPROPERTYTABLE_H

#include <string>
#include <ogr_feature.h>

#include "featureproperty.h"
#include "../utils/gislobject.h"

namespace GisL {
    class LayerPropertyTable : public GisLObject {
    public:
        explicit LayerPropertyTable( int fidOfLayer );

        void getFeatureCount( int count );

        void append( int fidOfFeature, FeatureProperty &poFeatureProperty );

        ~LayerPropertyTable( );

    private:

        int fid;
        int featureCount;
        FeatureProperty **pmFeatureProperty;


    };
}

#endif //GISL_LAYERPROPERTYTABLE_H

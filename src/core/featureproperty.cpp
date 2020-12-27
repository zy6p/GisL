/*!
 * @file featureproperty.cpp
 * @author omega 
 * @date 24/12/2020
 * 
 * @brief field
 * @details 
 *
 *
 */

#include "featureproperty.h"

namespace GisL {

    /*!
     * @brief feature property
     * @param poFeature
     */
    FeatureProperty::FeatureProperty( OGRFeature &poFeature ) : GisLObject() {
        pmFeature = &poFeature;

        propertyCount = pmFeature->GetFieldCount();
        pmPropertyDefn = new OGRFieldDefn *[propertyCount];
        pmPropertyValue = new std::string *[propertyCount];
        for ( int i = 0; i < propertyCount; ++i ) {
            pmPropertyDefn[i] = pmFeature->GetFieldDefnRef( i );
            pmPropertyValue[i] = new std::string;
            pmPropertyValue[i]->push_back( *pmFeature->GetFieldAsString( i ));

        }

    }


    FeatureProperty::~FeatureProperty( ) {
        if ( nullptr != pmPropertyDefn ) {
            for ( int i = 0; i < propertyCount; ++i ) {
                if ( nullptr != pmPropertyDefn[i] ) {
                    delete pmPropertyDefn[i];
                    pmPropertyDefn[i] = nullptr;
                }
                delete[] pmPropertyDefn;
                pmPropertyDefn = nullptr;
            }
        }

        if ( nullptr != pmPropertyValue ) {
            for ( int i = 0; i < propertyCount; ++i ) {
                if ( nullptr != pmPropertyValue[i] ) {
                    delete pmPropertyValue[i];
                    pmPropertyValue[i] = nullptr;
                }
                delete[] pmPropertyValue;
                pmPropertyValue = nullptr;
            }
        }

    }
}
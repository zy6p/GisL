/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorlayer.h"

#include <gdal/ogrsf_frmts.h>

#include "vectorfeature.h"

namespace GisL {

    void VectorLayer::seed(const int fidInVector) {
        fidInLayer = fidInVector * 100;
    }

    VectorLayer::VectorLayer(OGRLayer &poLayer) {
        fid = ++fidInLayer;
        pmLayer = &poLayer;
        if ( nullptr == pmLayer->GetSpatialRef()) {
            pmCrs = nullptr;
            mError.push_back( MError::GisLError::ErrSpatialRef );
            mErrorMessage.append( "Warning: No spatial reference in this layer!\n" );
        } else {
            pmCrs = new SpatialReference( pmLayer->GetSpatialRef());
        }

        if ( !pmLayer->GetExtent( pmExtent )) {
            pmExtent = nullptr;
            mError.push_back( MError::GisLError::ErrExtent );
            mErrorMessage.append( "Warning: can not fetch the extent of this layer!\n" );
        }

        VectorLayer::seed( fid );
        featureCount = pmLayer->GetFeatureCount();
        pmFeature = new VectorFeature *[featureCount];
        for ( int i = featureCount - 1; i >= 0; --i ) {
            pmFeature[i] = new VectorFeature( *pmLayer->GetFeature( i ));
        }

    }

    VectorLayer &VectorLayer::operator=(const VectorLayer& rhs) {
        return *this;
    }

    bool VectorLayer::hasError() {
        return mError.empty();
    }

    std::string VectorLayer::errorMessage() {
        return mErrorMessage;
    }

    VectorLayer::~VectorLayer() = default;
}

/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorlayer.h"

#include <gdal/ogrsf_frmts.h>

namespace GisL {
    VectorLayer::VectorLayer(OGRLayer *poLayer) {
        pmLayer = poLayer;

        if (nullptr == pmLayer->GetSpatialRef()) {
            pmCrs = nullptr;
            mError.push_back(MError::VectorError::ErrSpatialRef);
            mErrorMessage.append("Warning: No spatial reference in this layer!\n");
        } else {
            pmCrs = new SpatialReference(pmLayer->GetSpatialRef());
        }

        if (!pmLayer->GetExtent(pmExtent)) {
            pmExtent = nullptr;
            mError.push_back(MError::VectorError::ErrExtent);
            mErrorMessage.append("Warning: can not fetch the extent of this layer!\n");
        }

        featureCount = pmLayer->GetFeatureCount();
        for (auto &poFeature: poLayer) {

        }

    }

    VectorLayer::~VectorLayer() = default;
}

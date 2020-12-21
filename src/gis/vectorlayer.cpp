/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorlayer.h"

#include <gdal/ogrsf_frmts.h>

namespace GisL {
    VectorLayer::VectorLayer(OGRLayer *poLayer) {
        pmLayer = poLayer;
        pmCrs = new SpatialReference(pmLayer->GetSpatialRef());
        featureCount = pmLayer->GetFeatureCount();
        for (auto &poFeature: poLayer) {

        }

    }

    VectorLayer::~VectorLayer() = default;
}

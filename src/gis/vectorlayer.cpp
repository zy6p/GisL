/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorlayer.h"

#include <gdal/ogrsf_frmts.h>

#include "vectorfeature.h"

namespace GisL {

    int VectorLayer::fidInLayer = 100;

    void VectorLayer::seed(const int fidInVector) {
        VectorLayer::fidInLayer = fidInVector * 100;
    }

    VectorLayer::VectorLayer(OGRLayer &poLayer) {
        fid = ++VectorLayer::fidInLayer;
        pmLayer = &poLayer;
        if (nullptr == pmLayer->GetSpatialRef()) {
            pmCrs = nullptr;
//            mError = MError::GisLError::ErrSpatialRef;
            mErrorMessage.append("Warning: No spatial reference in this layer!\n");
        } else {
            pmCrs = new SpatialReference(*pmLayer->GetSpatialRef());
        }

        pmExtent = nullptr;
        getExtent();

        VectorLayer::seed(fid);
        featureCount = pmLayer->GetFeatureCount();
        pmFeature = new VectorFeature *[featureCount];
        for (int i = featureCount - 1; i >= 0; --i) {
            pmFeature[i] = new VectorFeature(*pmLayer->GetFeature(i));
        }

    }

    void VectorLayer::getExtent() {
        OGREnvelope temp;
        OGRErr ddss = pmLayer->GetExtent(&temp);
        pmExtent = new OGREnvelope(temp);
        if (nullptr == pmExtent) {
//            mError = MError::ErrExtent;
            mErrorMessage.append("Warning: can not fetch the extent of this layer!\n");
        }
    }

    VectorLayer &VectorLayer::operator=(const VectorLayer &rhs) {
        return *this;
    }

    bool VectorLayer::hasError() {
        return mError == MError::GisLError::NoError;
    }

    std::string VectorLayer::errorMessage() {
        return mErrorMessage;
    }

    VectorLayer::~VectorLayer() {
        if (nullptr != pmExtent) {
            delete pmExtent;
            pmExtent = nullptr;
        }

        if (nullptr != pmFeature) {
            for (int i = featureCount - 1; i >= 0; --i) {
                if (nullptr != pmFeature[i]) {
                    delete pmFeature;
                    pmFeature = nullptr;
                }
            }
            delete[] pmFeature;
            pmFeature = nullptr;
        }

        if (nullptr != pmCrs) {
            delete pmCrs;
            pmCrs = nullptr;
        }

    };
}

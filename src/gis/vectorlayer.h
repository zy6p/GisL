/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_VECTORLAYER_H
#define GISL_VECTORLAYER_H

#include <string>
#include <vector>
#include <gdal/ogrsf_frmts.h>

#include "spatialreference.h"
#include "../utils/merror.h"

namespace GisL {
    class VectorLayer {
    public:
        explicit VectorLayer(OGRLayer *poLayer);

        SpatialReference *pmCrs;
        int featureCount;


        ~VectorLayer();

    private:
        std::vector<MError::VectorError> mError;
        std::string mErrorMessage;

        OGRLayer *pmLayer;

        OGREnvelope *pmExtent;
    };
}


#endif //GISL_VECTORLAYER_H

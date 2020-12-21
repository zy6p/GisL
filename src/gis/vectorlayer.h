/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_VECTORLAYER_H
#define GISL_VECTORLAYER_H

#include <gdal/ogrsf_frmts.h>

#include "spatialreference.h"

namespace GisL {
    class VectorLayer {
    public:
        explicit VectorLayer(OGRLayer *poLayer);

        SpatialReference *pmCrs;
        int featureCount;
        


        ~VectorLayer();

    private:
        OGRLayer *pmLayer;

    };
}


#endif //GISL_VECTORLAYER_H

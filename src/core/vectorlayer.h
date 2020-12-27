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
#include "layerpropertytable.h"
#include "../utils/gislobject.h"
#include "vectorfeature.h"

namespace GisL {
    class VectorLayer : public GisLObject {
    public:

        static void seed( int fidInVector );

        explicit VectorLayer( OGRLayer &poLayer );

        VectorLayer &operator=( const VectorLayer &rhs );

        SpatialReference *pmCrs;

        int getFeatureCount( ) const;

        ~VectorLayer( );

    private:
        static int fidInLayer;
        int fid;

        int featureCount;

        OGRLayer *pmLayer;
        OGREnvelope *pmExtent;

        VectorFeature **pmFeature;

        LayerPropertyTable *pmLayerPropertyTable;

        void getExtent( );
    };
}


#endif //GISL_VECTORLAYER_H

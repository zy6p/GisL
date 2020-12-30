/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_VECTORFEATURE_H
#define GISL_VECTORFEATURE_H

#include <string>
#include <gdal/ogr_feature.h>

#include "geometry/abstractgeometry.h"
#include "featureproperty.h"
#include "../utils/gislobject.h"

namespace GisL {
    class VectorFeature : public GisLObject {
    public:
        static void seed( int fidInLayer );

        explicit VectorFeature( OGRFeature &poFeature );

        VectorFeature &operator=( const VectorFeature &rhs );

        int getFid( ) const;

        FeatureProperty *getPmFeatureProperty( ) const;

        ~VectorFeature( );

    private:

        FeatureProperty *pmFeatureProperty;

        OGRFeature *pmFeature;

        static int fidInFeature;
        int fid;

        AbstractGeometry *pmGeometry;
        AbstractGeometry::WkbType geoType;

        void defineGeo( );
    };
}

#endif //GISL_VECTORFEATURE_H

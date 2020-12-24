/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_VECTORFEATURE_H
#define GISL_VECTORFEATURE_H

#include <string>
#include <gdal/ogr_feature.h>

#include "geometry.h"
#include "featureproperty.h"
#include "../utils/merror.h"

namespace GisL {
    class VectorFeature {
    public:
        static void seed(int fidInLayer);

        explicit VectorFeature(OGRFeature &poFeature);

        VectorFeature &operator=(const VectorFeature &rhs);

        ~VectorFeature();

        bool hasError();

        std::string errorMessage();

    private:
        MError::GisLError mError;
        std::string mErrorMessage;

//        int fieldCount;

        FeatureProperty *pmFeatureProperty;

        OGRFeature *pmFeature;

        static int fidInFeature;
        int fid;

        Geometry *pmGeometry;
        OGRGeometry *poGeometry;
        Geometry::GeoType geoType;

        void defineGeo(OGRFeature &poFeature);
    };
}

#endif //GISL_VECTORFEATURE_H

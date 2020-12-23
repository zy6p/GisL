/*!
 * @author tau 
 * @date 12/20/20
*/

#ifndef GISL_VECTORFEATURE_H
#define GISL_VECTORFEATURE_H

#include <string>
#include <gdal/ogr_feature.h>

#include "geometry.h"

namespace GisL {
    class VectorFeature {
    public:
        static void seed(int fidInLayer);

        explicit VectorFeature(OGRFeature &poFeature);

        VectorFeature &operator=( const VectorFeature &rhs);

    private:
        int fieldCount;

        std::string **strField;

        OGRFeature *pmFeature;

        static int fidInFeature;
        int fid;

        Geometry *pmGeometry;

    };
}

#endif //GISL_VECTORFEATURE_H

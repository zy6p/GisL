/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorfeature.h"

//#include <gdal/ogrsf_frmts.h>

namespace GisL {

    void VectorFeature::seed(const int fidInLayer) {
        fidInFeature = fidInLayer * 100;
    }

    VectorFeature::VectorFeature(OGRFeature &poFeature) {
        fid = ++fidInFeature;
        pmFeature = &poFeature;

        fieldCount = pmFeature->GetFieldCount();
        strField = new std::string *[fieldCount];
        for ( int i = fieldCount - 1; i >= 0; --i ) {
//            strField[i] = new OGR_F_GetFieldAsString()
        }

        pmGeometry = new Geometry( *poFeature.GetGeometryRef());

    }

    VectorFeature &VectorFeature::operator=( const VectorFeature &rhs) {
        return *this;
    }

}
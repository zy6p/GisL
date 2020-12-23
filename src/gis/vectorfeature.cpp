/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorfeature.h"

#include <gdal/ogr_feature.h>

#include "geopoint.h"
#include "geoline.h"
#include "geopolygon.h"
#include "geomultipoint.h"
#include "geomultiline.h"
#include "geomultipolygon.h"

namespace GisL {

    int VectorFeature::fidInFeature = 10100;

    void VectorFeature::seed(const int fidInLayer) {
        VectorFeature::fidInFeature = fidInLayer * 100;
    }

    VectorFeature::VectorFeature(OGRFeature &poFeature) {
        fid = ++VectorFeature::fidInFeature;
        pmFeature = &poFeature;

        fieldCount = pmFeature->GetFieldCount();
        strField = new std::string *[fieldCount];
        for (int i = fieldCount - 1; i >= 0; --i) {
//            strField[i] = new OGR_F_GetFieldAsString()
        }

        pmGeometry = nullptr;
        poGeometry = nullptr;
        geoType = Geometry::GeoType::None;
        defineGeo(poFeature);

    }

    bool VectorFeature::hasError() {
        return mError == MError::GisLError::NoError;
    }

    std::string VectorFeature::errorMessage() {
        return mErrorMessage;
    }

    void VectorFeature::defineGeo(OGRFeature &poFeature) {
        poGeometry = poFeature.GetGeometryRef();
        geoType = Geometry::detectGeoType(*poGeometry);
        switch (geoType) {
            default:
                break;
            case Geometry::GeoType::None: {
                mError = MError::GisLError::ErrGeometry;
                mErrorMessage = "Wrong! no geometry here\n";
                break;
            }
            case Geometry::Point: {
                pmGeometry = new GeoPoint(*poGeometry);
                break;
            }
            case Geometry::LineString: {
                pmGeometry = new GeoLine(*poGeometry);
                break;
            }
            case Geometry::Polygon: {
                pmGeometry = new GeoPolygon(*poGeometry);
                break;
            }
            case Geometry::MultiPoint: {
                pmGeometry = new GeoMultiPoint(*poGeometry);
                break;
            }
            case Geometry::MultiLineString: {
                pmGeometry = new GeoMultiLine(*poGeometry);
                break;
            }
            case Geometry::MultiPolygon: {
                pmGeometry = new GeoMultiPolygon(*poGeometry);
                break;
            }
        }
    }

    VectorFeature &VectorFeature::operator=(const VectorFeature &rhs) {
        return *this;
    }

    VectorFeature::~VectorFeature() {
        if (nullptr != strField) {
            for (int i = 0; i < fieldCount; ++i) {
                if (nullptr != strField[i]) {
                    delete strField[i];
                    strField[i] = nullptr;
                }
                delete[] strField;
                strField = nullptr;
            }
        }

        if (nullptr != pmGeometry) {
            delete pmGeometry;
            pmGeometry = nullptr;
        }

    }

}
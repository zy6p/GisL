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
        mError = MError::GisLError::NoError;
        mErrorMessage = "";

        fid = ++VectorFeature::fidInFeature;
        pmFeature = &poFeature;

        pmFeatureProperty = new FeatureProperty(*pmFeature);

//        fieldCount = pmFeature->GetFieldCount();
//        pmFeatureProperty = new FeatureProperty*[fieldCount];
//        for (int i = fieldCount - 1; i >= 0; --i) {
//            pmFeatureProperty[i] = new FeatureProperty(*pmFeature->GetFieldDefnRef(i));
//        }

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
        if (nullptr != pmFeatureProperty) {
            delete pmFeatureProperty;
            pmFeatureProperty = nullptr;
        }

        if (nullptr != pmGeometry) {
            delete pmGeometry;
            pmGeometry = nullptr;
        }

    }

}
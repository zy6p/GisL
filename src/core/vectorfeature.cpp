/*!
 * @author tau 
 * @date 12/20/20
*/

#include "vectorfeature.h"

#include <gdal/ogr_feature.h>
#include <external/KkGis/GeoPolygon.h>

#include "geometry/geompoint.h"
#include "geometry/geomline.h"
#include "geometry/geompolygon.h"
#include "geometry/geommultipoint.h"
#include "geometry/geommultiline.h"
#include "geometry/geommultipolygon.h"
#include "../utils/ptroperate.h"

namespace GisL {

    int VectorFeature::fidInFeature = 10100;

    void VectorFeature::seed( const int fidInLayer ) {
        VectorFeature::fidInFeature = fidInLayer * 100;
    }

    VectorFeature::VectorFeature( OGRFeature &poFeature ) : GisLObject() {

        fid = ++VectorFeature::fidInFeature;
        pmFeature = &poFeature;

        pmFeatureProperty = new FeatureProperty( *pmFeature );

        pmGeometry = nullptr;
        geoType = AbstractGeometry::WkbType::NoGeometry;
        defineGeo( poFeature );

    }

    void VectorFeature::defineGeo( OGRFeature &poFeature ) {
        pmGeometry = dynamic_cast<AbstractGeometry *>(poFeature.GetGeometryRef());
        AbstractGeometry::detectWkbType(*pmGeometry);
        AbstractGeometry::WkbType type = pmGeometry->wkbType();
        switch ( type ) {
            default:
                break;
            case AbstractGeometry::Unknown:

            case AbstractGeometry::NoGeometry: {
                mError = MError::GisLError::ErrGeometry;
                mErrorMessage = "Wrong! no geometry here\n";
                break;
            }
            case AbstractGeometry::Point: {
                pmGeometry = new GeomPoint;
                break;
            }
            case Geometry::LineString: {
                pmGeometry = new GeoLine( *poGeometry );
                break;
            }
            case Geometry::Polygon: {
                pmGeometry = new GeoPolygon( *poGeometry );
                break;
            }
            case Geometry::MultiPoint: {
                pmGeometry = new GeoMultiPoint( *poGeometry );
                break;
            }
            case Geometry::MultiLineString: {
                pmGeometry = new GeoMultiLine( *poGeometry );
                break;
            }
            case Geometry::MultiPolygon: {
                pmGeometry = new GeoMultiPolygon( *poGeometry );
                break;
            }
        }
    }

    VectorFeature &VectorFeature::operator=( const VectorFeature &rhs ) {
        return *this;
    }

    VectorFeature::~VectorFeature( ) {
        PtrOperate::clear( pmFeatureProperty );
        PtrOperate::clear( pmGeometry );

    }

    int VectorFeature::getFid( ) const {
        return fid;
    }

    FeatureProperty *VectorFeature::getPmFeatureProperty( ) const {
        return pmFeatureProperty;
    }

    void VectorFeature::paint( ) {
        pmGeometry->hasError();
    }

}
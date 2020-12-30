//
// Created by omega on 14/12/2020.
//

#include "geompoint.h"

#include <gdal/ogr_geometry.h>

namespace GisL {

    GeomPoint::GeomPoint( ) {

        mWkbType = Point;
    }

    Rectangle *GeomPoint::boundary( ) const {
        Rectangle *p;
        OGRPoint::getEnvelope( p );
        return p;
    }

    void GeomPoint::clear( ) {
        OGRPoint::empty();
    }

    void GeomPoint::draw( ) {
        //todo how to do it?
    }

    bool GeomPoint::isEmpty( ) const {
        return OGRPoint::IsEmpty();
    }

    GeomPoint::~GeomPoint( ) {
        GeomPoint::clear();
    }

    int GeomPoint::WkbSize( ) const {
        return OGRPoint::WkbSize();
    }

    OGRErr
    GeomPoint::importFromWkb( const unsigned char *string, int i, OGRwkbVariant variant, int &nBytesConsumedOut ) {
        return OGRPoint::importFromWkb( string, i, variant, nBytesConsumedOut );
    }

    OGRErr GeomPoint::exportToWkb( OGRwkbByteOrder order, unsigned char *string, OGRwkbVariant variant ) const {
        return OGRPoint::exportToWkb( order, string, variant );
    }

    OGRErr GeomPoint::importFromWkt( const char **pString ) {
        return OGRPoint::importFromWkt( pString );
    }

    std::string GeomPoint::exportToWkt( const OGRWktOptions &opts, OGRErr *err ) const {
        return OGRPoint::exportToWkt( opts, err );
    }

    int GeomPoint::getDimension( ) const {
        return OGRPoint::getDimension();
    }

    OGRGeometry *GeomPoint::clone( ) const {
        return OGRPoint::clone();
    }

    void GeomPoint::empty( ) {
        OGRPoint::empty();
    }

    void GeomPoint::getEnvelope( OGREnvelope *psEnvelope ) const {
        OGRPoint::getEnvelope( psEnvelope );
    }

    void GeomPoint::getEnvelope( OGREnvelope3D *psEnvelope ) const {
        OGRPoint::getEnvelope( psEnvelope );
    }

    OGRBoolean GeomPoint::IsEmpty( ) const {
        return OGRPoint::IsEmpty();
    }

    void GeomPoint::setCoordinateDimension( int nDimension ) {
        OGRPoint::setCoordinateDimension( nDimension );
    }

    OGRBoolean GeomPoint::Equals( const OGRGeometry *geometry ) const {
        return OGRPoint::Equals( geometry );
    }

    OGRBoolean GeomPoint::Intersects( const OGRGeometry *geometry ) const {
        return OGRPoint::Intersects( geometry );
    }

    OGRBoolean GeomPoint::Within( const OGRGeometry *geometry ) const {
        return OGRPoint::Within( geometry );
    }

    const char *GeomPoint::getGeometryName( ) const {
        return OGRPoint::getGeometryName();
    }

    OGRwkbGeometryType GeomPoint::getGeometryType( ) const {
        return OGRPoint::getGeometryType();
    }

    OGRErr GeomPoint::transform( OGRCoordinateTransformation *poCT ) {
        return OGRPoint::transform( poCT );
    }

    void GeomPoint::flattenTo2D( ) {
        OGRPoint::flattenTo2D();
    }

    void GeomPoint::accept( IOGRGeometryVisitor *visitor ) {
        OGRPoint::accept( visitor );
    }

    void GeomPoint::accept( IOGRConstGeometryVisitor *visitor ) const {
        OGRPoint::accept( visitor );
    }

    void GeomPoint::swapXY( ) {
        OGRPoint::swapXY();
    };
}
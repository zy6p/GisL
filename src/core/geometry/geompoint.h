//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOMPOINT_H
#define GISL_GEOMPOINT_H

#include <gdal/ogr_geometry.h>

#include "abstractgeometry.h"
#include "../../utils/ptroperate.h"

namespace GisL {
    class GeomPoint : public AbstractGeometry, public OGRPoint {
    public:
        explicit GeomPoint( );

        ~GeomPoint( ) override;

        Rectangle *boundary( ) const override;

        void clear( ) override;

        void draw( ) override;

        bool isEmpty( ) const override;

        int WkbSize( ) const override;

        OGRErr
        importFromWkb( const unsigned char *string, int i, OGRwkbVariant variant, int &nBytesConsumedOut ) override;

        OGRErr exportToWkb( OGRwkbByteOrder order, unsigned char *string, OGRwkbVariant variant ) const override;

        OGRErr importFromWkt( const char **pString ) override;

        std::string exportToWkt( const OGRWktOptions &opts, OGRErr *err ) const override;

        int getDimension( ) const override;

        OGRGeometry *clone( ) const override;

        void empty( ) override;

        void getEnvelope( OGREnvelope *psEnvelope ) const override;

        void getEnvelope( OGREnvelope3D *psEnvelope ) const override;

        OGRBoolean IsEmpty( ) const override;

        void setCoordinateDimension( int nDimension ) override;

        OGRBoolean Equals( const OGRGeometry *geometry ) const override;

        OGRBoolean Intersects( const OGRGeometry *geometry ) const override;

        OGRBoolean Within( const OGRGeometry *geometry ) const override;

        const char *getGeometryName( ) const override;

        OGRwkbGeometryType getGeometryType( ) const override;

        OGRErr transform( OGRCoordinateTransformation *poCT ) override;

        void flattenTo2D( ) override;

        void accept( IOGRGeometryVisitor *visitor ) override;

        void accept( IOGRConstGeometryVisitor *visitor ) const override;

        void swapXY( ) override;

    private:

    };

}

#endif //GISL_GEOMPOINT_H

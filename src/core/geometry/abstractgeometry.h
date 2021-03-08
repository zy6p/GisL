/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_ABSTRACTGEOMETRY_H
#define GISL_ABSTRACTGEOMETRY_H

#include <ogr_geometry.h>
#include "../../gui/painter/painterfactory.h"

#include "rectangle.h"

namespace GisL {
    class AbstractGeometry {

    public:
        enum WkbType {
            Unknown = 0,
            Point = 1,
            LineString = 2,
            Polygon = 3,
            Triangle = 17,
            MultiPoint = 4,
            MultiLineString = 5,
            MultiPolygon = 6,
            GeometryCollection = 7,
            CircularString = 8,
            CompoundCurve = 9,
            CurvePolygon = 10, //13, //should be 10. Seems to be correct in newer PostGIS versions
            MultiCurve = 11,
            MultiSurface = 12,
            NoGeometry = 100, //attributes only
            PointZ = 1001,
            LineStringZ = 1002,
            PolygonZ = 1003,
            TriangleZ = 1017,
            MultiPointZ = 1004,
            MultiLineStringZ = 1005,
            MultiPolygonZ = 1006,
            GeometryCollectionZ = 1007,
            CircularStringZ = 1008,
            CompoundCurveZ = 1009,
            CurvePolygonZ = 1010,
            MultiCurveZ = 1011,
            MultiSurfaceZ = 1012,
            PointM = 2001,
            LineStringM = 2002,
            PolygonM = 2003,
            TriangleM = 2017,
            MultiPointM = 2004,
            MultiLineStringM = 2005,
            MultiPolygonM = 2006,
            GeometryCollectionM = 2007,
            CircularStringM = 2008,
            CompoundCurveM = 2009,
            CurvePolygonM = 2010,
            MultiCurveM = 2011,
            MultiSurfaceM = 2012,
            PointZM = 3001,
            LineStringZM = 3002,
            PolygonZM = 3003,
            MultiPointZM = 3004,
            MultiLineStringZM = 3005,
            MultiPolygonZM = 3006,
            GeometryCollectionZM = 3007,
            CircularStringZM = 3008,
            CompoundCurveZM = 3009,
            CurvePolygonZM = 3010,
            MultiCurveZM = 3011,
            MultiSurfaceZM = 3012,
            TriangleZM = 3017,
            Point25D = 0x80000001,
            LineString25D,
            Polygon25D,
            MultiPoint25D,
            MultiLineString25D,
            MultiPolygon25D
        };

        enum GeomErr {
            NoErr = 0,
            ErrNoGeom,
            ErrCoord,
            ErrCrs,
            ErrBoundary
        };

        AbstractGeometry( ) = default;

        explicit AbstractGeometry( OGRGeometry &p );

        inline WkbType wkbType( ) const {
            return mWkbType;
        }

        virtual Rectangle *boundary( ) const;

        virtual void clear( );

        static void detectWkbType( AbstractGeometry &p );

        virtual OGRGeometry *getGeometry( ) const;

        /*!
         * @todo need a param, such as paint class
         */
        virtual void draw( PainterFactory &p ) = 0;

        virtual bool isEmpty( ) const = 0;

        bool hasError( ) const;

        const std::string &getFeatureName( ) const;

        void setFeatureName( const std::string &name );

        ~AbstractGeometry( );

    protected:

        OGRGeometry *pmGeometry = nullptr;

        WkbType mWkbType = WkbType::Unknown;

        GeomErr mGeomErr = NoErr;

        std::string featureName;
    };
}

#endif //GISL_ABSTRACTGEOMETRY_H

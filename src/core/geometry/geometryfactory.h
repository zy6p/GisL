/*!
 * @file geometryfactory.h
 * @author omega 
 * @date 30/12/2020
 * 
 * @brief 程序的简要说明
 * @details
 */

#ifndef GISL_GEOMETRYFACTORY_H
#define GISL_GEOMETRYFACTORY_H

#include "abstractgeometry.h"
#include "geompoint.h"
#include "geomlinestring.h"
#include "geompolygon.h"
#include "geommultipoint.h"
#include "geommultilinestring.h"
#include "geommultipolygon.h"

namespace GisL {
    class GeometryFactory {
    public:

        static GeomPoint *toPoint( AbstractGeometry &abstractGeometry );

        static GeomLineString *toLineString( AbstractGeometry &abstractGeometry );

        static GeomPolygon *toPolygon( AbstractGeometry &abstractGeometry );

        static GeomMultiPoint *toMultiPoint( AbstractGeometry &abstractGeometry );

        static GeomMultiLineString *toMultiLineString( AbstractGeometry &abstractGeometry );

        static GeomMultiPolygon *toMultiPolygon( AbstractGeometry &abstractGeometry );

//        void detectWkbType( AbstractGeometry &p );
    };
}

#endif //GISL_GEOMETRYFACTORY_H

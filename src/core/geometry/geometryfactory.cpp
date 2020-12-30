/*!
 * @file geometryfactory.cpp
 * @author omega 
 * @date 30/12/2020
 * 
 * @brief 程序的简要说明
 * @details
 */

#include "geometryfactory.h"

GisL::GeomPoint *GisL::GeometryFactory::toPoint( GisL::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomPoint( *abstractGeometry.getGeometry()->toPoint());
    return p;
}

GisL::GeomLineString *GisL::GeometryFactory::toLineString( GisL::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomLineString( *abstractGeometry.getGeometry()->toLineString());
    return p;
}

GisL::GeomPolygon *GisL::GeometryFactory::toPolygon( GisL::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomPolygon( *abstractGeometry.getGeometry()->toPolygon());
    return p;
}

GisL::GeomMultiPoint *GisL::GeometryFactory::toMultiPoint( GisL::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomMultiPoint( *abstractGeometry.getGeometry()->toMultiPoint());
    return p;
}

GisL::GeomMultiLineString *
GisL::GeometryFactory::toMultiLineString( GisL::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomMultiLineString( *abstractGeometry.getGeometry()->toMultiLineString());
    return p;
}

GisL::GeomMultiPolygon *GisL::GeometryFactory::toMultiPolygon( GisL::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomMultiPolygon( *abstractGeometry.getGeometry()->toMultiPolygon());
    return p;
}



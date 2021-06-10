/*!
 * @file geometryfactory.cpp
 * @author omega 
 * @date 30/12/2020
 * 
 * @brief 程序的简要说明
 * @details
 */

#include "geometryfactory.h"

gisl::GeomPoint *gisl::GeometryFactory::toPoint( gisl::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomPoint( *abstractGeometry.getGeometry()->toPoint());
    return p;
}

gisl::GeomLineString *gisl::GeometryFactory::toLineString( gisl::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomLineString( *abstractGeometry.getGeometry()->toLineString());
    return p;
}

gisl::GeomPolygon *gisl::GeometryFactory::toPolygon( gisl::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomPolygon( *abstractGeometry.getGeometry()->toPolygon());
    return p;
}

gisl::GeomMultiPoint *gisl::GeometryFactory::toMultiPoint( gisl::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomMultiPoint( *abstractGeometry.getGeometry()->toMultiPoint());
    return p;
}

gisl::GeomMultiLineString *
gisl::GeometryFactory::toMultiLineString( gisl::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomMultiLineString( *abstractGeometry.getGeometry()->toMultiLineString());
    return p;
}

gisl::GeomMultiPolygon *gisl::GeometryFactory::toMultiPolygon( gisl::AbstractGeometry &abstractGeometry ) {
    auto *p = new GeomMultiPolygon( *abstractGeometry.getGeometry()->toMultiPolygon());
    return p;
}



/*!
 * @file geometryabstractfactory.cpp.cc
 * @author omega 
 * @date 30/12/2020
 * 
 * @brief 程序的简要说明
 * @details 
 * @verbatim
 * 程序的详细说明。
 */

#include "geometryabstractfactory.h"

GisL::GeomPoint *GisL::GeometryAbstractFactory::toPoint( GisL::AbstractGeometry &abstractGeometry ) {
    return dynamic_cast<GeomPoint *>(abstractGeometry.toPoint());
}

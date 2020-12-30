/*!
 * @file geometryabstractfactory.h
 * @author omega 
 * @date 30/12/2020
 * 
 * @brief 程序的简要说明
 * @details 
 * @verbatim
 * 程序的详细说明。
 */

#ifndef GISL_GEOMETRYABSTRACTFACTORY_H
#define GISL_GEOMETRYABSTRACTFACTORY_H

#include "abstractgeometry.h"
#include "geompoint.h"
#include "geomline.h"
#include "geompolygon.h"
#include "geompoint.h"
#include "geommultiline.h"
#include "geompolygon.h"

namespace GisL {
    class GeometryAbstractFactory {
    public:

        static GeomPoint *toPoint(AbstractGeometry &abstractGeometry);

    };
}

#endif //GISL_GEOMETRYABSTRACTFACTORY_H

//
// Created by omega on 14/12/2020.
//

#ifndef GISL_LAYERRENDER_H
#define GISL_LAYERRENDER_H

#include "sld.h"
#include "../gis/geometry.h"
#include "../utils/gislobject.h"

namespace GisL {

    /*!
     * basic unit of map
     */
    class LayerRender : GisLObject {

    public:
        explicit LayerRender( Geometry &poGeometry);

        explicit LayerRender( Geometry &poGeometry, Sld &poSld);

        LayerRender &operator=( const LayerRender &ths);

    private:

        Geometry *pmGeometry;
        Sld *pmSld;

        void init();
    };

}

#endif //GISL_LAYERRENDER_H

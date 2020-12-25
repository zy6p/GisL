//
// Created by omega on 14/12/2020.
//

#ifndef GISL_RENDER_H
#define GISL_RENDER_H

#include "sld.h"
#include "../gis/geometry.h"
#include "../utils/gislobject.h"

namespace GisL {

    /*!
     * basic unit of map
     */
    class Render : GisLObject {
    public:
        explicit Render(Geometry &poGeometry);

        explicit Render(Geometry &poGeometry, Sld &poSld);

        Render &operator=(const Render &ths);

    private:

        Geometry *pmGeometry;
        Sld *pmSld;

        void init();
    };

}

#endif //GISL_RENDER_H

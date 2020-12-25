//
// Created by omega on 14/12/2020.
//

#include "render.h"

#include "sld.h"

namespace GisL {

    Render::Render(Geometry &poGeometry, Sld &poSld) {
        pmGeometry = &poGeometry;
        pmSld = &poSld;
    }

    Render::Render(Geometry &poGeometry) {
        pmSld = nullptr;
        pmGeometry = &poGeometry;
        init();
    }

    /*!
     * @brief init Render with Geometry, not Sld
     */
    void Render::init() {

    }

    Render &Render::operator=(const Render &rhs) {
        return *this;
    }


}
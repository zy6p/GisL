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

    bool Render::hasError() {
        return mError == MError::GisLError::NoError;
    }

    std::string Render::errorMessage() {
        return mErrorMessage;
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
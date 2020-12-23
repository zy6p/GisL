//
// Created by omega on 14/12/2020.
//

#ifndef GISL_RENDER_H
#define GISL_RENDER_H

#include "sld.h"
#include "../gis/geometry.h"
#include "../utils/merror.h"

namespace GisL {

    /*!
     * basic unit of map
     */
    class Render {
    public:
        explicit Render(Geometry &poGeometry);

        explicit Render(Geometry &poGeometry, Sld &poSld);

        Render &operator=(const Render &ths);

        std::string errorMessage();

        bool hasError();

    private:
        MError::GisLError mError;
        std::string mErrorMessage;

        Geometry *pmGeometry;
        Sld *pmSld;

        void init();
    };

}

#endif //GISL_RENDER_H

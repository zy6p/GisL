//
// Created by omega on 14/12/2020.
//

#ifndef GISL_GEOFEATURE_H
#define GISL_GEOFEATURE_H

#include <string>

namespace GisL {

    /*!
     * @brief basic unit of geo features
     */
    class GeoFeature {
    public:
        GeoFeature();

        void loadVector(const std::string& theVectorFileName, const std::string& theFileEncoding);

        void loadShp(const std::string &theVectorFileName, const std::string &theFileEncoding);

        ~GeoFeature();

    };

}

#endif //GISL_GEOFEATURE_H

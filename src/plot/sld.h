//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <string>
#include <vector>

#include "../utils/merror.h"

namespace GisL {

    /*!
     * Styled Layer Descriptor
     */
    class Sld {
    public:
        Sld();
        Sld(const std::string& theSldFilename);


    private:
        std::string fileName;

        std::vector<MError::GisLError> mError;
        std::string mErrorMessage;

        void loadSldFile(const std::string& theSldFilename);


    };

}

#endif //GISL_SLD_H

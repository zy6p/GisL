//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <string>

#include "../utils/merror.h"

namespace GisL {

    /*!
     * Styled Layer Descriptor
     */
    class Sld {
    public:

        class sldDoc {

        };

        class SldAttribute {
        public:
            std::string name;
            std::string value;
            SldAttribute *right = nullptr;
            SldAttribute *left = nullptr;

            SldAttribute(std::string &name, std::string &value) : name(name), value(value) {};
        };

        class SldElement {
        public:
            std::string attribute;
            std::string text;

        private:

        };

        Sld();

        explicit Sld(const std::string &theSldFilename);



    private:
        std::string fileName;

        MError::GisLError mError;
        std::string mErrorMessage;

        void loadSldFile(const std::string &theSldFilename);


    };

}

#endif //GISL_SLD_H

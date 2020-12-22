//
// Created by omega on 14/12/2020.
//

#include "sld.h"

#include <string>
#include <istream>
#include <fstream>

#include "../utils/stringoperate.h"
#include "../utils/merror.h"

namespace GisL {

    Sld::Sld() = default;

    Sld::Sld(const std::string &theSldFilename) {
        loadSldFile(theSldFilename);
    }

    void Sld::loadSldFile(const std::string &theSldFilename) {
        if (theSldFilename.length() <= 4) {
            mError.push_back(MError::GisLError::ErrInFileName);
            mErrorMessage += "empty file name\n";
        }

        if (StringOperate::isEndWith(theSldFilename, ".sld")) {
            mError.push_back(MError::GisLError::ErrInFileName);
            mErrorMessage += "wrong filename\n";
        }



    }






}
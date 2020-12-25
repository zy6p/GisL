//
// Created by omega on 14/12/2020.
//

#include "sld.h"

#include <string>

#include "../utils/stringoperate.h"
#include "../utils/merror.h"

namespace GisL {


    Sld::Sld() : Xml() , GisLObject() {

    }

    Sld::Sld(const std::string &theSldFilename) : Xml(theSldFilename) , GisLObject() {

    }

    void Sld::loadSldFile(const std::string &theSldFilename) {
        Xml::loadXmlFile(theSldFilename);
    }

}
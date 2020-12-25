/*!
 * @file GIsLObject.h
 * @author omega 
 * @date 25/12/2020
 * 
 * @brief super class of all
 * @details 
 *
 *
 */

#ifndef GISL_GISLOBJECT_H
#define GISL_GISLOBJECT_H

#include <string>
#include "merror.h"

namespace GisL {


    class GisLObject {

    protected:
        MError::GisLError mError;
        std::string mErrorMessage;
    public:

        GisLObject();

        bool hasError( );

        std::string errorMessage( );

        ~GisLObject();
    };

}


#endif //GISL_GISLOBJECT_H

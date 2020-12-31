/*!
 * @author tau 
 * @date 12/30/20
*/

#include "command.h"

const std::string &GisL::Command::getMErrorMessage( ) const {
    return mErrorMessage;
}

GisL::Command::~Command( ) {
    mErrorMessage = "";
}

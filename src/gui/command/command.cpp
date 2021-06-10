/*!
 * @author tau 
 * @date 12/30/20
*/

#include "command.h"

const std::string &gisl::Command::getMErrorMessage( ) const {
    return mErrorMessage;
}

gisl::Command::~Command( ) {
    mErrorMessage = "";
}

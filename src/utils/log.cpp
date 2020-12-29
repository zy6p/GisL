/*!
 * @author tau 
 * @date 12/29/20
*/

#include "log.h"

namespace GisL {

    void Log::append( const std::string &s ) {
        mLog.push_back( s );
    }

    void Log::append( const QString &s ) {
        mLog.push_back( s.toStdString());
    }
}
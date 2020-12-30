/*!
 * @author tau 
 * @date 12/29/20
*/

#include "log.h"

namespace GisL {

    Log *Log::_log = nullptr;

    std::vector<std::string> Log::mLog;

    void Log::append( const std::string &s ) {
        Log::mLog.push_back( s );
    }

    Log *Log::log( ) {
        if ( nullptr == Log::_log ) {
            _log = new Log;
        }
        return Log::_log;
    }

}
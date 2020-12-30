/*!
 * @author tau 
 * @date 12/29/20
*/

#include "log.h"

namespace GisL {

    Log *Log::_log = nullptr;

    std::vector<QString> Log::mLog;

    void Log::append( const std::string &s ) {
        Log::mLog.push_back( QObject::tr( s.c_str()));
    }

    Log *Log::log( ) {
        if ( nullptr == Log::_log ) {
            _log = new Log;
        }
        return Log::_log;
    }

    void Log::append( const QString &s ) {
        Log::mLog.push_back( s );
    }

    const QString &Log::getLast( ) {
        return mLog.back();
    }

}
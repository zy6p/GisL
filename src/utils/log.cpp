/*!
 * @author tau
 * @date 12/29/20
 */

#include "log.h"

namespace gisl {

Log* Log::_log = nullptr;

void Log::append(const std::string& s) {
    mLog.push_back(QObject::tr(s.c_str()));
}

Log* Log::log() {
    if (nullptr == Log::_log) {
        _log = new Log;
    }
    return Log::_log;
}

void Log::append(const QString& s) {
    mLog.push_back(s);
}

const QString& Log::getLast() {
    return mLog.back();
}

Log* Log::getLog() {
    return log();
}
std::shared_ptr<Log> Log::getSharedLog() {
    return std::make_shared<Log>(*Log::getLog());
}

} // namespace gisl
/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_LOG_H
#define GISL_LOG_H

#include <string>
#include <vector>
#include <QString>

namespace GisL {
    class Log {
    public:
        void append( const std::string &s );

        void append( const QString &s );

    protected:
        std::vector<std::string> mLog;

    };
}

#endif //GISL_LOG_H

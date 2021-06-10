/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_LOG_H
#define GISL_LOG_H

#include <string>
#include <memory>
#include <vector>
#include <QObject>
#include <QString>

namespace gisl {
    /*!
     * @brief log of gisl, Singleton design patterns
     */
    class Log {
    public:
        void append( const std::string &s );

        void append( const QString &s );

        const QString &getLast( );

        static Log *getLog( );

        static std::shared_ptr<Log> getSharedLog();

        static Log *log( );

    protected:
        Log( ) = default;

        std::vector<QString> mLog;

    private:
        static Log *_log;

    };
}

#endif //GISL_LOG_H

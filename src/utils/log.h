/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_LOG_H
#define GISL_LOG_H

#include <string>
#include <vector>
#include <QObject>
#include <QString>

namespace GisL {
    /*!
     * @brief log of GisL, Singleton design patterns
     */
    class Log {
    public:
        static void append( const std::string &s );

        static void append( const QString &s );

        static const QString &getLast( );

        static Log *log( );

    protected:
        Log( ) = default;

        static std::vector<QString> mLog;

    private:
        static Log *_log;

    };
}

#endif //GISL_LOG_H

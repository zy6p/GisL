/*!
 * @author tau 
 * @date 12/29/20
*/

#ifndef GISL_LOG_H
#define GISL_LOG_H

#include <string>
#include <vector>

namespace GisL {
    /*!
     * @brief log of GisL, Singleton design patterns
     */
    class Log {
    public:
        static void append( const std::string &s );

        static Log *log( );

    protected:
        Log( ) = default;

        static std::vector<std::string> mLog;

    private:
        static Log *_log;

    };
}

#endif //GISL_LOG_H

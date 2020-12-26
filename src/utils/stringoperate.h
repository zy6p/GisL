/*!
 * @author beiyu 
 * @date 2020-12-19
*/

#ifndef GISL_STRINGOPERATE_H
#define GISL_STRINGOPERATE_H

#include <string>

namespace GisL {
    class StringOperate {
    public:

        static int isStrEndWith( const std::string &s, const std::string &end );

        template<typename... StdStrings>
        static bool isEndWith( const std::string &s, const std::string &end, const StdStrings &...ends ) {
            if ( isStrEndWith( s, end )) {
                return true;
            } else {
                return isEndWith( s, ends... );
            }
        }

        static bool isEndWith( const std::string &s ) { return false; };

        static std::wstring s2ws( const std::string &str );

        static std::string ws2s( const std::wstring &wstr );

    };
}


#endif //GISL_STRINGOPERATE_H

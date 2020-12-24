/*!
 * @author beiyu 
 * @date 2020-12-19
*/

#include "stringoperate.h"

#include <string>
#include <codecvt>
#include <locale>
#include <cstring>

namespace GisL {

//    bool StringOperate::isEndWith(const std::string &s, const std::string &end) {
//        int result = s.compare(s.length() - end.length(), end.length(), end);
//        return 0 == result;
//    }

    std::wstring StringOperate::s2ws(const std::string &str) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.from_bytes(str);
    }

    std::string StringOperate::ws2s(const std::wstring &wstr) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.to_bytes(wstr);
    }

//    template<typename... cstrs>
//    int StringOperate::isEndWith( const char *s, const char *end, cstrs *...ends ) {
//        if ( isEndWith(s, end) ) return 1;
//        return isEndWith(s, ends...);
//    }



    int StringOperate::isEndWith( const char *s, const char *end) {
        if ( !s || !end ) return -1;
        size_t lenS = strlen(s);
        size_t lenEnd = strlen( end);
        if (lenEnd > lenS ) return -2;
        if (0 == strncmp( s + lenS - lenEnd, end, lenEnd )) return 1;
//        return isEndWith(s, ends...);
        return 0;
    }

//    void StringOperate::isEndWith( const char *s) { }

//    template<typename... StdStrings>
//    bool StringOperate::isEndWith(const std::string& s, const StdStrings &...ends) {
//        int result = s.compare( s.length() - end.length(), end.length(), end );
//        if (sizeof ...(ends) == 0) {
//            return result == 0;
//        } else {
//            return (0 == result) || isEndWith(s, ends...);
//        }
//        return (bool *)(sizeof ...(ends));
//        return true;
//        const std::string &end,
//        printf("%d", sizeof ...(ends));
//        return sizeof ...(ends);
//        return true;
//    }


//    template<typename StdString>
//    bool StringOperate::isEndWith(const std::string& s, StdString &end) {
//        return isStrEndWith(s, end);
//    }

}
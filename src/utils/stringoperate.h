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

//        template<typename StdString>
//        static bool isEndWith(const std::string &s, StdString &end);

//        template<typename... StdStrings>
//        static bool isEndWith(const std::string& s, const StdStrings &...ends);
//        static bool isEndWith(const std::string& s) {return false;};
//        static bool isEndWith(const std::string& s, const std::string &end) {return false;};

//        template<typename cstr, typename ... cstrs>
//        static int isEndWith( const char *s, const cstr &end, const cstrs &... ends);

        static std::wstring s2ws(const std::string &str);

        static std::string ws2s(const std::wstring &wstr);

//        static bool isEndWith(const std::string &s, const std::string &end);

        static int isEndWith( const char *s, const char *end );

//        template<class ...cstrs>
//        int isEndWith( const char *s, const char *end, cstrs *... ends );
    };
}


#endif //GISL_STRINGOPERATE_H

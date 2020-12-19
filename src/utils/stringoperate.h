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

        static bool isEndWith(const std::string &s, const std::string &end);

        static std::wstring s2ws(const std::string &str);

        static std::string ws2s(const std::wstring &wstr);
    };
}


#endif //GISL_STRINGOPERATE_H

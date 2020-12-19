/*!
 * @author beiyu 
 * @date 2020-12-19
*/

#include "stringoperate.h"

#include <string>
#include <codecvt>
#include <locale>

namespace GisL {

    bool StringOperate::isEndWith(const std::string &s, const std::string &end) {
        int result = s.compare(s.length() - end.length(), end.length(), end);
        return 0 == result;
    }

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

}
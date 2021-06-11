/*!
 * @author beiyu
 * @date 2020-12-19
 */

#include "stringoperate.h"

#include <codecvt>
#include <locale>
#include <string>

namespace gisl {

std::wstring StringOperate::s2ws(const std::string& str) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.from_bytes(str);
}

std::string StringOperate::ws2s(const std::wstring& wstr) {
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes(wstr);
}

int StringOperate::isStrEndWith(const std::string& s, const std::string& end) {
    if (s.empty() || end.empty())
        return -1;
    size_t lenS = s.length();
    size_t lenEnd = end.length();
    if (lenEnd > lenS)
        return -2;
    if (0 == s.compare(lenS - lenEnd, lenEnd, end))
        return 1;
    return 0;
}

//    constexpr std::uint32_t StringOperate::hash_str_to_uint32( const char
//    *data ) {
//        std::uint32_t h( 0 );
//        for ( int i = 0; data && ( '\0' != data[i] ); i++ ) {
//            h = ( h << 6 ) ^ ( h >> 26 ) ^ data[i];
//        }
//        return h;
//    }

} // namespace gisl
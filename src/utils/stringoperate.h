/*!
 * @author beiyu
 * @date 2020-12-19
 */

#ifndef GISL_STRINGOPERATE_H
#define GISL_STRINGOPERATE_H

#include <string>

namespace gisl {
class StringOperate {
public:
    static int isStrEndWith(const std::string& s, const std::string& end);

    template <typename... StdStrings>
    static bool isEndWith(
        const std::string& s,
        const std::string& end,
        const StdStrings&... ends) {
        if (isStrEndWith(s, end)) {
            return true;
        } else {
            return isEndWith(s, ends...);
        }
    }

    static bool isEndWith(const std::string& s) {
        return false;
    };

    static std::wstring s2ws(const std::string& str);

    static std::string ws2s(const std::wstring& wstr);

    //        static constexpr std::uint32_t hash_str_to_uint32( const char *data
    //        );

    typedef std::uint64_t hash_t;

    static constexpr hash_t prime = 0x100000001B3ull;
    static constexpr hash_t basis = 0xCBF29CE484222325ull;

    static hash_t hash_(char const* str) {
        hash_t ret{basis};

        while (*str) {
            ret ^= *str;
            ret *= prime;
            str++;
        }

        return ret;
    }

    static constexpr hash_t
    hash_compile_time(char const* str, hash_t last_value = basis) {
        return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime)
               : last_value;
    }
};

constexpr unsigned long long operator"" _hash(char const* p, size_t) {
    return StringOperate::hash_compile_time(p);
}
} // namespace gisl

#endif // GISL_STRINGOPERATE_H

/*!
 * @author tau 
 * @date 12/23/20
*/

#include "../src/utils/stringoperate.h"
#include <string>

int main() {
    std::string s = "dsadasd.sld";
    std::string d = ".sld";
    std::string c = "ddd";
//    bool a = GisL::StringOperate::isStrEndWith(s, d);
    bool a = GisL::StringOperate::isEndWith(s, d);
//    bool a = GisL::StringOperate::isEndWith(s, ".sld");
    printf("%d", a);
    return 1;
}
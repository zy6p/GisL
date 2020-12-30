/*!
 * @author tau 
 * @date 12/23/20
*/

#include <string>

#include "../src/utils/log.h"
#include "../src/utils/stringoperate.h"
#include "../src/utils/ptroperate.h"

int main( ) {
    auto *p = GisL::Log::log();
    p->append( "yes" );


    std::string s = "dsadasd.sld";
    std::string d = ".sld";
//    std::string c = "ddd";
    bool a = GisL::StringOperate::isEndWith<std::string>( s, "s", "aa", "bb" );
//    bool a = GisL::StringOperate::isEndWith(s.c_str(), ".sld");
////    bool a = GisL::StringOperate::isEndWith(s, ".sld");
    printf( "%d", a );

    return 1;
}
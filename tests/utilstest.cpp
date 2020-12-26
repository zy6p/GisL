/*!
 * @author tau 
 * @date 12/23/20
*/

#include <string>

#include "../src/utils/stringoperate.h"
#include "../src/utils/ptroperate.h"

struct dd {
    int a;
};


int main( ) {
    std::string s = "dsadasd.sld";
    std::string d = ".sld";
//    std::string c = "ddd";
    bool a = GisL::StringOperate::isEndWith<std::string>( s, "s", "aa", "bb" );
//    bool a = GisL::StringOperate::isEndWith(s.c_str(), ".sld");
////    bool a = GisL::StringOperate::isEndWith(s, ".sld");
    printf( "%d", a );

    dd **p;
    int c = 20;
    p = new dd *[c];
    for ( int i = 0; i < c; ++i ) {
        p[i] = new dd;
        p[i]->a = i;
    }
//    GisL::clear<dd>(p, c);

//    GisL::PtrOperate::clear(p, c);
    p = GisL::PtrOperate::raiseSize<dd>( p, c );
    for ( int i = 0; i < 20; ++i ) {
        printf( "%d", p[i]->a );
    }
    return 1;
}
/*!
 * @author tau 
 * @date 12/26/20
*/

#ifndef GISL_PTROPERATE_H
#define GISL_PTROPERATE_H

#include <algorithm>

namespace GisL {
    class PtrOperate {
    public:

        template<typename ptr>
        inline static void clear( ptr *p ) {
            if ( nullptr != p ) {
                delete p;
                p = nullptr;
            }
        }

        template<typename ptr>
        static void clear( ptr **p, int count ) {
            if ( nullptr != p ) {
                for ( int i = count - 1; i >= 0; --i ) {
                    if ( nullptr != p[i] ) {
                        delete p[i];
                        p[i] = nullptr;
                    }
                }
                delete[] p;
                p = nullptr;
            }
        }

        template<typename ptr>
        static ptr **raiseSize( ptr **p, int &count ) {
            int newCount;
            if ( count < 100 ) {
                newCount = count + 100;
            } else {
                newCount = count * 11 / 10;
            }

            ptr **pNew = new ptr *[newCount];
            std::copy( p, p + count, pNew );
            delete[] p;

            count = newCount;
            return pNew;
        }
    };


}

#endif //GISL_PTROPERATE_H

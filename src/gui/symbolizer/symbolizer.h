/*!
 * @author tau 
 * @date 12/28/20
*/

#ifndef GISL_SYMBOLIZER_H
#define GISL_SYMBOLIZER_H

#include <QXmlStreamReader>

namespace GisL {
    class Symbolizer {
    public:
        virtual void init( QXmlStreamReader &sldStream ) = 0;

        virtual void rand( ) = 0;

        virtual ~Symbolizer( ) = 0;

    };
}

#endif //GISL_SYMBOLIZER_H

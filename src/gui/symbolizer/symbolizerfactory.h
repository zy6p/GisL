/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_SYMBOLIZERFACTORY_H
#define GISL_SYMBOLIZERFACTORY_H

#include "abstractsymbolizer.h"
#include "polygonsymbolizer.h"
#include "textsymbolizer.h"

namespace GisL {
    class symbolizerfactory {
    public:

        static PolygonSymbolizer *toPolygonSymbolizer( AbstractSymbolizer &symbolizer );

        static TextSymbolizer *toTextSymbolizer( AbstractSymbolizer &symbolizer );
    };
}

#endif //GISL_SYMBOLIZERFACTORY_H

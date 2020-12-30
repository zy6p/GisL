/*!
 * @author tau 
 * @date 12/30/20
*/

#ifndef GISL_SYMBOLIZERABSTRACTFACTORY_H
#define GISL_SYMBOLIZERABSTRACTFACTORY_H

#include "abstractsymbolizer.h"
#include "polygonsymbolizer.h"
#include "textsymbolizer.h"

namespace GisL {
    class symbolizerabstractfactory {
    public:

        static PolygonSymbolizer *toPolygonSymbolizer( AbstractSymbolizer &symbolizer );

        static TextSymbolizer *toTextSymbolizer( AbstractSymbolizer &symbolizer );
    };
}

#endif //GISL_SYMBOLIZERABSTRACTFACTORY_H

/*!
 * @author tau 
 * @date 12/30/20
*/

#include "symbolizerabstractfactory.h"

GisL::PolygonSymbolizer *GisL::symbolizerabstractfactory::toPolygonSymbolizer( GisL::AbstractSymbolizer &symbolizer ) {
    return dynamic_cast<PolygonSymbolizer *>(&symbolizer);
}

GisL::TextSymbolizer *GisL::symbolizerabstractfactory::toTextSymbolizer( GisL::AbstractSymbolizer &symbolizer ) {
    return dynamic_cast<TextSymbolizer *>(&symbolizer);
}

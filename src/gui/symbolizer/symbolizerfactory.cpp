/*!
 * @author tau 
 * @date 12/30/20
*/

#include "symbolizerfactory.h"

GisL::PolygonSymbolizer *GisL::symbolizerfactory::toPolygonSymbolizer( GisL::AbstractSymbolizer &symbolizer ) {
    return dynamic_cast<PolygonSymbolizer *>(&symbolizer);
}

GisL::TextSymbolizer *GisL::symbolizerfactory::toTextSymbolizer( GisL::AbstractSymbolizer &symbolizer ) {
    return dynamic_cast<TextSymbolizer *>(&symbolizer);
}

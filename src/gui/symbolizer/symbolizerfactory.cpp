/*!
 * @author tau 
 * @date 12/30/20
*/

#include "symbolizerfactory.h"

GisL::PolygonSymbolizer *GisL::SymbolizerFactory::toPolygonSymbolizer( GisL::AbstractSymbolizer &symbolizer ) {
    return dynamic_cast<PolygonSymbolizer *>(&symbolizer);
}

GisL::TextSymbolizer *GisL::SymbolizerFactory::toTextSymbolizer( GisL::AbstractSymbolizer &symbolizer ) {
    return dynamic_cast<TextSymbolizer *>(&symbolizer);
}

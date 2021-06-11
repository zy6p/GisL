/*!
 * @author tau
 * @date 12/30/20
 */

#include "symbolizerfactory.h"

gisl::PolygonSymbolizer* gisl::SymbolizerFactory::toPolygonSymbolizer(
    gisl::AbstractSymbolizer& symbolizer) {
  return dynamic_cast<PolygonSymbolizer*>(&symbolizer);
}

gisl::TextSymbolizer* gisl::SymbolizerFactory::toTextSymbolizer(
    gisl::AbstractSymbolizer& symbolizer) {
  return dynamic_cast<TextSymbolizer*>(&symbolizer);
}

/*!
 * @author tau
 * @date 12/30/20
 */

#ifndef GISL_SYMBOLIZERFACTORY_H
#define GISL_SYMBOLIZERFACTORY_H

#include "abstractsymbolizer.h"
#include "polygonsymbolizer.h"
#include "textsymbolizer.h"

namespace gisl {
class SymbolizerFactory {
  friend PolygonSymbolizer;
  friend TextSymbolizer;

public:
  static PolygonSymbolizer *toPolygonSymbolizer(AbstractSymbolizer &symbolizer);

  static TextSymbolizer *toTextSymbolizer(AbstractSymbolizer &symbolizer);
};
} // namespace gisl

#endif // GISL_SYMBOLIZERFACTORY_H

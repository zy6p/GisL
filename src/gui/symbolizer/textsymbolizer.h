/*!
 * @author tau
 * @date 12/28/20
 */

#ifndef GISL_TEXTSYMBOLIZER_H
#define GISL_TEXTSYMBOLIZER_H

#include <QColor>
#include <string>

#include "abstractsymbolizer.h"

namespace gisl {
class TextSymbolizer : public AbstractSymbolizer {
public:
  // <se:Label>
  std::string propertyName;

  // <se:Font>
  std::string fontFamily;
  int fontSize;

  // <se:LabelPlacement><se:PointPlacement>
  float anchorPointX;
  float anchorPointY;

  // <se:Fill>
  bool fill = true;
  QColor fillColor;

  // <se:VendorOption>
  float maxDisplacement;

  QColor getDefColor(const std::string& s) override;

  float getDefFloat(const std::string& s) override;

  std::string getDefString(const std::string& s) override;

  void rand() override;

  void init(QXmlStreamReader& sldStream) override;

  ~TextSymbolizer() override = default;
};
} // namespace gisl

#endif // GISL_TEXTSYMBOLIZER_H

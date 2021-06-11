/*!
 * @author tau
 * @date 12/28/20
 */

#include "textsymbolizer.h"

#include "../../utils/stringoperate.h"

namespace gisl {
void TextSymbolizer::rand() {
  propertyName = "fid";

  fontFamily = "Times New Roman";
  fontSize = 13;

  anchorPointX = 0;
  anchorPointY = 0;

  fillColor.setNamedColor("#000000");

  maxDisplacement = 1;
}

void TextSymbolizer::init(QXmlStreamReader& sldStream) {
  sldStream.readNextStartElement();
  sldStream.readNextStartElement();
  propertyName = sldStream.readElementText().toStdString();

  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNextStartElement();
  fontFamily = sldStream.readElementText().toStdString();
  sldStream.readNextStartElement();
  fontSize = sldStream.readElementText().toInt();

  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNextStartElement();
  sldStream.readNextStartElement();
  sldStream.readNextStartElement();
  anchorPointX = sldStream.readElementText().toFloat();
  sldStream.readNextStartElement();
  anchorPointY = sldStream.readElementText().toFloat();

  //        GisLObject::mErrorMessage;
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNextStartElement();
  fillColor.setNamedColor(sldStream.readElementText());

  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  maxDisplacement = sldStream.readElementText().toFloat();
}

QColor TextSymbolizer::getDefColor(const std::string& s) {
  switch (StringOperate::hash_(s.c_str())) {
  case "fill"_hash:
    return fillColor;
  default:
    return nullptr;
  }
}

float TextSymbolizer::getDefFloat(const std::string& s) {
  switch (StringOperate::hash_(s.c_str())) {
  case "fontSize"_hash:
    return fontSize;
  case "anchorPointX"_hash:
    return anchorPointX;
  case "anchorPointY"_hash:
    return anchorPointY;
  case "maxDisplacement"_hash:
    return maxDisplacement;
  default:
    return 0;
  }
}

std::string TextSymbolizer::getDefString(const std::string& s) {
  switch (StringOperate::hash_(s.c_str())) {
  case "propertyName"_hash:
    return propertyName;
  case "fontFamily"_hash:
    return fontFamily;
  default:
    return "";
  }
}
} // namespace gisl
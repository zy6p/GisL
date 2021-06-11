/*!
 * @author tau
 * @date 12/28/20
 */

#include <random>

#include "../../utils/stringoperate.h"
#include "polygonsymbolizer.h"

namespace gisl {

void PolygonSymbolizer::rand() {
  std::default_random_engine e((unsigned)time(nullptr));
  std::uniform_int_distribution<> u(0, 255);
  polygonFill = true;
  polygonFillColor = QColor(u(e), u(e), u(e));
  polygonStroke = true;
  polygonStrokeColor = QColor(u(e), u(e), u(e));
  polygonStrokeWidth = 1.0;
  polygonStrokeLinejoin = "bevel";
}

void PolygonSymbolizer::init(QXmlStreamReader& sldStream) {
  sldStream.readNextStartElement();
  polygonFill = true;
  sldStream.readNextStartElement();
  polygonFillColor.setNamedColor(sldStream.readElementText());

  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  sldStream.readNext();
  polygonStroke = true;
  sldStream.readNextStartElement();
  polygonStrokeColor.setNamedColor(sldStream.readElementText());
  sldStream.readNextStartElement();
  polygonStrokeWidth = sldStream.readElementText().toFloat();
  sldStream.readNextStartElement();
  polygonStrokeLinejoin = sldStream.readElementText().toStdString();
}

PolygonSymbolizer::~PolygonSymbolizer() { int i = 0; }

QColor PolygonSymbolizer::getDefColor(const std::string& s) {
  switch (StringOperate::hash_(s.c_str())) {
  case "polygonFillColor"_hash: {
    return polygonFillColor;
  }
  case "polygonStrokeColor"_hash: {
    return polygonStrokeColor;
  }
  default:
    return nullptr;
  }
}

float PolygonSymbolizer::getDefFloat(const std::string& s) {
  switch (StringOperate::hash_(s.c_str())) {
  case "polygonStrokeWidth"_hash:
    return polygonStrokeWidth;
  default:
    return 0;
  }
}

std::string PolygonSymbolizer::getDefString(const std::string& s) {
  switch (StringOperate::hash_(s.c_str())) {
  case "polygonStrokeLinejoin"_hash:
    return polygonStrokeLinejoin;
  default:
    return "";
  }
}

} // namespace gisl

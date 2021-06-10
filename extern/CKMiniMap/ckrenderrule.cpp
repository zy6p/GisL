#include "ckrenderrule.h"
#include "ckpolygonsymbolizer.h"

#include <QDebug>
#include <QTextCodec>

CKRenderRule::CKRenderRule() { pSymbol = 0x00; }

CKRenderRule::CKRenderRule(QXmlStreamReader &sld) {
  QXmlStreamReader::TokenType token;
  while (!sld.atEnd()) {
    token = sld.readNext();
    switch (token) {
    case QXmlStreamReader::StartElement:
      if (sld.name() == "Filter") { //符号配置的对应规则，即选定应用该符号的要素
        while (sld.readNextStartElement()) {
          if (sld.name() == "PropertyIsEqualTo") {
            sld.readNextStartElement();
            field_name = sld.readElementText();
            sld.readNextStartElement();
            field_value = sld.readElementText();
            qDebug() << field_name << "," << field_value << endl;

            //转码测试
            //                        QTextCodec*
            //                        code=QTextCodec::codecForName("gb2312");
            //                        QString rst=code->toUnicode()
            continue;
          }
        }
      }
      if (sld.name() == "PolygonSymbolizer") {
        pSymbol = new CKPolygonSymbolizer(sld);
      }
      break;
    case QXmlStreamReader::EndElement:
      if (sld.name() == "Rule")
        return;
      break;
    default:
      break;
    }
  }
}

CKRenderRule::~CKRenderRule() {
  if (pSymbol != 0x00) {
    delete pSymbol;
    pSymbol = 0x00;
  }
}

CKSymbolizer *CKRenderRule::getPSymbol() const { return pSymbol; }

QString CKRenderRule::getField_name() const { return field_name; }

QString CKRenderRule::getField_value() const { return field_value; }

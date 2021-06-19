/*!
 * @file plottest.cpp
 * @author omega
 * @date 22/12/2020
 *
 * @brief test paint
 * @details
 * @verbatim
 *
 */

#include "gui/sld.h"
#include "gui/symbolizer/polygonsymbolizer.h"
#include "gui/symbolizer/textsymbolizer.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
  std::string sldFilename = "../resource/practise_6/qu-style.sld";
  auto sld = GisL::Sld(sldFilename);
  for (auto p = sld.begin(); p != sld.end(); ++p) {
    auto r = p->second;
    r->rand();
    //        std::cout << dynamic_cast<GisL::TextSymbolizer
    //        *>(sld.end()->second)->fillColor.name().toStdString();
    //        GisL::PolygonSymbolizer *d = dynamic_cast<GisL::PolygonSymbolizer
    //        *>(r); std::cout << p->first << "\t->" <<
    //        d->polygonFillColor.name().toStdString() << "\n";
  }

  return 1;
}

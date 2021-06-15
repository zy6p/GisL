//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <map>
#include <string>

#include "gui/symbolizer/abstractsymbolizer.h"
#include "utils/xml.h"

namespace gisl {
using SymMap = std::map<std::string, AbstractSymbolizer*>;

/*!
 * Styled Layer Descriptor
 */
class Sld : public Xml {

public:
  Sld();

  explicit Sld(const std::string& theSldFilename);

  void loadSldFile(const std::string& theSldFilename);

  AbstractSymbolizer* operator[](const std::string& Literal);

  [[nodiscard]] const SymMap& getSymbolizerMap() const;

  [[nodiscard]] const std::string& getPropertyName() const;

  void rand(int fid);

  ~Sld();

private:
  void readSld(QFile& qFile);

  std::string propertyName;
  SymMap symbolizerMap;
};

} // namespace gisl

#endif // GISL_SLD_H

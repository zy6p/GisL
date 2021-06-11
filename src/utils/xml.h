/*!
 * @file xml.h
 * @author omega
 * @date 23/12/2020
 *
 * @brief xml lib
 * @details
 *
 *
 */

#ifndef GISL_XML_H
#define GISL_XML_H

#include <QFile>
#include <map>
#include <string>

#include "stringoperate.h"

namespace gisl {
/*!
 * @brief xml lib
 */
class Xml {
public:
  typedef std::map<std::string, std::string> StdStringMap;

  class XmlElement {
  public:
    StdStringMap attribute;
    std::string tag;
    std::string text;
    XmlElement* inhere = nullptr;

    XmlElement* next = nullptr;
  };

  class XmlHead {
  public:
    std::string lang = "xml";
    StdStringMap head;

    explicit XmlHead(
        const std::string& version = "1.0",
        const std::string& encoding = "uft-8",
        const std::string& standalone = "");

    ~XmlHead();
  };

  class XmlDoc {
  public:
    XmlHead* pXmlHead;
    XmlElement* pElement;

    XmlDoc();

    ~XmlDoc();
  };

public:
  Xml();

  explicit Xml(const std::string& theXmlFilename);

  void loadXmlFile(const std::string& theXmlFilename);

  ~Xml();

protected:
  std::string mErrorMessage;

private:
  std::string filename;

  XmlDoc* pXmlDoc;

  void readXml(QFile& qFile);
};

} // namespace gisl
#endif // GISL_XML_H

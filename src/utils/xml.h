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

#include <string>

#include "merror.h"
#include "stringoperate.h"

namespace GisL {
    /*!
     * @brief xml lib
     */
    class Xml {
    public:

        class XmlAttribute {
        public:
            std::string name;
            std::string value;
            XmlAttribute *next = nullptr;;

            XmlAttribute( std::string &name, std::string &value );
        };

        class XmlElement {
        public:
            XmlAttribute *pAttribute = nullptr;
            std::string tag;
            std::string text;
            XmlElement *inhere = nullptr;

            XmlElement *next = nullptr;
        };

        class XmlHead {
        public:
            std::string lang = "xml";
            XmlAttribute *head;

            explicit XmlHead( std::string version = "1.0", std::string encoding = "uft-8",
                              std::string standalone = "" );

            ~XmlHead( );
        };

        class XmlDoc {
        public:
            XmlHead *pXmlHead;
            XmlElement *pElement;

            XmlDoc( );

            ~XmlDoc( );
        };


    public:
        Xml( );

        explicit Xml( const std::string &theXmlFilename );

        void loadXmlFile( const std::string &theXmlFilename );

        bool hasError( );

        std::string errorMessage( );

        ~Xml( );


    private:
        std::string filename;

        MError::GisLError mError;
        std::string mErrorMessage;

        XmlDoc *pXmlDoc;


    };

}
#endif //GISL_XML_H

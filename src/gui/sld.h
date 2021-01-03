//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <map>
#include <string>

#include "src/gui/symbolizer/abstractsymbolizer.h"
#include "../utils/gislobject.h"
#include "../utils/xml.h"

namespace GisL {
    typedef std::map<std::string, AbstractSymbolizer *> SymMap;

    /*!
     * Styled Layer Descriptor
     */
    class Sld : public Xml {

    public:
        Sld( );

        explicit Sld( const std::string &theSldFilename );

        void loadSldFile( const std::string &theSldFilename );

        AbstractSymbolizer *operator[]( const std::string &Literal );

//        std::_Rb_tree_iterator<SymbolizerMap> begin( );
//
//        std::_Rb_tree_iterator<SymbolizerMap> end( );
        const SymMap &getSymbolizerMap( ) const;

        const std::string &getPropertyName( ) const;

        void rand( const std::string &layerName );

        ~Sld( );


    private:

        void readSld( QFile &qFile );

        std::string propertyName;
        SymMap symbolizerMap;
    };

}

#endif //GISL_SLD_H

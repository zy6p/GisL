//
// Created by omega on 14/12/2020.
//

#ifndef GISL_SLD_H
#define GISL_SLD_H

#include <map>
#include <string>

#include "symbolizer/symbolizer.h"
#include "../utils/gislobject.h"
#include "../utils/xml.h"

namespace GisL {

    /*!
     * Styled Layer Descriptor
     */
    class Sld : public Xml {

    public:
        Sld( );

        explicit Sld( const std::string &theSldFilename );

        void loadSldFile( const std::string &theSldFilename );

        Symbolizer *operator[]( const std::string &Literal );

        std::_Rb_tree_iterator<std::pair<const std::string, Symbolizer *>> begin( );

        std::_Rb_tree_iterator<std::pair<const std::string, Symbolizer *>> end( );

        ~Sld( );


    private:

        void readSld( QFile &qFile );

        std::string propertyName;
        std::map<std::string, Symbolizer *> symbolizerMap;
    };

}

#endif //GISL_SLD_H

/*!
 * @author tau 
 * @date 12/28/20
*/

#ifndef GISL_ABSTRACTSYMBOLIZER_H
#define GISL_ABSTRACTSYMBOLIZER_H

#include <QXmlStreamReader>
#include <QColor>

namespace gisl {
    class AbstractSymbolizer {

    public:
        virtual void init( QXmlStreamReader &sldStream ) = 0;

        virtual void rand( ) = 0;

        virtual ~AbstractSymbolizer( ) = default;

        virtual QColor getDefColor( const std::string &s ) = 0;

        virtual float getDefFloat( const std::string &s ) = 0;

        virtual std::string getDefString( const std::string &s ) = 0;

        typedef std::pair<const std::string, AbstractSymbolizer *> SymbolizerMap;
    };
}

#endif //GISL_ABSTRACTSYMBOLIZER_H

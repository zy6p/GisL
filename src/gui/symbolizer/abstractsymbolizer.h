/*!
 * @author tau 
 * @date 12/28/20
*/

#ifndef GISL_ABSTRACTSYMBOLIZER_H
#define GISL_ABSTRACTSYMBOLIZER_H

#include <QXmlStreamReader>

#include "../../core/geometry/abstractgeometry.h"

namespace GisL {
    class AbstractSymbolizer {

    public:
        virtual void init( QXmlStreamReader &sldStream ) = 0;

        virtual void rand( ) = 0;

        virtual ~AbstractSymbolizer( ) = default;

        typedef std::pair<const std::string, AbstractSymbolizer *> SymbolizerMap;
    };
}

#endif //GISL_ABSTRACTSYMBOLIZER_H

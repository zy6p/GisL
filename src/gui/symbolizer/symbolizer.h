/*!
 * @author tau 
 * @date 12/28/20
*/

#ifndef GISL_SYMBOLIZER_H
#define GISL_SYMBOLIZER_H

#include <QXmlStreamReader>

#include "../../utils/gislobject.h"

namespace GisL {
    class Symbolizer : public GisLObject {
    public:
        virtual void init( QXmlStreamReader &sldStream ) = 0;

        virtual void rand( ) = 0;

        virtual ~Symbolizer( ) = default;

    };

    typedef std::pair<const std::string, Symbolizer *> SymbolizerMap;
}

#endif //GISL_SYMBOLIZER_H

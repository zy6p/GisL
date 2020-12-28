/*!
 * @author tau 
 * @date 12/28/20
*/

#ifndef GISL_POLYGONSYMBOLIZER_H
#define GISL_POLYGONSYMBOLIZER_H

#include <string>
#include <QColor>

#include "symbolizer.h"

namespace GisL {
    class PolygonSymbolizer : public Symbolizer {
    public:
        bool polygonFill;
        QColor polygonFillColor;

        bool polygonStroke;
        QColor polygonStrokeColor;
        float polygonStrokeWidth;
        std::string polygonStrokeLinejoin;

        void rand( ) override;

        void init( QXmlStreamReader &sldStream ) override;
    };
}

#endif //GISL_POLYGONSYMBOLIZER_H

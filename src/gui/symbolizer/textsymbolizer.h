/*!
 * @author tau 
 * @date 12/28/20
*/

#ifndef GISL_TEXTSYMBOLIZER_H
#define GISL_TEXTSYMBOLIZER_H

#include <string>
#include <QColor>

#include "abstractsymbolizer.h"

namespace GisL {
    class TextSymbolizer : public AbstractSymbolizer {
    public:
        // <se:Label>
        std::string propertyName;

        // <se:Font>
        std::string fontFamily;
        int fontSize;

        // <se:LabelPlacement><se:PointPlacement>
        float anchorPointX;
        float anchorPointY;

        // <se:Fill>
        bool fill = true;
        QColor fillColor;

        // <se:VendorOption>
        float maxDisplacement;

        void rand( ) override;

        void init( QXmlStreamReader &sldStream ) override;

        ~TextSymbolizer( ) override = default;
    };
}

#endif //GISL_TEXTSYMBOLIZER_H

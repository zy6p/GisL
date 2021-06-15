/*!
 * @author tau
 * @date 12/28/20
 */

#ifndef GISL_POLYGONSYMBOLIZER_H
#define GISL_POLYGONSYMBOLIZER_H

#include <QColor>
#include <string>

#include "abstractsymbolizer.h"
#include "core/geometry/geompolygon.h"

namespace gisl {
class PolygonSymbolizer : public AbstractSymbolizer {
public:
    bool polygonFill;
    QColor polygonFillColor;

    bool polygonStroke;
    QColor polygonStrokeColor;
    float polygonStrokeWidth;
    std::string polygonStrokeLinejoin;

    QColor getDefColor(const std::string& s) override;

    float getDefFloat(const std::string& s) override;

    std::string getDefString(const std::string& s) override;

    void rand() override;

    void init(QXmlStreamReader& sldStream) override;

    ~PolygonSymbolizer() override;
};
} // namespace gisl

#endif // GISL_POLYGONSYMBOLIZER_H

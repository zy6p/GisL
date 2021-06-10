#ifndef CKPOLYGONSYMBOLIZER_H
#define CKPOLYGONSYMBOLIZER_H

#include <QXmlStreamReader>
#include <QColor>
#include "cksymbolizer.h"

class CKPolygonSymbolizer : public CKSymbolizer {
public:
    CKPolygonSymbolizer( );

    CKPolygonSymbolizer( QXmlStreamReader &sld );

private:
    QColor fill_color;
    QColor stroke_color;
    float stroke_width;
    QString stroke_join;
};

#endif // CKPOLYGONSYMBOLIZER_H

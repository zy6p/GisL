#ifndef CKPOLYGONSYMBOLIZER_H
#define CKPOLYGONSYMBOLIZER_H

#include <QXmlStreamReader>
#include <QColor>
#include "cksymbolizer.h"

class CKPolygonSymbolizer : public CKSymbolizer {
public:
    CKPolygonSymbolizer( );

    CKPolygonSymbolizer( QXmlStreamReader &sld );

    virtual ~CKPolygonSymbolizer( );

    QColor fill_color;
    QColor stroke_color;
    float stroke_width;
private:
    QString stroke_join;
};

#endif // CKPOLYGONSYMBOLIZER_H

#ifndef RENDER_H
#define RENDER_H

#include <QList>
#include "GeoGeometry.h"
#include "GeoPoint.h"
#include "GeoPolygon.h"
#include "GeoPolyline.h"
#include "Symbol.h"
#include "MarkerSymbol.h"
#include "LineSymbol.h"
#include "FillSymbol.h"

class Render {
public:
    Render();

    ~Render();

    void draw(QList<GeoGeometry *> objs);

    Symbol *setMarkerSymbol(MarkerSymbol *markerSymbol);

    Symbol *setLineSymbol(LineSymbol *lineSymbol);

    Symbol *setFillSymbol(FillSymbol *fillSymbol);

    MarkerSymbol *getMarkerSymbol();

    LineSymbol *getLineSymbol();

    FillSymbol *getFillSymbol();

    void configSelection(QColor color);

    void configSelection(float width);

    void configSelection(QColor color, float width);

    MarkerSymbol *getSelectionMarkerSymbol();

    LineSymbol *getSelectionLineSymbol();

    FillSymbol *getSelectionFillSymbol();

private:
    MarkerSymbol *markerSymbol;  //需要手动指定
    LineSymbol *lineSymbol;
    FillSymbol *fillSymbol;

    QColor selectionColor;
    float selectionWidth;

    MarkerSymbol *selectionMarkerSymbol; //可直接使用默认配置，也可调用configSelection手动指定
    LineSymbol *selectionLineSymbol;
    FillSymbol *selectionFillSymbol;
};

#endif // RENDER_H

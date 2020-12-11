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
    MarkerSymbol *markerSymbol;  //��Ҫ�ֶ�ָ��
    LineSymbol *lineSymbol;
    FillSymbol *fillSymbol;

    QColor selectionColor;
    float selectionWidth;

    MarkerSymbol *selectionMarkerSymbol; //��ֱ��ʹ��Ĭ�����ã�Ҳ�ɵ���configSelection�ֶ�ָ��
    LineSymbol *selectionLineSymbol;
    FillSymbol *selectionFillSymbol;
};

#endif // RENDER_H

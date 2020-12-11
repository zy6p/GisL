#pragma once

#include "qbytearray.h"
#include "qcolor.h"
#include "Symbol.h"

class LineSymbol :
        public Symbol {
public:
    LineSymbol();

    ~LineSymbol();

    LineSymbol(QColor color, float width);

    QColor getColor();

    void setColor(QColor color);

    float getWidth();

    void setWidth(float width);

private:
    QColor color;
    float width;
};


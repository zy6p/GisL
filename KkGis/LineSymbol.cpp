#include "LineSymbol.h"
#include "EnumType.h"


LineSymbol::LineSymbol() {
    this->type = EnumType::LINESYMBOL;
}

LineSymbol::~LineSymbol() {
}

LineSymbol::LineSymbol(QColor color, float width) {
    this->color = color;
    this->width = width;
}

QColor LineSymbol::getColor() {
    return this->color;
}

void LineSymbol::setColor(QColor color) {
    this->color = color;
}

float LineSymbol::getWidth() {
    return this->width;
}

void LineSymbol::setWidth(float width) {
    this->width = width;
}

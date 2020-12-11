#include "MarkerSymbol.h"
#include "qbytearray.h"
#include "EnumType.h"

MarkerSymbol::MarkerSymbol() {
    this->type = EnumType::MARKERSYMBOL;
}


MarkerSymbol::~MarkerSymbol() {
    if (outline) delete outline;
}

MarkerSymbol::MarkerSymbol(QColor color, float size) {
    this->inColor = color;
    this->size = size;
}

MarkerSymbol::MarkerSymbol(QColor color, float size, LineSymbol *outline) {
    this->inColor = color;
    this->size = size;
    this->outline = outline;
}

void MarkerSymbol::setOutline(LineSymbol *outline) {

    this->outline = outline;

}

LineSymbol *MarkerSymbol::getOutline() {
    return this->outline;
}

void MarkerSymbol::setColor(QColor color) {
    this->inColor = color;
}

QColor MarkerSymbol::getColor() {
    return this->inColor;
}

void MarkerSymbol::setSize(float size) {
    this->size = size;
}

float MarkerSymbol::getSize() {
    return this->size;
}

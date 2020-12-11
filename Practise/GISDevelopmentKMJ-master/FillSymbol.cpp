#include "FillSymbol.h"
#include "EnumType.h"


FillSymbol::FillSymbol() {
    type = EnumType::FILLSYMBOL;
}


FillSymbol::~FillSymbol() {
    if (outline) delete outline;
}

FillSymbol::FillSymbol(QColor color, LineSymbol *outline) {
    this->inColor = color;
    this->outline = outline;
}

void FillSymbol::setOutline(LineSymbol *outline) {
    this->outline = outline;
}

LineSymbol *FillSymbol::getOutline() {
    return this->outline;
}

void FillSymbol::setColor(QColor color) {
    this->inColor = color;
}

QColor FillSymbol::getColor() {
    return this->inColor;
}

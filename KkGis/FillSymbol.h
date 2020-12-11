#pragma once
#include "Symbol.h"
#include "LineSymbol.h"
#include "qbytearray.h"
#include "qcolor.h"
class FillSymbol :
	public Symbol
{
public:
	FillSymbol();
	~FillSymbol();
	FillSymbol(QColor color, LineSymbol* outline);
	void setOutline(LineSymbol* outline);
	LineSymbol* getOutline();
	void setColor(QColor color);
	QColor getColor();
private:
	LineSymbol* outline;
	QColor inColor;
};


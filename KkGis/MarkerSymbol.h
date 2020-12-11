#pragma once
#include "Symbol.h"
#include "LineSymbol.h"
#include "qcolor.h"
class MarkerSymbol :
	public Symbol
{
public:
	MarkerSymbol();
	~MarkerSymbol();
	MarkerSymbol(QColor color, float size);
	MarkerSymbol(QColor color, float size, LineSymbol* outline);
	void setOutline(LineSymbol* outline);
	LineSymbol* getOutline();
	void setColor(QColor color);
	QColor getColor();
	void setSize(float size);
	float getSize();
private:
	LineSymbol* outline;
	QColor inColor;
	float size;
};


#include "Render.h"

Render::Render()
{
	//默认被选择要素的配置为，红色表内框，黄色填充
	selectionLineSymbol = new LineSymbol();
	LineSymbol* markerOutlineSymbol = new LineSymbol();
	LineSymbol* fillOutlineSymbol = new LineSymbol();
	selectionMarkerSymbol = new MarkerSymbol();
	selectionFillSymbol = new FillSymbol();
	QColor red;
	QColor yellow;
	red.setNamedColor("red");
	yellow.setNamedColor("yellow");
	selectionLineSymbol->setWidth(1);
	selectionLineSymbol->setColor(yellow);  //线的被选择变为黄色
	markerOutlineSymbol->setWidth(1);
	markerOutlineSymbol->setColor(yellow);  //点的被选择变为黄色
	fillOutlineSymbol->setWidth(1);
	fillOutlineSymbol->setColor(red);   //面的被选择变为黄色填充红色边缘
	selectionMarkerSymbol->setColor(yellow);
	selectionMarkerSymbol->setSize(1);
	selectionMarkerSymbol->setOutline(markerOutlineSymbol);
	selectionFillSymbol->setColor(yellow);
	selectionFillSymbol->setOutline(fillOutlineSymbol);
}

Render::~Render()
{
	if (markerSymbol) delete markerSymbol;
	if (fillSymbol) delete fillSymbol;
	if (lineSymbol) delete lineSymbol;
	if (selectionMarkerSymbol) delete selectionMarkerSymbol;
	if (selectionFillSymbol) delete selectionFillSymbol;
	if (selectionLineSymbol) delete selectionLineSymbol;
}

void Render::draw(QList<GeoGeometry *> objs)
{

}

Symbol* Render::setMarkerSymbol(MarkerSymbol * markerSymbol)
{
	Symbol* old = this->markerSymbol;
	this->markerSymbol = markerSymbol;
	return old;
}

Symbol* Render::setLineSymbol(LineSymbol * lineSymbol)
{
	Symbol* old = this->lineSymbol;
	this->lineSymbol = lineSymbol;
	return old;
}

Symbol* Render::setFillSymbol(FillSymbol * fillSymbol)
{
	Symbol* old = this->fillSymbol;
	this->fillSymbol = fillSymbol;
	return old;
}

MarkerSymbol * Render::getMarkerSymbol()
{
	return markerSymbol;
}

LineSymbol * Render::getLineSymbol()
{
	return lineSymbol;
}

FillSymbol * Render::getFillSymbol()
{
	return fillSymbol;
}

void Render::configSelection(QColor color)
{
	configSelection(color, selectionWidth);
}

void Render::configSelection(float width)
{
	configSelection(selectionColor, width);
}

void Render::configSelection(QColor color, float width)
{
	LineSymbol* markerOutlineSymbol = selectionMarkerSymbol->getOutline();
	LineSymbol* fillOutlineSymbol = selectionFillSymbol->getOutline();
	if (color != selectionColor) {
		this->selectionColor = color;
		selectionLineSymbol->setColor(color);
		markerOutlineSymbol->setColor(color);
		fillOutlineSymbol->setColor(color);
		selectionMarkerSymbol->setColor(color);
		selectionFillSymbol->setColor(color);
	}
	else if (width != selectionWidth) {
		this->selectionWidth = width;
		selectionLineSymbol->setWidth(width);
		selectionMarkerSymbol->setSize(width);
		markerOutlineSymbol->setWidth(width);
		fillOutlineSymbol->setWidth(width);
	}
}

MarkerSymbol * Render::getSelectionMarkerSymbol()
{
	return selectionMarkerSymbol;
}

LineSymbol * Render::getSelectionLineSymbol()
{
	return selectionLineSymbol;
}

FillSymbol * Render::getSelectionFillSymbol()
{
	return selectionFillSymbol;
}

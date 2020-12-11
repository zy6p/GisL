#pragma once
#include "qlist.h"
#include "qcolor.h"
#include "qmath.h"
class StretchRenderer
{
public:
	StretchRenderer();
	StretchRenderer(QList<float> valueDateset, QList<QColor> colors);
	~StretchRenderer();
	int size();
	QColor getColorAt(int i);
	void addColor(QColor color);
	void setColors(QList<QColor> colors);
	void setRange(QList<float> valueDateset);
	void setRange(float max, float min);
	void insertColor(QColor color, int index);
	QList<QColor> getAllColors();
	QColor removeAt(int index);
	QList<QColor> clear();

	QColor cellColor(float value);
private:
	QList<QColor> colors;
	float max;
	float min;
	float dValue;
};


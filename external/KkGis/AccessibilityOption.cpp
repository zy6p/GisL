#include "AccessibilityOption.h"



AccessibilityOption::AccessibilityOption():useSelectedFeatures(false)
{
	this->type = EnumType::ACCESSIBILITY_ANALYSIS;
}


AccessibilityOption::~AccessibilityOption()
{
}

void AccessibilityOption::setOriLayer(GeoLayer * layer)
{
	this->oriPointLayer = layer;
}

GeoLayer * AccessibilityOption::getOriginPointLayer()
{
	return oriPointLayer;
	return oriPointLayer;
}

void AccessibilityOption::setDirPointLayer(GeoLayer * layer)
{
	dirPointLayer = layer;
}

GeoLayer * AccessibilityOption::getDirPointLayer()
{
	return dirPointLayer;
}

void AccessibilityOption::setArcLayer(GeoLayer * layer)
{
	arcLayer = layer;
}

GeoLayer * AccessibilityOption::getArcLayer()
{
	return arcLayer;
}

void AccessibilityOption::setNodeLayer(GeoLayer * layer)
{
	nodeLayer = layer;
}

GeoLayer * AccessibilityOption::getNodeLayer()
{
	return nodeLayer;
}

QString AccessibilityOption::getSaveField()
{
	return saveField;
}

void AccessibilityOption::setSaveField(QString field)
{
	saveField = field;
}

void AccessibilityOption::setTimeLimit(float time)
{
	timeLimit = time;
}

float AccessibilityOption::getTimeLimit()
{
	return timeLimit;
}

bool AccessibilityOption::getUseSelectedFeatures()
{
	return useSelectedFeatures;
}

void AccessibilityOption::setUseSelectedFeatures(bool flag)
{
	useSelectedFeatures = flag;
}

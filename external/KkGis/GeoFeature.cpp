#include "GeoFeature.h"


GeoFeature::GeoFeature(void):geometry(NULL)
{
	attriMap = new QMap<QString, QVariant>;
}


GeoFeature::~GeoFeature(void)
{
	delete geometry;
	delete attriMap;
}

GeoGeometry * GeoFeature::getGeometry()
{
	return geometry;
}

void GeoFeature::setGemetry(GeoGeometry * geometry)
{
	this->geometry = geometry;
}

QMap<QString, QVariant>* GeoFeature::getAttributeMap()
{
	return attriMap;
}

void GeoFeature::setAttributeMap(QMap<QString, QVariant>* map)
{
	this->attriMap = map;
}

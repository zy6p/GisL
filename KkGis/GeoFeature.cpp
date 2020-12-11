#pragma once
#include "GeoGeometry.h"
#include <qmap.h>
#include <qvariant.h>

class GeoFeature
{
public:
	GeoFeature(void);
	~GeoFeature(void);
	GeoGeometry* getGeometry();
	void setGemetry(GeoGeometry* geometry);
	QMap<QString, QVariant>* getAttributeMap();
	void setAttributeMap(QMap<QString, QVariant>* map);
private:
	GeoGeometry* geometry;
	QMap<QString,QVariant>* attriMap;
};


#pragma once
#include <qxml.h>
#include <QXmlStreamReader>
#include <qmessagebox.h>
#include <qstring.h>
#include <qdebug.h>
#include "GeoLayer.h"
class MyXMLReader
{
public:
	MyXMLReader(void);
	virtual ~MyXMLReader(void);

    bool readSLDFile(const QString fileName,CGeoLayer *layer);
	void readNamedLayer(CGeoLayer *layer);
	void readUserStyle(CGeoLayer *layer);
	void readFeatureTypeStyle(CGeoLayer *layer);
	void readRule(CGeoLayer *layer);
	void readPolygonSymbolizer(CGeoLayer *layer);
	void readFill(CGeoLayer *layer);
	void readStroke(CGeoLayer *layer);
	void readName(CGeoLayer *layer);
	void readTitle(CGeoLayer *layer);
	void readAbstract(CGeoLayer *layer);
	void skipUnknownElement();		
	void readCssParameter(CGeoLayer *layer);
private:
	QXmlStreamReader reader;
};


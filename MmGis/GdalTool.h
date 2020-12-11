#pragma once

#include "ogrsf_frmts.h"
#include <gdal_priv.h>
#include <iostream>
#include <fstream>
#include "GeoLayer.h"
#include "GeoMap.h"
#include "gpc.h"
#include "TriangulateUtil.h"
#include "MyXMLReader.h"
#include "GPCUtil.h"
#include "SpatialIndex.h"

class GdalTool {
public:
    GdalTool(void);

    virtual ~GdalTool(void);

    // shpתgeojson
    void getGeoJson(const char *filename);

    // �������Ա�
    void getDBF(const char *filename);

    // ����shp
    CGeoLayer *readShape(const char *filename);

    gpc_vertex BuildVertex(float x, float y);

    CGeoLayer *readShapeWithoutTriangle(const char *filename);
};
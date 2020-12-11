#pragma once

#include <iostream>
#include <fstream>
#include <istreamwrapper.h>
#include <string>
#include "document.h"     // rapidjson's DOM-style API
#include "prettywriter.h" // for stringify JSON
#include <cstdio>
#include "GeoLayer.h"
#include "ogrsf_frmts.h"
#include <gdal_priv.h>
#include "TriangulateUtil.h"
#include "MyXMLReader.h"
#include "GPCUtil.h"
#include "SpatialIndex.h"

using namespace rapidjson;
using namespace std;

class GeoJsonTool {
public:
    GeoJsonTool(void);

    virtual ~GeoJsonTool(void);

    CGeoLayer *readGeoJSON(const char *filename);
};


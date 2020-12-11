#pragma once

#include<iostream>
#include<libpq-fe.h>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "GeoMap.h"

#include "ogrsf_frmts.h"
#include "ogr_feature.h"
#include "ogr_geometry.h"
#include "gdal_priv.h"
#include "GdalTool.h"
#include "MyXMLReader.h"
#include "GPCUtil.h"

class Connect_Sql {
public:
    Connect_Sql(void);

    virtual ~Connect_Sql(void);

    bool ConnectToDB(); // ԭ������
    bool ConnectToDBSaveShpByGdal(const char *filename); // ʹ��gdal����¼��shp����
    CGeoLayer *ConnectToDBGetShpByGdal(QString dbname, QString port, QString host, QString user, QString password,
                                       QString table); // ʹ��gdal���ӵõ�shp����
};


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
class Connect_Sql
{
public:
	Connect_Sql(void);
	virtual ~Connect_Sql(void);
	bool ConnectToDB(); // 原生连接
	bool ConnectToDBSaveShpByGdal(const char* filename); // 使用gdal连接录入shp数据
	CGeoLayer* ConnectToDBGetShpByGdal(QString dbname,QString port,QString host,QString user,QString password,QString table); // 使用gdal连接得到shp数据
};


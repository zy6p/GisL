#pragma once

#include "GeoTool.h"
#include "AccessibilityOption.h"
#include"ogrsf_frmts.h"
#include <qsqldatabase.h>
#include <libpq-fe.h>  //��Ϊpostgresql��include�ļ������������˽ṹ���ȫ�ֺ���

class AccessibilityAnalysisTool :
        public GeoTool {
public:
    AccessibilityAnalysisTool();

    ~AccessibilityAnalysisTool();

    int run_tool();

private:
    QSqlDatabase db;
    QString dijkstraSql;

};


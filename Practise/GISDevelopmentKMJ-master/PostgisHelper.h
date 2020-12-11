#pragma once

#include <qstring.h>
#include"ogrsf_frmts.h"

class PostgisHelper {
public:
    PostgisHelper(QString path);

    ~PostgisHelper();

    GDALDataset *getDataSet();

private:
    GDALDataset *ods;
};


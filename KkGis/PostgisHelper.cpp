#include "PostgisHelper.h"
#include"ogrsf_frmts.h"


PostgisHelper::PostgisHelper(QString path) {
    const char *filePath;
    QByteArray baPath = path.toLatin1();
    filePath = baPath.data();
    ods = (GDALDataset *) GDALOpenEx(filePath, GDAL_OF_VECTOR, NULL, NULL, NULL);
}


PostgisHelper::~PostgisHelper() {

}

GDALDataset *PostgisHelper::getDataSet() {
    return ods;
}

#include "util.h"
#include <QFileDialog>
#include <QWidget>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "GeoPoint.h"
#include "GeoPolygon.h"
#include "GeoPolyline.h"
#include "GeoLayer.h"
#include "EnumType.h"
#include <string>
#include "Practise/GISDevelopmentKMJ-master/cjson/CJsonObject.hpp"
#include <vector>
#include <qdebug.h>
#include <QtXml/qdom.h>
#include <sstream>
#include <qrgb.h>

using namespace std;

util::util() {

}

QString util::openFileDialog(QWidget *widget, QString curPath) {
    QString dlgTitle = "open a file";
    return QFileDialog::getOpenFileName(widget, dlgTitle, curPath);
}


//TODO 点线面测试完成
GeoLayer *util::openGeoJson(QString path) {

    QFile file(path);
    if (!file.exists()) //文件不存在
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QByteArray text = file.readAll();
    QJsonParseError error;
    bool hasInitAttriNames = false;
    QList<QString> nameList;

    //注意，大坑，不能有中文，同时fromJson作为一个file指针， 在不移动指针位置的情况下只能使用一次
    //果然有问题还是得上geogle，一般问题还好，稍微偏门一点的问题就不行了
    QJsonDocument jsonDocu = QJsonDocument::fromJson(QString::fromLocal8Bit(text).toLocal8Bit(), &error);
    //QJsonDocument jsonDocu = QJsonDocument::fromJson(text, &error);
    QJsonObject jsonData = jsonDocu.object();
    QJsonArray featuresJ = jsonData["features"].toArray();

    GeoLayer *layer = new GeoLayer();
    layer->setDataType(EnumType::dataRenderType::GEOMETRYTYPE);
    layer->setRendererType(EnumType::rendererType::SIGNALRGB);
    layer->setSource(EnumType::source::GEOJSON);
    layer->bindDefaultRender();
    layer->setFullPath(path);
    layer->setName(path.mid(path.lastIndexOf("/") + 1, path.lastIndexOf(".") - path.lastIndexOf("/") - 1));
    layer->setIndexMode(EnumType::indexMode::QUADTREE);
    for (int i = 0; i < featuresJ.size(); i++) {
        QJsonObject featureJ = featuresJ.at(i).toObject();
        GeoFeature *feature = new GeoFeature();
        QMap<QString, QVariant> *map = feature->getAttributeMap();
        //TODO 读取属性
        QJsonObject attrsJ = featureJ["properties"].toObject();
        /*QStringList keys = attrsJ.keys();
        for (int i = 0; i < keys.length(); i++) {
            QString key = keys.at(i);
            QString value = attrsJ[key].toString();
            qDebug() << key << ":" << value;
            map->insert(key, QVariant(value));
        }*/ // 这种方法读不出来170，只能读取字符串形式的"170"

        //添加属性名到layer中
        QVariantMap attriMap = attrsJ.toVariantMap();
        QList<QString> keys = attriMap.keys();
        for (int i = 0; i < keys.size(); i++) {
            map->insert(keys.at(i), attriMap[keys.at(i)]);
            if (!hasInitAttriNames) {
                nameList.push_back(keys.at(i));
            }
        }
        layer->setAttributeNames(nameList);
        hasInitAttriNames = true;
        //读取geometry
        QJsonObject geometryJ = featureJ["geometry"].toObject();
        QString type = geometryJ.value("type").toString();
        if (type == "Polygon") {
            layer->setType(EnumType::POLYGON);
            QJsonArray polygonWithHoleJ = geometryJ["coordinates"].toArray(); // [[[x1,y1],[x2,y2]]]
            GeoPolygon *polygon = new GeoPolygon();
            //实际上我现在的只有一个polygon，也就是没有洞和环
            for (int j = 0; j < polygonWithHoleJ.size(); j++) {
                QJsonArray polygonJ = polygonWithHoleJ.at(j).toArray(); // [[x1,y1],[x2,y2]]
                for (int z = 0; z < polygonJ.size(); z++) {  // [x1,y1]
                    QJsonArray pointJ = polygonJ.at(z).toArray();
                    double x = pointJ.at(0).toDouble();
                    double y = pointJ.at(1).toDouble();
                    GeoPoint *point = new GeoPoint();
                    point->setXYf(x, y);
                    polygon->addPoint(point);
                }
            }
            feature->setGemetry(polygon);
            layer->addFeature(feature);
        } else if (type == "LineString") {
            layer->setType(EnumType::POLYLINE);
            QJsonArray polylineJ = geometryJ["coordinates"].toArray(); // [[x1,y1],[x2,y2]]
            GeoPolyline *polyline = new GeoPolyline();
            for (int z = 0; z < polylineJ.size(); z++) {  // [x1,y1]
                QJsonArray pointJ = polylineJ.at(z).toArray();
                double x = pointJ.at(0).toDouble();
                double y = pointJ.at(1).toDouble();
                GeoPoint *point = new GeoPoint();
                point->setXYf(x, y);
                polyline->addPoint(point);
            }
            feature->setGemetry(polyline);
            layer->addFeature(feature);
        } else if (type == "Point") {
            layer->setType(EnumType::POINT);
            QJsonArray pointJ = geometryJ["coordinates"].toArray(); // [x1,y1]
            double x = pointJ.at(0).toDouble();
            double y = pointJ.at(1).toDouble();
            GeoPoint *point = new GeoPoint();
            point->setXYf(x, y);
            feature->setGemetry(point);
            layer->addFeature(feature);
        }
    }
    if (layer->getIndexMode() == EnumType::indexMode::GRIDINDEX) {
        GridIndex *gridIndex = new GridIndex;
        gridIndex->setGrid(layer->getRect(), layer->getAllFeature());
        layer->setIndex(gridIndex);
    } else if (layer->getIndexMode() == EnumType::indexMode::QUADTREE) {
        QuadTree *quadTree = new QuadTree;
        quadTree->CreateQuadTree(layer->getRect(), layer->getAllFeature());
        layer->setIndex(quadTree);
    }
    if (layer->size()) {
        return layer;
    }
    return NULL;
}


GeoLayer *util::openShapeFile(QString path) {
    //将QString转为char*
    std::string str = path.toStdString();
    const char *fileName1 = str.c_str();

    //注册GDAL支持的所有格式
    GDALAllRegister();

    //创建GDAL数据集并读入shp
    GDALDataset *poDS;
    poDS = (GDALDataset *) GDALOpenEx(fileName1, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == nullptr) {
        qDebug() << "open shapefile failed";
        return NULL;
    }

    //创建地图对象并添加图层
    GeoLayer *layer = new GeoLayer;
    layer->setDataType(EnumType::dataRenderType::GEOMETRYTYPE);
    layer->setRendererType(EnumType::rendererType::SIGNALRGB);
    bool hasInitAttriNames = false;
    QRectF layerRect;
    layer->setSource(EnumType::source::SHAPEFILE);
    layer->bindDefaultRender();
    layer->setFullPath(path);
    layer->setName(path.mid(path.lastIndexOf("/") + 1, path.lastIndexOf(".") - path.lastIndexOf("/") - 1));
    layer->setIndexMode(EnumType::indexMode::QUADTREE);
    //创建图层,只有一个shp文件时，数据全部位于第一个图层上
    OGRLayer *poLayer;
    poLayer = poDS->GetLayer(0);
    OGRFeature *poFeature;
    poLayer->ResetReading();

    //遍历所有的要素
    while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
        OGRwkbGeometryType type = poLayer->GetGeomType();
        if (type == OGRwkbGeometryType::wkbPoint)layer->setType(EnumType::POINT);
        else if (type == OGRwkbGeometryType::wkbLineString)layer->setType(EnumType::POLYLINE);
        else if (type == OGRwkbGeometryType::wkbPolygon)layer->setType(EnumType::POLYGON);
        GeoFeature *feature = new GeoFeature;
        layer->addFeature(feature);
        //获取属性信息并打印
        QMap<QString, QVariant> *attriMap = feature->getAttributeMap();
        OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
        int fieldNum = poFDefn->GetFieldCount(); //获得字段的数目，不包括前两个字段（FID,Shape），这两个字段在arcgis里也不能被修改;
        QList<QString> nameList;


        for (int fieldi = 0; fieldi < fieldNum; fieldi++) {
            OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(fieldi);
            QString attriName(poFieldDefn->GetNameRef());
            if (!hasInitAttriNames) nameList.push_back(attriName);
            //根据字段值得类型，选择对应的输出
            if (poFieldDefn->GetType() == OFTInteger) {
                QVariant attriValue(poFeature->GetFieldAsInteger(fieldi));
                attriMap->insert(attriName, attriValue);
            } else if (poFieldDefn->GetType() == OFTReal) {
                QVariant attriValue(poFeature->GetFieldAsDouble(fieldi));
                attriMap->insert(attriName, attriValue);
            } else if (poFieldDefn->GetType() == OFTString) {
                QVariant attriValue(poFeature->GetFieldAsString(fieldi));
                attriMap->insert(attriName, attriValue);
            } else {
                QVariant attriValue(poFeature->GetFieldAsString(fieldi));
                attriMap->insert(attriName, attriValue);
            }
        }
        if (!hasInitAttriNames) {
            layer->setAttributeNames(nameList);
            hasInitAttriNames = true;
        }
        //获取空间位置信息，创建相应的对象并分配存储空间
        OGRGeometry *poGeometry;
        poGeometry = poFeature->GetGeometryRef();
        if (poGeometry != nullptr) {
            //读point
            OGRwkbGeometryType pGeoType = poGeometry->getGeometryType();
            if (pGeoType == wkbPoint) {
                OGRPoint *poPoint = (OGRPoint *) poGeometry;
                double x = poPoint->getX();
                double y = poPoint->getY();
                GeoPoint *point = new GeoPoint;
                feature->setGemetry(point);
                point->setXYf(x, y);
            }
                //读polyline
            else if (pGeoType == wkbLineString) {
                QRectF polylineRect;
                OGRLineString *poLine = (OGRLineString *) poGeometry;
                int pointNum = poLine->getNumPoints();
                if (pointNum == 0)
                    continue;
                GeoPolyline *polyline = new GeoPolyline;
                feature->setGemetry(polyline);
                for (int j = 0; j < pointNum; j++) {
                    double x = poLine->getX(j);
                    double y = poLine->getY(j);
                    GeoPoint *p = new GeoPoint();
                    polyline->addPoint(p);
                    p->setXYf(x, y);
                }
            }
                //读polygon
            else if (pGeoType == wkbPolygon) {
                QRectF polygonRect;
                OGRPolygon *pPolygon = (OGRPolygon *) poGeometry->clone();
                OGRLinearRing *poLR = pPolygon->getExteriorRing();//找出多边形边界
                int pointNum = poLR->getNumPoints();
                if (pointNum == 0)
                    continue;
                GeoPolygon *polygon = new GeoPolygon;
                feature->setGemetry(polygon);
                for (int j = 0; j < pointNum; j++) {
                    double x = poLR->getX(j);
                    double y = poLR->getY(j);
                    GeoPoint *p = new GeoPoint();
                    polygon->addPoint(p);
                    p->setXYf(x, y);
                }
            } else {
                printf("invalid or unsupported geojson type\n");
            }

        }
        OGRFeature::DestroyFeature(poFeature);
    }


    if (layer->getIndexMode() == EnumType::indexMode::GRIDINDEX) {
        GridIndex *gridIndex = new GridIndex;
        gridIndex->setGrid(layer->getRect(), layer->getAllFeature());
        layer->setIndex(gridIndex);
    } else if (layer->getIndexMode() == EnumType::indexMode::QUADTREE) {
        QuadTree *quadTree = new QuadTree;
        quadTree->CreateQuadTree(layer->getRect(), layer->getAllFeature());
        layer->setIndex(quadTree);
    }
    poDS->Release();
    if (layer->size()) {
        return layer;
    }
    return NULL;
}

GeoLayer *util::openFileFromPostgresql(QString path, QString layername) {
    GeoLayer *layer = new GeoLayer;
    layer->setDataType(EnumType::dataRenderType::GEOMETRYTYPE);
    layer->setRendererType(EnumType::rendererType::SIGNALRGB);
    bool hasInitAttriNames = false;
    layer->bindDefaultRender();
    layer->setFullPath(path + "-" + layername);
    layer->setName(layername);
    layer->setSource(EnumType::source::POSTGRESQL);
    layer->setIndexMode(EnumType::indexMode::QUADTREE);
    const char *filePath;
    QByteArray baPath = path.toLatin1();
    filePath = baPath.data();

    const char *pLayerName;
    QByteArray baLayername = layername.toLatin1();
    pLayerName = baLayername.data();

    //  const char *filePath="PG:dbname=Beijing host=localhost port=5432 user=postgres password=gyxdlwwcx";
    //  const char *pLayerName="Beijing";

    //2.读取数据库中数据
    //1.1打开用户指定的database
    GDALDataset *pODS = (GDALDataset *) GDALOpenEx(filePath, GDAL_OF_VECTOR, NULL, NULL, NULL);

    //1.2打开用户指定的layer
    OGRLayer *poLayer = pODS->GetLayerByName(pLayerName);

    //1.3读取数据
    //创建图层,由于用户只指定一个表，所以数据全部位于第一个图层上
    OGRFeature *poFeature;
    poLayer->ResetReading();
    //遍历所有的要素
    while ((poFeature = poLayer->GetNextFeature()) != nullptr) {
        OGRGeometry *poGeometry;
        poGeometry = poFeature->GetGeomFieldRef(0);
        if (poGeometry != nullptr) {
            GeoFeature *feature = new GeoFeature;
            layer->addFeature(feature);
            OGRwkbGeometryType pGeoType;
            if (layer->getType() == -1) {
                pGeoType = poGeometry->getGeometryType();
                if (pGeoType == wkbPoint)layer->setType(EnumType::POINT);
                else if (pGeoType == wkbLineString || pGeoType == wkbMultiLineString)layer->setType(EnumType::POLYLINE);
                else if (pGeoType == wkbPolygon || pGeoType == wkbMultiPolygon)layer->setType(EnumType::POLYGON);
            }

            //获取属性信息并打印
            QMap<QString, QVariant> *attriMap = feature->getAttributeMap();
            OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
            int fieldNum = poFDefn->GetFieldCount(); //获得字段的数目，不包括前两个字段（FID,Shape），这两个字段在arcgis里也不能被修改;
            QList<QString> nameList;
            for (int fieldi = 0; fieldi < fieldNum; fieldi++) {
                OGRFieldDefn *poFieldDefn = poFDefn->GetFieldDefn(fieldi);
                QString attriName(poFieldDefn->GetNameRef());
                if (!hasInitAttriNames) nameList.push_back(attriName);
                //根据字段值得类型，选择对应的输出
                if (poFieldDefn->GetType() == OFTInteger) {
                    QVariant attriValue(poFeature->GetFieldAsInteger(fieldi));
                    attriMap->insert(attriName, attriValue);
                } else if (poFieldDefn->GetType() == OFTReal) {
                    QVariant attriValue(poFeature->GetFieldAsDouble(fieldi));
                    attriMap->insert(attriName, attriValue);
                } else if (poFieldDefn->GetType() == OFTString) {
                    QVariant attriValue(poFeature->GetFieldAsString(fieldi));
                    attriMap->insert(attriName, attriValue);
                } else {
                    QVariant attriValue(poFeature->GetFieldAsString(fieldi));
                    attriMap->insert(attriName, attriValue);
                }
            }
            if (!hasInitAttriNames) {
                layer->setAttributeNames(nameList);
                hasInitAttriNames = true;
            }
            //获取空间位置信息，创建相应的对象并分配存储空间
            //在postgis中，都是multi的要素！！！
            //point
            if (pGeoType == wkbPoint) {
                OGRPoint *poPoint = (OGRPoint *) poGeometry;
                double x = poPoint->getX();
                double y = poPoint->getY();
                qDebug("%.15lf,%.15lf", x, y);

                GeoPoint *point = new GeoPoint;
                feature->setGemetry(point);
                point->setXYf(x, y);
            } else if (pGeoType == wkbLineString) {
                OGRLineString *pPolyline = (OGRLineString *) poGeometry->clone();
                int pointNum = pPolyline->getNumPoints();
                if (pointNum == 0)
                    continue;
                GeoPolyline *polyline = new GeoPolyline;
                feature->setGemetry(polyline);
                for (int j = 0; j < pointNum; j++) {
                    double x = pPolyline->getX(j);
                    double y = pPolyline->getY(j);
                    qDebug("%.15lf,%.15lf", x, y);
                    GeoPoint *p = new GeoPoint;
                    polyline->addPoint(p);
                    p->setXYf(x, y);
                }
            }
                //polygon
            else if (pGeoType == wkbPolygon) {
                OGRPolygon *pPolygon = (OGRPolygon *) poGeometry->clone();
                OGRLinearRing *poLR = pPolygon->getExteriorRing();//找出多边形边界
                int pointNum = poLR->getNumPoints();
                if (pointNum == 0)
                    continue;
                GeoPolygon *polygon = new GeoPolygon;
                feature->setGemetry(polygon);
                for (int j = 0; j < pointNum; j++) {
                    double x = poLR->getX(j);
                    double y = poLR->getY(j);
                    qDebug("%.15lf,%.15lf", x, y);
                    GeoPoint *p = new GeoPoint;
                    polygon->addPoint(p);
                    p->setXYf(x, y);
                }
            } else if (pGeoType == wkbMultiLineString) {
                OGRMultiLineString *pMulPolyline = (OGRMultiLineString *) poGeometry;
                OGRLineString *pPolyline;
                int polylineNum = pMulPolyline->getNumGeometries();
                //如果该multipolyline只由一个多边形组成，则按单一多边形处理
                if (polylineNum == 1) {
                    pPolyline = (OGRLineString *) pMulPolyline->getGeometryRef(0)->clone();
                    int pointNum = pPolyline->getNumPoints();
                    if (pointNum == 0)
                        continue;
                    GeoPolyline *polyline = new GeoPolyline;
                    feature->setGemetry(polyline);
                    for (int j = 0; j < pointNum; j++) {
                        double x = pPolyline->getX(j);
                        double y = pPolyline->getY(j);
                        qDebug("%.15lf,%.15lf", x, y);
                        GeoPoint *p = new GeoPoint;
                        polyline->addPoint(p);
                        p->setXYf(x, y);
                    }
                } else {
                    for (int i = 0; i < polylineNum; i++) {
                        pPolyline = (OGRLineString *) pMulPolyline->getGeometryRef(i);
                    }
                }
            }
                //multipolygon
            else if (pGeoType == wkbMultiPolygon) {
                OGRMultiPolygon *pMulPolygon = (OGRMultiPolygon *) poGeometry;
                OGRPolygon *pPolygon;
                int polygonNum = pMulPolygon->getNumGeometries();
                //如果该multipolygon只由一个多边形组成，则按单一多边形处理
                if (polygonNum == 1) {
                    QRectF polygonRect;
                    pPolygon = (OGRPolygon *) pMulPolygon->getGeometryRef(0)->clone();
                    OGRLinearRing *poLR = pPolygon->getExteriorRing();//找出多边形边界
                    int pointNum = poLR->getNumPoints();
                    if (pointNum == 0)
                        continue;
                    GeoPolygon *polygon = new GeoPolygon;
                    feature->setGemetry(polygon);
                    for (int j = 0; j < pointNum; j++) {
                        double x = poLR->getX(j);
                        double y = poLR->getY(j);
                        qDebug("%.15lf,%.15lf", x, y);
                        GeoPoint *p = new GeoPoint;
                        polygon->addPoint(p);
                        p->setXYf(x, y);
                    }
                } else {
                    for (int i = 0; i < polygonNum; i++) {
                        pPolygon = (OGRPolygon *) pMulPolygon->getGeometryRef(i);
                    }
                }
            } else {
                printf("no point geometry\n");
            }
        } else {
            OGRFeature::DestroyFeature(poFeature);
        }
    }
    if (layer->getIndexMode() == EnumType::indexMode::GRIDINDEX) {
        GridIndex *gridIndex = new GridIndex;
        gridIndex->setGrid(layer->getRect(), layer->getAllFeature());
        layer->setIndex(gridIndex);
    } else if (layer->getIndexMode() == EnumType::indexMode::QUADTREE) {
        QuadTree *quadTree = new QuadTree;
        quadTree->CreateQuadTree(layer->getRect(), layer->getAllFeature());
        layer->setIndex(quadTree);
    }
    pODS->Release();
    if (layer->size()) {
        return layer;
    }
    return NULL;
}

QList<GeoFeature *> util::search(GeoLayer *layer, QString attriName, QString attriValue) {
    QList<GeoFeature *> features = layer->getAllFeature();
    QList<GeoFeature *> featuresFound;//保存找到的要素
    for (int i = 0; i < features.size(); i++)//遍历layer上的所有要素
    {
        GeoFeature *feature = features.at(i);
        QList<QString> keys = feature->getAttributeMap()->keys();
        QList<QVariant> values = feature->getAttributeMap()->values();
        for (int j = 0; j < keys.size(); j++) {
            if (keys.at(j) == attriName)//如果是要查找的属性名
            {
                if (values.at(j).toString().contains(attriValue))//如果输入的属性值是要素属性值的一部分
                {
                    featuresFound.append(feature);
                }
            }
        }
    }
    return featuresFound;
}

GeoFeature *util::identify(GeoPoint *point, GeoLayer *layer, float threshold, Index *spatialIndex) {
    GeoFeature *featureFound;
    if (layer->getIndexMode() == EnumType::GRIDINDEX) {
        featureFound = static_cast<GridIndex *>(spatialIndex)->searchGrid(point, threshold);
    } else if (layer->getIndexMode() == EnumType::QUADTREE) {
        featureFound = static_cast<QuadTree *>(spatialIndex)->SearchQuadTree(point, threshold);
    }
    return featureFound;
}

QList<GeoFeature *> util::globalSearch(GeoMap *map, QString attriValue) {
    QList<GeoFeature *> features;
    for (int i = 0; i < map->size(); i++) {
        GeoLayer *layer = map->getLayerAt(i);
    }
    return features;
}

GeoLayer *util::openGeoJsonByCJson(QString path) {
    QFile file(path);
    if (!file.exists()) //文件不存在
        return false;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;
    QByteArray qtext = file.readAll();
    string text = qtext.toStdString();
    neb::CJsonObject ojson(text);
    GeoLayer *layer = new GeoLayer();
    layer->setFullPath(file.fileName());
    neb::CJsonObject featuresJ = ojson["features"];
    for (int i = 0; i < featuresJ.GetArraySize(); i++) {
        neb::CJsonObject featureJ = featuresJ[i];
        GeoFeature *feature = new GeoFeature();
        QMap<QString, QVariant> *map = feature->getAttributeMap();
        neb::CJsonObject propertiesJ = featureJ["properties"];
        vector<string> keys = propertiesJ.keys();
        //读取属性数据
        for (int i = 0; i < keys.size(); i++) {
            string key = keys.at(i);
            string value;
            propertiesJ.Get(i, value);
            map->insert(QString::fromStdString(key), QVariant(QString::fromStdString(value)));
        }
        //读取空间数据
        neb::CJsonObject geometryJ = featureJ["geometry"];
        string type;
        geometryJ.Get("type", type);
        if (type == "Polygon") {
            layer->setType(EnumType::POLYGON);
            neb::CJsonObject polygonJWithHole = geometryJ["coordinates"];
            neb::CJsonObject polygonJ = polygonJWithHole[0];
            GeoPolygon *polygon = new GeoPolygon();
            for (int i = 0; i < polygonJ.GetArraySize(); i++) {
                double x;
                double y;
                polygonJ[i].Get(0, x);
                polygonJ[i].Get(1, y);
                GeoPoint *point = new GeoPoint();
                point->setXYf(x, y);
                polygon->addPoint(point);
            }
            feature->setGemetry(polygon);
            layer->addFeature(feature);
        } else if (type == "LineString") {
            layer->setType(EnumType::POLYLINE);
            neb::CJsonObject polylineJ = geometryJ["coordinates"];
            GeoPolyline *polyline = new GeoPolyline();
            for (int i = 0; i < polylineJ.GetArraySize(); i++) {
                double x;
                double y;
                polylineJ[i].Get(0, x);
                polylineJ[i].Get(1, y);
                GeoPoint *point = new GeoPoint();
                point->setXYf(x, y);
                polyline->addPoint(point);
            }
            feature->setGemetry(polyline);
            layer->addFeature(feature);
        } else if (type == "Point") {
            layer->setType(EnumType::POINT);
            neb::CJsonObject pointJ = geometryJ["coordinates"];
            double x;
            double y;
            pointJ.Get(0, x);
            pointJ.Get(1, y);
            GeoPoint *point = new GeoPoint();
            point->setXYf(x, y);
            feature->setGemetry(point);
            layer->addFeature(feature);
        }
    }
    if (layer->size()) {
        return layer;
    }
    return nullptr;
}

FillSymbol *util::parseSLD_Fill(QString path) {
    //打开或创建文件
    QFile file(path);
    if (!file.open(QFile::ReadOnly)) {
        return NULL;
    }
    QDomDocument document;
    if (!document.setContent(&file)) {
        file.close();
        return NULL;
    }
    FillSymbol *fillSymbol = new FillSymbol();
    LineSymbol *lineSymbol = new LineSymbol();
    fillSymbol->setOutline(lineSymbol);

    QDomElement root = document.documentElement();
    QDomElement namedLayer = root.firstChildElement("NamedLayer");
    QDomElement userStyle = namedLayer.firstChildElement("UserStyle");
    QDomElement featureTypeStyle = userStyle.firstChildElement("FeatureTypeStyle");
    QDomElement rule = featureTypeStyle.firstChildElement("Rule");
    QDomElement polygonSymbolizer = rule.firstChildElement("PolygonSymbolizer");
    QDomElement fill = polygonSymbolizer.firstChildElement("Fill");
    for (QDomElement cssPara = fill.firstChildElement(
            "CssParameter"); !cssPara.isNull(); cssPara = cssPara.nextSiblingElement("CssParameter")) {
        QString attrName = cssPara.attribute("name");
        if (attrName == "fill") {
            QString fillColor = cssPara.text();
            fillSymbol->setColor(color24BitTo256(fillColor));
        } else if (attrName == "") {

        }
    }
    QDomElement stroke = polygonSymbolizer.firstChildElement("Stroke");
    for (QDomElement cssPara = stroke.firstChildElement(
            "CssParameter"); !cssPara.isNull(); cssPara = cssPara.nextSiblingElement("CssParameter")) {
        QString attrName = cssPara.attribute("name");
        if (attrName == "stroke") {
            QString outlineColor = cssPara.text();
            lineSymbol->setColor(color24BitTo256(outlineColor));
        } else if (attrName == "stroke-width") {
            QString outlineWidth = cssPara.text();
            lineSymbol->setWidth(outlineWidth.toFloat());
        }
    }
    file.close();
    return fillSymbol;
}

QColor util::color24BitTo256(QString color)   // #AAAAAA -> [200,200,200,98]
{
    return parseColor(color);
}

/*vector<unsigned char> util::hexToBin(const string &hex)
{
	std::vector<unsigned char> dest;
	auto len = hex.size();
	dest.reserve(len / 2);
	for (decltype(len) i = 0; i < len; i += 2)
	{
		unsigned int element;
		istringstream strHex(hex.substr(i, 2));
		strHex >> std::hex >> element;
		dest.push_back(static_cast<unsigned char>(element));
	}
	return dest;
}*/

/*QByteArray util::hexToBinInQt(QString hex)
{
	QByteArray binArray;
	std::vector<unsigned char> dest = hexToBin(hex.toStdString());
	for (int i = 0; i < dest.size(); i++) {
		unsigned char cha = dest.at(i);
		binArray.append(cha);
	}
	return binArray;
}*/

QColor util::parseColor(QString hexNamedColor) {
    QColor color;
    color.setNamedColor(hexNamedColor); //默认透明度为65565,但这只是内部储存的数字，实际范围rgba都是[0-255]
    return color;
}

void util::tesselation(GeoPolygon *opolygon, gpc_tristrip *tristrip) {
    int vertexNum = opolygon->size();

    //将QVector中的顶点转移到gpc_vertex数组中
    gpc_vertex *vertices = new gpc_vertex[vertexNum];
    for (int i = 0; i < vertexNum; i++) {
        GeoPoint *point = opolygon->getPointAt(i);
        vertices[i].x = point->getXf();
        vertices[i].y = point->getYf();
    }

    //生成gpc_vertex_list
    gpc_vertex_list vertexList;
    vertexList.num_vertices = vertexNum;//顶点的个数
    vertexList.vertex = vertices;//顶点序列

    //生成gpc_polygon
    gpc_polygon polygon;
    polygon.num_contours = 1;//有一条轮廓
    polygon.hole = nullptr;//没有孔洞
    polygon.contour = &vertexList;

    //获取分解后的三角形
    tristrip->num_strips = 0;
    tristrip->strip = nullptr;//分解后的三角形顶点是连续接壤的<0,1,2><1,2,3><2,3,4>...

    //三角剖分多边形
    gpc_polygon_to_tristrip(&polygon, tristrip);
}


/*QByteArray util::setDefaultAlpha(QByteArray color)
{
	if (color.size() == 3) {
		for (int i = 0; i < 256; i++) {
			QString hex = QString::number(i, 16);
			color.push_back(hexToBinInQt(hex)); //默认透明度为100
		}
	}
	return color;
}*/

GeoLayer *util::grid2FeatureLayer(float **gridData, QRectF mbr, int widthNum, int heightNum,
                                  float cellSize, QString fullPath, QString name, QString cellValueAttriName) {
    if (widthNum > 0 && heightNum > 0 && cellSize > 0) {
        GeoLayer *layer = new GeoLayer;
        //基本属性
        layer->setAttriToStretch(cellValueAttriName);
        layer->setDataType(EnumType::dataRenderType::GRIDTYPE);
        layer->setRendererType(EnumType::rendererType::STRETCHRGB);
        layer->setSource(EnumType::source::GEOTIFF);
        layer->bindDefaultRender();
        layer->setFullPath(fullPath);
        layer->setName(name);
        layer->setIndexMode(EnumType::indexMode::QUADTREE);

        //属性数据与空间数据
        QList<QString> names;
        names.push_back(cellValueAttriName);
        layer->setAttributeNames(names);
        layer->setType(EnumType::POLYGON);
        QList<float> values;
        for (int i = 0; i < heightNum; i++) {
            for (int j = 0; j < widthNum; j++) {
                GeoFeature *feature = new GeoFeature;
                layer->addFeature(feature);
                *(feature->getAttributeMap())->insert(cellValueAttriName, gridData[i][j]);
                qDebug() << "----" << gridData[i][j];
                values.push_back(gridData[i][j]);
                GeoPolygon *cell = new GeoPolygon;
                feature->setGemetry(cell);
                QPointF center(mbr.left() + cellSize / 2 + j * cellSize, mbr.top() - cellSize / 2 - i * cellSize);
                GeoPoint *leftTop = new GeoPoint(center.x() - cellSize / 2, center.y() + cellSize / 2);
                GeoPoint *rightTop = new GeoPoint(center.x() + cellSize / 2, center.y() + cellSize / 2);
                GeoPoint *leftBottom = new GeoPoint(center.x() - cellSize / 2, center.y() - cellSize / 2);
                GeoPoint *rightBottom = new GeoPoint(center.x() + cellSize / 2, center.y() - cellSize / 2);
                cell->addPoint(leftTop);
                cell->addPoint(rightTop);
                cell->addPoint(leftBottom);
                cell->addPoint(rightBottom);
            }
        }
        layer->getStretchRenderer()->setRange(values);
        //索引
        if (layer->getIndexMode() == EnumType::indexMode::GRIDINDEX) {
            GridIndex *gridIndex = new GridIndex;
            gridIndex->setGrid(layer->getRect(), layer->getAllFeature());
            layer->setIndex(gridIndex);
        } else if (layer->getIndexMode() == EnumType::indexMode::QUADTREE) {
            QuadTree *quadTree = new QuadTree;
            quadTree->CreateQuadTree(layer->getRect(), layer->getAllFeature());
            layer->setIndex(quadTree);
        }
        return layer;
    }
    return NULL;
}






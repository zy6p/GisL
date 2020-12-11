#include "GdalTool.h"

using namespace std;

GdalTool::GdalTool(void) {
}


GdalTool::~GdalTool(void) {
}


gpc_vertex GdalTool::BuildVertex(float x, float y) {
    gpc_vertex vertex;
    vertex.x = x;
    vertex.y = y;
    return vertex;
}

/**
*	��shp����ΪGeoJson��ʽ
*/
void GdalTool::getGeoJson(const char *filename) {
    // ע��
    GDALAllRegister();
    // �½����ݼ�����
    GDALDataset *poDS;
    // �������·��
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    // ���������������
    CPLSetConfigOption("SHAPE_ENCODING", "");
    // ��ȡshp�ļ�
    poDS = (GDALDataset *) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == NULL) {
        printf("Open failed.\n");
        exit(1);
    }
    // �½�����
    OGRSFDriverH driver = OGRGetDriverByName("GeoJSON");
    // ����ļ�
    OGR_Dr_CopyDataSource(driver, poDS, "test.geojson", NULL);
    // �ر��ļ�
    GDALClose(poDS);
}

/**
*	�������Ա��ļ�
*/
void GdalTool::getDBF(const char *filename) {
    // ע��
    GDALAllRegister();
    // �½����ݼ�����
    GDALDataset *poDS;
    // �������·��
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    // ���������������
    CPLSetConfigOption("SHAPE_ENCODING", "");
    // ��ȡshp�ļ�
    poDS = (GDALDataset *) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == NULL) {
        printf("Open failed.\n");
        exit(1);
    }
    // �½�txt�ļ�
    ofstream dataFile;
    fstream file("dataFile.txt", ios::out);
    dataFile.open("dataFile.txt", ofstream::app);
    if (dataFile != NULL)
        dataFile.clear();
    dataFile << "{" << endl;

    // �õ�ͼ����
    int layerCount = poDS->GetLayerCount();
    for (int k = 0; k < layerCount; k++) {
        // ͼ�������
        OGRLayer *poLayer;
        poLayer = poDS->GetLayer(k); //��ȡ��
        // Ҫ�����������
        OGRFeatureDefn *poFeaDefn;
        poFeaDefn = poLayer->GetLayerDefn();
        // Ҫ�������
        OGRFeature *poFeature;
        poLayer->ResetReading();
        int i = 0;
        while ((poFeature = poLayer->GetNextFeature()) != NULL) {
            i = i++;
            cout << i << "  ";
            dataFile << i << ":{" << endl;
            int n = poFeaDefn->GetFieldCount(); //����ֶε���Ŀ��������ǰ�����ֶΣ�FID,Shape);
            for (int iField = 0; iField < n; iField++) {
                // �õ�����
                dataFile << poFeaDefn->GetFieldDefn(iField)->GetNameRef() << ":";
                //���ÿ���ֶε�ֵ
                cout << poFeature->GetFieldAsString(iField) << "    ";
                // ��TXT�ĵ���д������
                dataFile << poFeature->GetFieldAsString(iField) << "," << endl;
            }
            dataFile << "}" << endl;
            cout << endl;
            OGRFeature::DestroyFeature(poFeature);
        }
    }
    dataFile << "}" << endl;
    GDALClose(poDS);
    // �ر��ĵ�
    dataFile.close();
}

CGeoLayer *GdalTool::readShape(const char *filename) {
    // ע��
    GDALAllRegister();
    // �������·��
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    // ���������������
    CPLSetConfigOption("SHAPE_ENCODING", "");
    // ��ȡ
    GDALDataset *dataset = (GDALDataset *) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (dataset == NULL) {
        printf("Open failed.\n");
        exit(1);
    }
    // ͼ�������
    OGRLayer *poLayer;
    CGeoLayer *geolayer = new CGeoLayer();
    poLayer = dataset->GetLayer(0); //��ȡ��
    // Ҫ�����������
    OGRFeatureDefn *poFeaDefn;
    poFeaDefn = poLayer->GetLayerDefn();
    geolayer->setLayerName(QString::fromLocal8Bit(poLayer->GetName()));
    OGREnvelope *envelope = new OGREnvelope;
    poLayer->GetExtent(envelope);
    geolayer->setRect(QRectF(QPointF(envelope->MinX, envelope->MaxY), QPointF(envelope->MaxX, envelope->MinY)));
    // Ҫ�������
    OGRFeature *poFeature;
    int n = poFeaDefn->GetFieldCount(); //����ֶε���Ŀ��������ǰ�����ֶΣ�FID,Shape);
    // ȷ���Ǵӿ�ʼ����
    poLayer->ResetReading();
    int i = 0;
    while ((poFeature = poLayer->GetNextFeature()) != NULL) {
        CGeoObject *object;
        OGRGeometry *geo = poFeature->GetGeometryRef();
        if (geo != NULL
            && wkbFlatten(geo->getGeometryType()) == wkbPoint) {
            OGRPoint *poPoint = (OGRPoint *) geo;
            object = new CGeoPoint();
            ((CGeoPoint *) object)->setType(QString("Point"));
            QPointF pt;
            pt.setX(poPoint->getX());
            pt.setY(poPoint->getY());
            ((CGeoPoint *) object)->setPoint(pt);
            ((CGeoPoint *) object)->pts.append(QPointF(pt.x() - 0.001 * pt.x(), pt.y() + 0.001 * pt.y()));
            ((CGeoPoint *) object)->pts.append(QPointF(pt.x() - 0.001 * pt.x(), pt.y() - 0.001 * pt.y()));
            ((CGeoPoint *) object)->pts.append(QPointF(pt.x() + 0.001 * pt.x(), pt.y() - 0.001 * pt.y()));
            ((CGeoPoint *) object)->pts.append(QPointF(pt.x() + 0.001 * pt.x(), pt.y() + 0.001 * pt.y()));
            ((CGeoPoint *) object)->pts.append(QPointF(pt.x() - 0.001 * pt.x(), pt.y() + 0.001 * pt.y()));

            geolayer->type = 0;

        } else if (geo != NULL
                   && wkbFlatten(geo->getGeometryType()) == wkbPolygon) {
            OGRPolygon *polygon = (OGRPolygon *) geo;
            object = new CGeoPolygon();
            ((CGeoPolygon *) object)->setType(QString("Polygon"));
            OGRLinearRing *ring = polygon->getExteriorRing();
            int pointNum = ring->getNumPoints(); // �����
            OGRRawPoint *points = new OGRRawPoint[pointNum];
            ring->getPoints(points);

            for (int i = 0; i < pointNum; i++) {
                QPointF pt;
                pt.setX(points[i].x);
                pt.setY(points[i].y);
                ((CGeoPolygon *) object)->addPoint(pt);
            }
            geolayer->type = 2;

        } else if (geo != NULL
                   && wkbFlatten(geo->getGeometryType()) == wkbLineString) {
            OGRLineString *polyline = (OGRLineString *) geo;
            object = new CGeoPolyline();
            ((CGeoPolyline *) object)->setType(QString("Polyline"));
            int pointNum = polyline->getNumPoints(); // �����

            for (int i = 0; i < pointNum; i++) {
                QPointF pt;
                pt.setX(polyline->getX(i));
                pt.setY(polyline->getY(i));
                ((CGeoPolyline *) object)->addPoint(pt);
            }
            geolayer->type = 1;

        } else {
            QMessageBox::critical(NULL, QString::fromLocal8Bit("��֧�ֵ�����"),
                                  QString::fromLocal8Bit("��Ҫ��ͼ�㲻Ϊ�㡢�ߡ����ʽ���ݲ�֧��!"), QMessageBox::Yes,
                                  QMessageBox::Yes);
            return nullptr;
        }

        QMap<QString, QString> str;
        // ��������
        for (int iField = 0; iField < n; iField++) {
            str.insert(QString::fromLocal8Bit(poFeaDefn->GetFieldDefn(iField)->GetNameRef()),
                       QString::fromLocal8Bit(poFeature->GetFieldAsString(iField)));
        }
        object->setProps(str);

        geolayer->addObjects(object);
        OGRFeature::DestroyFeature(poFeature);

    }
    GDALClose(dataset);
    MyXMLReader xmlReader;
    xmlReader.readSLDFile("G:\\finally\\polygon.xml", geolayer);
    geolayer->setPropsKey();
    makeIndex(geolayer);
    // �����Polygon�������ʷ�
    if (geolayer->type == 2) {
        CGeoLayer *tessaLayer = subvision(geolayer);
        geolayer->tessaLayer = tessaLayer;
    }
    return geolayer;
}


CGeoLayer *GdalTool::readShapeWithoutTriangle(const char *filename) {
    // ע��
    GDALAllRegister();
    // �������·��
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");
    // ���������������
    CPLSetConfigOption("SHAPE_ENCODING", "");
    // ��ȡ
    GDALDataset *dataset = (GDALDataset *) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (dataset == NULL) {
        printf("Open failed.\n");
        exit(1);
    }
    // ͼ�������
    OGRLayer *poLayer;
    CGeoLayer *geolayer = new CGeoLayer();
    poLayer = dataset->GetLayer(0); //��ȡ��
    // Ҫ�����������
    OGRFeatureDefn *poFeaDefn;
    poFeaDefn = poLayer->GetLayerDefn();
    geolayer->setLayerName(QString::fromLocal8Bit(poLayer->GetName()));
    OGREnvelope *envelope = new OGREnvelope;
    poLayer->GetExtent(envelope);
    geolayer->setRect(QRectF(QPointF(envelope->MinX, envelope->MaxY), QPointF(envelope->MaxX, envelope->MinY)));
    // Ҫ�������
    OGRFeature *poFeature;
    int n = poFeaDefn->GetFieldCount(); //����ֶε���Ŀ��������ǰ�����ֶΣ�FID,Shape);
    // ȷ���Ǵӿ�ʼ����
    poLayer->ResetReading();
    int i = 0;
    while ((poFeature = poLayer->GetNextFeature()) != NULL) {
        CGeoObject *object;
        OGRGeometry *geo = poFeature->GetGeometryRef();
        if (geo != NULL
            && wkbFlatten(geo->getGeometryType()) == wkbPoint) {
            OGRPoint *poPoint = (OGRPoint *) geo;
            object = new CGeoPoint();
            ((CGeoPoint *) object)->setType(QString("Point"));
            QPointF pt;
            pt.setX(poPoint->getX());
            pt.setY(poPoint->getY());
            ((CGeoPoint *) object)->setPoint(pt);
            geolayer->type = 0;

        } else if (geo != NULL
                   && wkbFlatten(geo->getGeometryType()) == wkbPolygon) {
            OGRPolygon *polygon = (OGRPolygon *) geo;
            OGRPoint *point = new OGRPoint();
            object = new CGeoPolygon();
            ((CGeoPolygon *) object)->setType(QString("Polygon"));
            ((CGeoPolygon *) object)->centriod.setX(point->getX());
            ((CGeoPolygon *) object)->centriod.setY(point->getY());
            OGRLinearRing *ring = polygon->getExteriorRing();
            ring->Centroid(point);
            int pointNum = ring->getNumPoints(); // �����
            OGRRawPoint *points = new OGRRawPoint[pointNum];
            ring->getPoints(points);
            for (int i = 0; i < pointNum; i++) {
                QPointF pt;
                pt.setX(points[i].x);
                pt.setY(points[i].y);
                ((CGeoPolygon *) object)->addPoint(pt);
            }
            geolayer->type = 2;

        } else if (geo != NULL
                   && wkbFlatten(geo->getGeometryType()) == wkbLineString) {
            OGRLineString *polyline = (OGRLineString *) geo;
            object = new CGeoPolyline();
            ((CGeoPolyline *) object)->setType(QString("Polyline"));

            int pointNum = polyline->getNumPoints(); // �����
            for (int i = 0; i < pointNum; i++) {
                QPointF pt;
                pt.setX(polyline->getX(i));
                pt.setY(polyline->getY(i));
                ((CGeoPolyline *) object)->addPoint(pt);
            }
            geolayer->type = 1;

        } else {
            QMessageBox::critical(NULL, QString::fromLocal8Bit("��֧�ֵ�����"),
                                  QString::fromLocal8Bit("��Ҫ��ͼ�㲻Ϊ�㡢�ߡ����ʽ���ݲ�֧��!"), QMessageBox::Yes,
                                  QMessageBox::Yes);
            return nullptr;
        }

        QMap<QString, QString> str;
        // ��������
        for (int iField = 0; iField < n; iField++) {
            str.insert(QString::fromLocal8Bit(poFeaDefn->GetFieldDefn(iField)->GetNameRef()),
                       QString::fromLocal8Bit(poFeature->GetFieldAsString(iField)));
        }
        object->setProps(str);
        // ���÷�Χ
        OGREnvelope *envelope2 = new OGREnvelope;
        geo->getEnvelope(envelope2);
        object->setRect(QRectF(QPointF(envelope2->MinX, envelope2->MaxY), QPointF(envelope2->MaxX, envelope2->MinY)));
        geolayer->addObjects(object);
        OGRFeature::DestroyFeature(poFeature);

    }
    GDALClose(dataset);
    geolayer->setPropsKey();
    return geolayer;
}


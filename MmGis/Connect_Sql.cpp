#include "Connect_Sql.h"

using namespace std;


Connect_Sql::Connect_Sql(void) {
}


Connect_Sql::~Connect_Sql(void) {
}

// ʹ��libpq����
bool Connect_Sql::ConnectToDB() {
    int lib_ver = PQlibVersion();
    printf("Version of libpq: %d\n", lib_ver);
    PGconn *conn = PQconnectdb("host=127.0.0.1 dbname=test user=postgres password=husen");//����Ӧ���ݸ�����������޸�
    if (PQstatus(conn) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",
                PQerrorMessage(conn));
        PQfinish(conn);
        return 0;
    }
    int ver = PQserverVersion(conn);
    printf("Server version: %d\n", ver);
    PQfinish(conn);
    return 0;
}

// �������ݿ�洢shp���ݣ������Ļ�һ��shp�ļ���Ӧһ�ű�
bool Connect_Sql::ConnectToDBSaveShpByGdal(const char *filename) {
    GdalTool gdalTool;

    CGeoLayer *layer = gdalTool.readShapeWithoutTriangle(filename);
    if (layer == nullptr) {
        return false;
    }
    // ע������
    OGRRegisterAll();
    // ���ݿ����Ӳ���
    const char *filepath = "PG:dbname=test host=127.0.0.1 user=postgres password=husen";
    const char *driver = "PostgreSQL";
    std::string str = layer->getLayerName().toStdString();
    const char *table = str.c_str();
    OGRSFDriver *pDriver = NULL;
    OGRLayer *player = NULL;
    OGRDataSource *pDS = NULL;
    pDS = (OGRDataSource *) GDALOpenEx(filepath, GDAL_OF_VECTOR, NULL, NULL, NULL);
    /*
    pDriver = (OGRSFDriver*)OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(driver);
    if ( pDriver == NULL ) {
    return false;
    }
    pDS = pDriver->Open(filepath,0);
    */
    if (NULL == pDS) {
        return false;
    }
    // �������ݱ�
    //pDS->DeleteLayer(0);
    player = pDS->CreateLayer(table, NULL, wkbPolygon, NULL);
    if (NULL == player) {
        return false;
    }
    // ������map����Զ����ֶ�
    QList<QString> propsKey = layer->getPropsKey();
    OGRFieldDefn *pfielddefn;
    for (int i = 0; i < propsKey.size(); i++) {
        //����һ���ֶ�one_way
        std::string str = propsKey.at(i).toStdString();
        pfielddefn = new OGRFieldDefn(str.c_str(), OFTString);
        //�����ݱ��д���������ֶ�
        player->CreateField(pfielddefn);
        delete pfielddefn;
    }
    OGRFieldDefn *pfielddefn2 = new OGRFieldDefn("type", OFTString);
    //�����ݱ��д���������ֶ�
    player->CreateField(pfielddefn2);
    delete pfielddefn2;
    for (int i = 0; i < layer->geoObjects.size(); i++) {
        CGeoObject *obj = layer->geoObjects[i];
        std::string str2 = obj->getType().toStdString();
        if (strcmp(str2.c_str(), "Point") == 0) {
            OGRPoint *point = new OGRPoint();
            point->setX(((CGeoPoint *) obj)->getPoint().x());
            point->setY(((CGeoPoint *) obj)->getPoint().y());
            OGRGeometry *pgeo = (OGRGeometry *) point;
            pgeo->setCoordinateDimension(2);//��������ϵά��
            OGRFeature *pfeature = OGRFeature::CreateFeature(player->GetLayerDefn());
            pfeature->SetField("type", "Point");

            QMap<QString, QString> props = ((CGeoPoint *) obj)->getProps();
            QMapIterator<QString, QString> i(props);
            while (i.hasNext()) {
                i.next();
                std::string str = i.key().toStdString();
                std::string str2 = i.value().toStdString();
                pfeature->SetField(str.c_str(), str2.c_str());
            }

            if (OGRERR_NONE != pfeature->SetGeometry(pgeo)) {
                return false;
            }
            //����¼д�����ݱ�
            if (OGRERR_NONE != player->CreateFeature(pfeature)) {
                return false;
            }
            //delete point;
            OGRFeature::DestroyFeature(pfeature);
        } else if (strcmp(str2.c_str(), "Polygon") == 0) {
            OGRPolygon *polygon = new OGRPolygon();
            OGRLinearRing *ring = new OGRLinearRing();
            int num = ((CGeoPolygon *) obj)->pts.size();
            for (int i = 0; i < num; i++) {
                ring->addPoint(((CGeoPolygon *) obj)->pts[i].x(), ((CGeoPolygon *) obj)->pts[i].y());
            }
            polygon->addRing(ring);
            OGRGeometry *pgeo = (OGRGeometry *) polygon;
            pgeo->setCoordinateDimension(2);//��������ϵά��
            OGRFeature *pfeature = OGRFeature::CreateFeature(player->GetLayerDefn());
            pfeature->SetField("type", "Polygon");
            QMap<QString, QString> props = ((CGeoPolygon *) obj)->getProps();
            QMapIterator<QString, QString> i(props);
            while (i.hasNext()) {
                i.next();
                std::string str = i.key().toStdString();
                std::string str2 = i.value().toStdString();
                pfeature->SetField(str.c_str(), str2.c_str());
            }
            if (OGRERR_NONE != pfeature->SetGeometry(pgeo)) {
                return false;
            }
            //����¼д�����ݱ�
            if (OGRERR_NONE != player->CreateFeature(pfeature)) {
                return false;
            }
            //delete polygon;
            OGRFeature::DestroyFeature(pfeature);

        } else if (strcmp(str2.c_str(), "Polyline") == 0) {
            OGRLineString *polyline = new OGRLineString();
            int num = ((CGeoPolyline *) obj)->pts.size();
            for (int i = 0; i < num; i++) {
                polyline->addPoint(((CGeoPolyline *) obj)->pts[i].x(), ((CGeoPolyline *) obj)->pts[i].y());
            }
            OGRGeometry *pgeo = (OGRGeometry *) polyline;
            pgeo->setCoordinateDimension(2);//��������ϵά��
            OGRFeature *pfeature = OGRFeature::CreateFeature(player->GetLayerDefn());
            pfeature->SetField("type", "Polyline");
            QMap<QString, QString> props = ((CGeoPolyline *) obj)->getProps();
            QMapIterator<QString, QString> i(props);
            while (i.hasNext()) {
                i.next();
                std::string str = i.key().toStdString();
                std::string str2 = i.value().toStdString();
                pfeature->SetField(str.c_str(), str2.c_str());
            }
            if (OGRERR_NONE != pfeature->SetGeometry(pgeo)) {
                return false;
            }
            //����¼д�����ݱ�
            if (OGRERR_NONE != player->CreateFeature(pfeature)) {
                return false;
            }
            //delete polyline;
            OGRFeature::DestroyFeature(pfeature);
        } else {
            QMessageBox::critical(NULL, QString::fromLocal8Bit("��֧�ֵ�����"),
                                  QString::fromLocal8Bit("��Ҫ��ͼ�㲻Ϊ�㡢�ߡ����ʽ���ݲ�֧��!"), QMessageBox::Yes,
                                  QMessageBox::Yes);
            return false;
        }
    }
    OGRDataSource::DestroyDataSource(pDS);
    return true;
}

// ʹ��gdal���ӵõ�shp����
CGeoLayer *
Connect_Sql::ConnectToDBGetShpByGdal(QString dbname, QString port, QString host, QString user, QString password,
                                     QString table) {
    // ���ݿ����Ӳ���
    OGRRegisterAll();
    QString filepath =
            "PG:dbname=" + dbname + " port=" + port + " host=" + host + " user=" + user + " password=" + password;
    OGRDataSource *pDS = NULL;
    std::string s = table.toStdString();
    const char *tab = s.c_str();
    OGRLayer *player = NULL;
    std::string s2 = filepath.toStdString();
    const char *filep = s2.c_str();
    pDS = (OGRDataSource *) GDALOpenEx(filep, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (NULL == pDS) {
        return false;
    }
    // �õ�table��
    player = pDS->GetLayerByName(tab);
    if (NULL == player) {
        return false;
    }

    // ͼ�������
    CGeoLayer *geolayer = new CGeoLayer();
    // Ҫ�����������
    OGRFeatureDefn *poFeaDefn;
    poFeaDefn = player->GetLayerDefn();
    geolayer->setLayerName(player->GetName());
    OGREnvelope *envelope = new OGREnvelope;
    player->GetExtent(envelope);
    geolayer->setRect(QRectF(QPointF(envelope->MinX, envelope->MaxY), QPointF(envelope->MaxX, envelope->MinY)));
    // Ҫ�������
    OGRFeature *poFeature;
    int n = poFeaDefn->GetFieldCount(); //����ֶε���Ŀ��������ǰ�����ֶΣ�FID,Shape);
    // ȷ���Ǵӿ�ʼ����
    player->ResetReading();
    int i = 0;
    while ((poFeature = player->GetNextFeature()) != NULL) {
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
            str.insert(poFeaDefn->GetFieldDefn(iField)->GetNameRef(), poFeature->GetFieldAsString(iField));
        }
        object->setProps(str);
        if (object->getType().compare("Point") != 0) {
            // ���÷�Χ
            OGREnvelope *envelope2 = new OGREnvelope;
            geo->getEnvelope(envelope2);
            object->setRect(
                    QRectF(QPointF(envelope2->MinX, envelope2->MaxY), QPointF(envelope2->MaxX, envelope2->MinY)));
            object->centriod = object->getRect().center();
        }

        geolayer->addObjects(object);
        OGRFeature::DestroyFeature(poFeature);

    }
    GDALClose(pDS);
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

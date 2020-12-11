��#include "CGeoKernalDensTool.h"

CGeoKernalDensTool::CGeoKernalDensTool() {
    GDALAllRegister();//ע����������
    OGRRegisterAll();
    CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//֧������·��
}

CGeoKernalDensTool::~CGeoKernalDensTool() {
}

int CGeoKernalDensTool::run_tool() {
    if (layer->getType() == EnumType::POLYGON)
        return 3;//�����������ʹ���

    if (layer->getType() == EnumType::POINT)//���ܶȷ���
    {
        //�����û������������в���
        QList<GeoPoint *> points = getGeoPoints(layer);
        QRectF layerRect = layer->getRect();
        if (points.size() == 0)//�����������Ч
            return 2;

        if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
            COption *option = (COption *) this->option;
            QString output_file = option->output_file;
            float output_cell_size = getCellSize(layerRect);
            cellSize = output_cell_size;

            QList<float> populations = getPopulations(points, layer);
            if (populations.size() == 0)//�ֶβ�����Ҫ��
                return 1;

            float search_radius = getSearchRadius(points, populations, layerRect);
            int area_unit = option->area_unit;
            int method = option->method_type;
            int outputvalue = option->output_value_type;

            //���з���
            if (outputvalue == 0)//д�����ܶ�
            {
                QList<float> KDResult = KernelDensity(points, populations, output_cell_size,
                                                      search_radius, area_unit, method, layerRect);//�õ����
                QList<uchar> resultDensity = MinMaxNormalization(KDResult, 255);//��һ��
                saveResultDense(output_file, resultDensity, layerRect, output_cell_size);//д�����
            } else if (outputvalue == 1)//д������
            {
                QList<int> KDResult = KernelCount(points, populations, output_cell_size,
                                                  search_radius, area_unit, method, layerRect);//�õ����
                QList<uchar> resultCount = MinMaxNormalization(KDResult, 255);//��һ��
                saveResultCount(output_file, resultCount, layerRect, output_cell_size);//д�����
            }
        }


    } else if (layer->getType() == EnumType::POLYLINE) {
        //�����û������������в���
        QList<GeoPolyline *> polylines = getGeoPolyline(layer);
        QRectF layerRect = layer->getRect();
        if (polylines.size() == 0)//�����������Ч
            return 2;

        if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
            COption *option = (COption *) this->option;
            QString output_file = option->output_file;
            float output_cell_size = getCellSize(layerRect);
            cellSize = output_cell_size;
            QList<float> populations = getPopulations(polylines, layer);
            if (populations.size() == 0)//�ֶβ�����Ҫ��
                return 1;

            QList<GeoPoint *> points = getPolylineMeanCenters(polylines);//�õ�����polyline��meanCenter
            float search_radius = getSearchRadius(points, populations, layerRect);
            int area_unit = option->area_unit;
            int method = option->method_type;
            int outputvalue = option->output_value_type;

            //���з���
            if (outputvalue == 0)//д�����ܶ�
            {
                QList<float> KDResult = KernelDensity_line(polylines, populations, output_cell_size,
                                                           search_radius, area_unit, method, layerRect);//�õ����
                QList<uchar> resultDensity = MinMaxNormalization(KDResult, 255);//��һ��
                saveResultDense(output_file, resultDensity, layerRect, output_cell_size);//д�����
            } else if (outputvalue == 1)//д������
            {
                QList<int> KDResult = KernelCount_line(polylines, populations, output_cell_size,
                                                       search_radius, area_unit, method, layerRect);//�õ����
                QList<uchar> resultCount = MinMaxNormalization(KDResult, 255);//��һ��
                saveResultCount(output_file, resultCount, layerRect, output_cell_size);//д�����
            }
        }

    }

    return 0;
}

QList<GeoPoint *> CGeoKernalDensTool::getGeoPoints(GeoLayer *layer) {
    QList<GeoPoint *> points;
    if (layer->getType() == EnumType::POINT)//��ĺ��ܶȼ���
    {
        QList<GeoFeature *> features = layer->getAllFeature();
        int featureNum = features.size();
        for (int i = 0; i < featureNum; i++) {
            points.append(static_cast<GeoPoint *>(features.at(i)->getGeometry()));
        }
    }
    return points;
}

QList<GeoPolyline *> CGeoKernalDensTool::getGeoPolyline(GeoLayer *layer) {
    QList<GeoPolyline *> polylines;
    if (layer->getType() == EnumType::POLYLINE)//��ĺ��ܶȼ���
    {
        QList<GeoFeature *> features = layer->getAllFeature();
        int featureNum = features.size();
        for (int i = 0; i < featureNum; i++) {
            polylines.append(static_cast<GeoPolyline *>(features.at(i)->getGeometry()));
        }
    }
    return polylines;
}

QList<float> CGeoKernalDensTool::getPopulations(QList<GeoPoint *> points, GeoLayer *layer) {
    QList<float> populations, populations_unNormd;
    //����û�δָ��population�ֶΣ���populationȫ����ֵΪ1
    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        QString field = option->population_field;
        if (option->population_field.isNull() || option->population_field == QString("NONE")) {
            for (int i = 0; i < points.size(); i++)
                populations.append(1.0f);
        } else {
            QList<QString> attris = layer->getAttributeNames();
            int attriNum = attris.size();
            for (int j = 0; j < points.size(); j++)//��������Ҫ��
            {
                QVariant var = layer->getFeatureAt(j)->getAttributeMap()->value(option->population_field);
                if (var.toFloat() > MINFLOAT)
                    populations_unNormd.append(var.toFloat());
            }
            populations = MinMaxNormalization_pop(populations_unNormd, 1.0f);//��pop�ֶι�һ��
        }
        return populations;
    }


}

QList<float> CGeoKernalDensTool::getPopulations(QList<GeoPolyline *> polylines, GeoLayer *layer) {
    QList<float> populations, populations_unNormd;
    //����û�δָ��population�ֶΣ���populationȫ����ֵΪ1

    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        QString field = option->population_field;
        if (option->population_field.isNull() || option->population_field == QString("NONE")) {
            for (int i = 0; i < polylines.size(); i++)
                populations.append(1.0f);
        } else {
            QList<QString> attris = layer->getAttributeNames();
            int attriNum = attris.size();
            for (int j = 0; j < polylines.size(); j++)//��������Ҫ��
            {
                QVariant var = layer->getFeatureAt(j)->getAttributeMap()->value(option->population_field);
                if (var.toFloat() > MINFLOAT)
                    populations_unNormd.append(var.toFloat());
            }
            populations = MinMaxNormalization_pop(populations_unNormd, 1.0f);//��pop�ֶι�һ��
        }
    }

    return populations;
}

QList<GeoPoint *> CGeoKernalDensTool::getPolylineMeanCenters(QList<GeoPolyline *> polylines) {
    QList<GeoPoint *> meanCenters;
    int polylineNum = polylines.size();
    for (int i = 0; i < polylineNum; i++)
        meanCenters.append(polylines.at(i)->getMeanCenter());
    return meanCenters;
}

float CGeoKernalDensTool::getSearchRadius(QList<GeoPoint *> points, QList<float> populations, QRectF layerRect) {
    float searchRadius;
    //����û�δָ���κ����ݣ������Ĭ�ϴ���
    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        if (option->search_radius < MINFLOAT) {
            float SD = 0, Dm = 0, n = 0;
            float Xsd = 0, Ysd = 0, Xmean = 0, Ymean = 0;
            float pointNum = points.size();
            //����ƽ�����ģ���Ȩ��
            for (int i = 0; i < pointNum; i++) {
                Xmean = Xmean + (points.at(i)->getXf()) * populations.at(i);
                Ymean = Ymean + (points.at(i)->getYf()) * populations.at(i);
            }
            Xmean = Xmean / pointNum;
            Ymean = Ymean / pointNum;
            QPointF centerPoint = QPointF(Xmean, Ymean);//��Ȩƽ������

            QList<float> disToCenter;//�������е㣨��Ȩ����ƽ�����ĵľ���
            for (int i = 0; i < pointNum; i++) {
                disToCenter.append(getDis(*points.at(i), centerPoint) * populations.at(i));//�˴���Ҫ��Ҫ��Ȩ��
                n = n + populations.at(i);//n�ǵ�����ûȨ����population�ֶε��ܺͣ���Ȩ��
                Xsd = Xsd + pow(points.at(i)->getXf() - Xmean, 2);
                Ysd = Ysd + pow(points.at(i)->getYf() - Ymean, 2);
            }
            Dm = getMedian(disToCenter);//������Щ�������ֵ
            SD = pow(Xsd * (1 / pointNum) + Ysd * (1 / pointNum), 0.5);
            float Dm1 = pow(1 / log(2), 0.5) * Dm;
            float minD = SD;
            if (minD > Dm1)
                minD = Dm1;
            searchRadius = 0.9 * minD * pow(n, -0.2);
        }
            //����û�ָ�����ݣ���ֱ�ӷ���
        else
            searchRadius = option->search_radius;
    }

    return searchRadius;
}

float CGeoKernalDensTool::getCellSize(QRectF layerRect) {
    float cellSize;
    //����û�δָ���κ����ݣ�����Ԫ��С��ͨ��ʹ�÷�Χ�Ŀ�Ȼ�߶��еĽ�Сֵ����250������
    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        if (option->output_cell_size < MINFLOAT) {
            float min = abs(layerRect.height());
            if (min > abs(layerRect.width()))
                min = abs(layerRect.width());
            cellSize = min / 100;
        }
            //����û�ָ�����ݣ���ֱ�ӷ���
        else
            cellSize = option->output_cell_size;
    }

    return cellSize;
}

float CGeoKernalDensTool::getDis(GeoPoint pt1, QPointF pt2) {
    float dis;
    float R = 6378137;
    //���method_typeΪ0��ʹ��ƽ�����
    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        if (option->method_type == 0) {
            float dx = pt1.getXf() - pt2.x();
            float dy = pt1.getYf() - pt2.y();
            dis = pow(dx * dx + dy * dy, 0.5);
        }
            //���method_typeΪ1��ʹ�ô���߾���
        else if (option->method_type == 1) {
            float dB = (pt1.getYf() - pt2.x()) * PI / 180;
            float dL = (pt1.getXf() - pt2.y()) * PI / 180;
            float a = sinf(dL / 2) * sinf(dB / 2) +
                      cosf(pt1.getXf() * PI / 180) * cosf(pt2.x() * PI / 180) * sinf(dL / 2) * sinf(dL / 2);
            float c = 2 * atan2f(pow(a, 0.5), pow((1 - a), 0.5));
            dis = R * c;
        }
    }

    return dis;
}

QList<float> CGeoKernalDensTool::KernelDensity(QList<GeoPoint *> points, QList<float> populations,
                                               float cell_size, float search_radius, int area_unit, int method,
                                               QRectF layerRect) {
    //����cellsize�õ�������������ȡ����
    nYSize = abs(layerRect.height()) / cell_size;
    nXSize = abs(layerRect.width()) / cell_size;

    float *KDResult_final = new float[nXSize * nYSize];

    //�������ݴ洢�ռ�,��Ϊÿһ��դ�񸳳�ֵ0
    KDResult = new float *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        KDResult[y] = new float[nXSize];
        for (int x = 0; x < nXSize; x++)
            KDResult[y][x] = MINFLOAT;
    }
    //����ÿһդ�����ĵ��Ӧ��x���� y�������
    float **LocX = new float *[nYSize];
    float **LocY = new float *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        LocY[y] = new float[nXSize];
        LocX[y] = new float[nXSize];
        for (int x = 0; x < nXSize; x++) {
            LocX[y][x] = layerRect.left() + (0.5 + x) * cell_size;
            LocY[y][x] = layerRect.top() - (0.5 + y) * cell_size;
        }
    }

    //����ÿһ��դ�����ֵ,point��˳����population��˳��һ��
    QList<float> KDResult_forOutPut;
    int pointNum = points.size();
    for (int y = 0; y < nYSize; y++) {
        for (int x = 0; x < nXSize; x++) {
            QPointF gridPoint(LocX[y][x], LocY[y][x]);
            QList<float> pops;
            QList<float> dists;
            float pop, dist;
            for (int i = 0; i < pointNum; i++)//����ÿһ��Ҫ�ص㣬���������뾶��Χ�ڣ������
            {
                dist = getDis(*points.at(i), gridPoint);
                pop = populations.at(i);
                if (dist < search_radius) {
                    pops.append(pop);
                    dists.append(dist);
                }
            }
            if (pops.size() > 0) {
                KDResult[y][x] = getDensity(search_radius, pops, dists);
                KDResult_forOutPut.append(getDensity(search_radius, pops, dists));
            } else {
                KDResult[y][x] = 0.0f;
                KDResult_forOutPut.append(0.0f);
            }
        }
    }

    return KDResult_forOutPut;
}

QList<float>
CGeoKernalDensTool::KernelDensity_line(QList<GeoPolyline *> polylines, QList<float> populations, float cell_size,
                                       float search_radius, int area_unit, int method, QRectF layerRect) {
    //����cellsize�õ�������������ȡ����
    nYSize = abs(layerRect.height()) / cell_size;
    nXSize = abs(layerRect.width()) / cell_size;

    float *KDResult_final = new float[nXSize * nYSize];

    //�������ݴ洢�ռ�,��Ϊÿһ��դ�񸳳�ֵ0
    KDResult = new float *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        KDResult[y] = new float[nXSize];
        for (int x = 0; x < nXSize; x++)
            KDResult[y][x] = MINFLOAT;
    }
    //����ÿһդ�����ĵ��Ӧ��x���� y�������
    float **LocX = new float *[nYSize];
    float **LocY = new float *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        LocY[y] = new float[nXSize];
        LocX[y] = new float[nXSize];
        for (int x = 0; x < nXSize; x++) {
            LocX[y][x] = layerRect.left() + (0.5 + x) * cell_size;
            LocY[y][x] = layerRect.top() - (0.5 + y) * cell_size;
        }
    }

    //����ÿһ��դ�����ֵ,point��˳����population��˳��һ��
    QList<float> KDResult_forOutPut;
    int polylineNum = polylines.size();
    for (int y = 0; y < nYSize; y++) {
        for (int x = 0; x < nXSize; x++) {
            //QPointF gridPoint(LocX[y][x], LocY[y][x]);
            GeoPoint *pt = new GeoPoint();
            pt->setXf(LocX[y][x]), pt->setYf(LocY[y][x]);
            QList<float> pops;
            QList<float> dists;
            float pop, dist;
            for (int i = 0; i < polylineNum; i++)//����ÿһ��Ҫ���ߣ����������뾶��Χ�ڣ������
            {
                dist = polylines.at(i)->disToPoint(pt);
                pop = populations.at(i);
                if (dist < search_radius) {
                    pops.append(pop);
                    dists.append(dist);
                }
            }
            if (pops.size() > 0) {
                KDResult[y][x] = getDensity(search_radius, pops, dists);
                KDResult_forOutPut.append(getDensity(search_radius, pops, dists));
            } else {
                KDResult[y][x] = 0.0f;
                KDResult_forOutPut.append(0.0f);
            }
        }
    }

    return KDResult_forOutPut;
}

QList<int> CGeoKernalDensTool::KernelCount(QList<GeoPoint *> points, QList<float> populations,
                                           float cell_size, float search_radius, int area_unit, int method,
                                           QRectF layerRect) {
    //����cellsize�õ�������������ȡ����
    nYSize = abs(layerRect.height()) / cell_size;
    nXSize = abs(layerRect.width()) / cell_size;

    int *KDResult_final = new int[nXSize * nYSize];
    //�������ݴ洢�ռ�,��Ϊÿһ��դ�񸳳�ֵ0
    int **KDResult = new int *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        KDResult[y] = new int[nXSize];
        for (int x = 0; x < nXSize; x++)
            KDResult[y][x] = MINFLOAT;
    }
    //����ÿһդ�����ĵ��Ӧ��x���� y�������
    float **LocX = new float *[nYSize];
    float **LocY = new float *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        LocY[y] = new float[nXSize];
        LocX[y] = new float[nXSize];
        for (int x = 0; x < nXSize; x++) {
            LocX[y][x] = layerRect.left() + (0.5 + x) * cell_size;
            LocY[y][x] = layerRect.top() - (0.5 + y) * cell_size;
        }
    }
    QList<int> KDResut_forOutput;
    int pointNum = points.size();
    for (int y = 0; y < nYSize; y++) {
        for (int x = 0; x < nXSize; x++) {
            int count = 0;
            QPointF gridPoint(LocX[y][x], LocY[y][x]);
            float dist;
            for (int i = 0; i < pointNum; i++)//����ÿһ��Ҫ�ص㣬���������뾶��Χ�ڣ������
            {
                dist = getDis(*points.at(i), gridPoint);
                if (dist < search_radius)
                    count++;
            }
            KDResult[y][x] = count;
            KDResut_forOutput.append(count);
        }
    }
    return KDResut_forOutput;
}

QList<int>
CGeoKernalDensTool::KernelCount_line(QList<GeoPolyline *> polylines, QList<float> populations, float cell_size,
                                     float search_radius, int area_unit, int method, QRectF layerRect) {
    //����cellsize�õ�������������ȡ����
    nYSize = abs(layerRect.height()) / cell_size;
    nXSize = abs(layerRect.width()) / cell_size;

    int *KDResult_final = new int[nXSize * nYSize];
    //�������ݴ洢�ռ�,��Ϊÿһ��դ�񸳳�ֵ0
    int **KDResult = new int *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        KDResult[y] = new int[nXSize];
        for (int x = 0; x < nXSize; x++)
            KDResult[y][x] = MINFLOAT;
    }
    //����ÿһդ�����ĵ��Ӧ��x���� y�������
    float **LocX = new float *[nYSize];
    float **LocY = new float *[nYSize];
    for (int y = 0; y < nYSize; y++) {
        LocY[y] = new float[nXSize];
        LocX[y] = new float[nXSize];
        for (int x = 0; x < nXSize; x++) {
            LocX[y][x] = layerRect.left() + (0.5 + x) * cell_size;
            LocY[y][x] = layerRect.top() - (0.5 + y) * cell_size;
        }
    }
    QList<int> KDResut_forOutput;
    int polylineNum = polylines.size();
    for (int y = 0; y < nYSize; y++) {
        for (int x = 0; x < nXSize; x++) {
            int count = 0;
            GeoPoint *pt = new GeoPoint();
            pt->setXf(LocX[y][x]), pt->setYf(LocY[y][x]);
            //QPointF gridPoint(LocX[y][x], LocY[y][x]);
            float dist;
            for (int i = 0; i < polylineNum; i++)//����ÿһ��Ҫ�ص㣬���������뾶��Χ�ڣ������
            {
                dist = polylines.at(i)->disToPoint(pt);
                if (dist < search_radius)
                    count++;
            }
            KDResult[y][x] = count;
            KDResut_forOutput.append(count);
        }
    }
    return KDResut_forOutput;
}

float CGeoKernalDensTool::getDensity(float search_radius, QList<float> pops, QList<float> dists) {
    //һ����n��Ҫ�ص���������դ��������뾶��
    //popsΪ�ڰ뾶��Ҫ�ص���ֶ�ֵ��distsΪ����դ�����뾶��Ҫ�ص�ľ���
    int n = pops.size();
    float density = 0;
    float dens = 0;
    if (n != 0) {
        for (int i = 0; i < n; i++) {
            dens = dens + (3 / PI) * pops.at(i) * pow((1 - pow((dists.at(i) / search_radius), 2)), 2);
        }
        density = (1 / pow(search_radius, 2)) * dens;
    }
    return density;
}

void CGeoKernalDensTool::saveResultDense(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size) {
    ////�������������ͼ����Ϣ
    //QByteArray ba = output_file.toLocal8Bit();
    //const char *outfilePath = ba.data();
    //int nYSize = abs(layerRect.height()) / cell_size;
    //int nXSize = abs(layerRect.width()) / cell_size;
    //int nBands = 1;
    //char **ppszOptions = NULL;
    //char **raster_creation_options = NULL;

    ////����դ�����ݼ������������ʲô��������GDAL���Զ�д��0����ֵ
    //GDALDataset *dataset;
    ////GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");//ͼ������
    //GDALDriver *driver;
    //dataset = driver->Create(outfilePath, nXSize, nYSize, nBands, GDT_Float32, raster_creation_options);

    ////д��դ��������Ϣ
    //dataset->RasterIO(GF_Write, 0, 0, nXSize, nYSize, KDResult, nXSize, nYSize, GDT_Float32, 1, NULL, 0, 0, 0);

    ////�رմ򿪵��ļ�
    //GDALClose(dataset);

    int resultLength = result.size();
    uchar *KDResult = new uchar[resultLength];

    //����8λ�Ҷ�ͼ
    for (int i = 0; i < resultLength; i++)
        KDResult[i] = result.at(i);
    int bytePerLine = nXSize * 1;
    QImage denseResult(KDResult, nXSize, nYSize, bytePerLine, QImage::Format_Grayscale8, nullptr, nullptr);
    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        if (option->output_file.contains(QString("jpg")))
            denseResult.save(output_file, "JPG", 100);
        else if (option->output_file.contains(QString(".png")))
            denseResult.save(output_file, "PNG", 100);
        else if (option->output_file.contains(QString(".bmp")))
            denseResult.save(output_file, "BMP", 100);
    }

}

void CGeoKernalDensTool::saveResultCount(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size) {
    ////�������������ͼ����Ϣ
    //QByteArray ba = output_file.toLocal8Bit();
    //const char *outfilePath = ba.data();
    //int nYSize = abs(layerRect.height()) / cell_size;
    //int nXSize = abs(layerRect.width()) / cell_size;
    //int nBands = 1;
    //char **ppszOptions = NULL;
    //char **raster_creation_options = NULL;

    ////����դ�����ݼ������������ʲô��������GDAL���Զ�д��0����ֵ
    //GDALDataset *dataset;
    //GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");//ͼ������
    ////GDALDriver *driver;
    //dataset = driver->Create(outfilePath, nXSize, nYSize, nBands, GDT_Int32 , raster_creation_options);

    ////д��դ��������Ϣ
    //dataset->RasterIO(GF_Write, 0, 0, nXSize, nYSize, KDResult, nXSize, nYSize, GDT_Int32, 1, NULL, 0, 0, 0);

    ////�رմ򿪵��ļ�
    //GDALClose(dataset);

    //int resultLength = result.size();
    //uchar *KDResult = new uchar[resultLength];
    //for (int i = 0; i < resultLength; i++)
    //	KDResult[i] = result.at(i);

    int resultLength = result.size();
    uchar *KCResult = new uchar[resultLength];

    //����8λ�Ҷ�ͼ
    for (int i = 0; i < resultLength; i++)
        KCResult[i] = result.at(i);
    int bytePerLine = nXSize * 1;
    QImage denseResult(KCResult, nXSize, nYSize, bytePerLine, QImage::Format_Grayscale8, nullptr, nullptr);
    if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
        COption *option = (COption *) this->option;
        if (option->output_file.contains(QString("jpg")))
            denseResult.save(output_file, "JPG", 100);
        else if (option->output_file.contains(QString(".png")))
            denseResult.save(output_file, "PNG", 100);
        else if (option->output_file.contains(QString(".bmp")))
            denseResult.save(output_file, "BMP", 100);
    }

}

void CGeoKernalDensTool::setLayer(GeoLayer *layer1) {
    layer = layer1;
}

GeoLayer *CGeoKernalDensTool::getLayer() {
    return layer;
}

float CGeoKernalDensTool::getMedian(QList<float> nums) {
    float median;
    float temp;
    int size = nums.size();
    //ð������
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (nums.at(j) > nums.at(j + 1))
                nums.swapItemsAt(j, j + 1);
        }
    }
    //Ѱ����ֵ
    if (size % 2 == 0)
        median = 0.5 * (nums.at(size * 0.5) + nums.at(size * 0.5 - 1));
    else
        median = nums.at(floor(size * 0.5));
    return median;
}

QList<uchar> CGeoKernalDensTool::MinMaxNormalization(QList<float> data, int scale) {
    int length = data.size();
    QList<uchar> results;
    //�ҵ����ֵ����Сֵ
    float min, max;
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            min = data.at(i);
            max = data.at(i);
        }
        if (min > data.at(i))
            min = data.at(i);
        if (max < data.at(i))
            max = data.at(i);
    }
    //��һ����0-255֮��
    for (int i = 0; i < length; i++) {
        results.append(floor(((data[i] - min) / (max - min)) * scale));
    }
    return results;
}

QList<uchar> CGeoKernalDensTool::MinMaxNormalization(QList<int> data, int scale) {
    QList<uchar> results;
    int length = data.size();
    //�ҵ����ֵ����Сֵ
    float min, max;
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            min = data.at(i);
            max = data.at(i);
        }
        if (min > data.at(i))
            min = data.at(i);
        if (max < data.at(i))
            max = data.at(i);
    }
    //��һ����0-255֮��
    for (int i = 0; i < length; i++) {
        results.append(floor(((float(data[i]) - min) / (max - min)) * scale));
    }
    return results;
}

QList<float> CGeoKernalDensTool::MinMaxNormalization_pop(QList<float> data, float scale) {
    QList<float> results;
    int length = data.size();
    //�ҵ����ֵ����Сֵ
    float min, max;
    for (int i = 0; i < length; i++) {
        if (i == 0) {
            min = data.at(i);
            max = data.at(i);
        }
        if (min > data.at(i))
            min = data.at(i);
        if (max < data.at(i))
            max = data.at(i);
    }
    //��һ����0-255֮��
    for (int i = 0; i < length; i++) {
        results.append(((data[i] - min) / (max - min)) * scale);
    }
    return results;
}

int CGeoKernalDensTool::getWidthCellNum() {
    return nXSize;
}

int CGeoKernalDensTool::getHeightCellNum() {
    return nYSize;
}

float **CGeoKernalDensTool::getKDResult() {
    return KDResult;
}

float CGeoKernalDensTool::getCellSize() {
    return cellSize;
}

QString CGeoKernalDensTool::getFullPath() {
    return ((COption * )
    this->option)->output_file;
}


  
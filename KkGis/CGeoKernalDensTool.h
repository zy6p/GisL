#pragma once

#include"GeoTool.h"
#include"GeoFeature.h"
#include"ogrsf_frmts.h"
#include"ogr_spatialref.h"
#include"GeoPoint.h"
#include"GeoLayer.h"
#include"qmessagebox.h"
#include"EnumType.h"

#define PI 3.1415926
#define MINFLOAT 0.000000001

class CGeoKernalDensTool : public GeoTool {
public:
    CGeoKernalDensTool();

    ~CGeoKernalDensTool();

    //���з���,���еĺ�����˳���Ƕ�׵��ã�д��������
    int run_tool();

    //��layer�еõ���Ҫ��
    QList<GeoPoint *> getGeoPoints(GeoLayer *layer);

    //1ȷ��population�ֶ�
    QList<float> getPopulations(QList<GeoPoint *> points, GeoLayer *layer);

    //2ȷ��Ĭ�ϴ���
    float getSearchRadius(QList<GeoPoint *> points, QList<float> populations, QRectF layerRect);

    //3ȷ��Ĭ����Ԫ��С
    float getCellSize(QRectF layerRect);

    //4����ѡ��ľ��뷽ʽȷ������
    float getDis(GeoPoint pt1, QPointF pt2);


    QList<GeoPolyline *> getGeoPolyline(GeoLayer *layer);

    QList<float> getPopulations(QList<GeoPolyline *> polylines, GeoLayer *layer);

    QList<GeoPoint *> getPolylineMeanCenters(QList<GeoPolyline *> polylines);
    //5out_value��ѡ���ں��ܶȷ�������������

    //���ܶȷ�������
    QList<float> KernelDensity(QList<GeoPoint *> points, QList<float> populations,
                               float output_cell_size, float search_radius, int area_unit, int method,
                               QRectF layerRect);

    QList<float> KernelDensity_line(QList<GeoPolyline *> polylines, QList<float> populations,
                                    float output_cell_size, float search_radius, int area_unit, int method,
                                    QRectF layerRect);

    //�ۼƵ�
    QList<int> CGeoKernalDensTool::KernelCount(QList<GeoPoint *> points, QList<float> populations,
                                               float cell_size, float search_radius, int area_unit, int method,
                                               QRectF layerRect);

    QList<int> CGeoKernalDensTool::KernelCount_line(QList<GeoPolyline *> polylines, QList<float> populations,
                                                    float cell_size, float search_radius, int area_unit, int method,
                                                    QRectF layerRect);

    //�ܶȼ���
    float getDensity(float search_radius, QList<float> populations, QList<float> dists);

    //д�����
    void saveResultDense(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size);

    void saveResultCount(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size);

    //��ȡͼ����Ϣ
    void setLayer(GeoLayer *layer1);

    GeoLayer *getLayer();

    //����һ��������ֵ
    float getMedian(QList<float> nums);

    //���ݱ�׼��
    QList<uchar> MinMaxNormalization(QList<float> data, int scale);

    QList<uchar> MinMaxNormalization(QList<int> data, int scale);

    QList<float> MinMaxNormalization_pop(QList<float> data, float scale);


    int getWidthCellNum();

    int getHeightCellNum();

    float **getKDResult();

    float getCellSize();

    QString getFullPath();

private:
    GeoLayer *layer;
    int nXSize;
    int nYSize;
    float **KDResult;
    float cellSize;

};


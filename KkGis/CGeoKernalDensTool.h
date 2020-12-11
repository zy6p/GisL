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

class CGeoKernalDensTool:public GeoTool
{
public:
	CGeoKernalDensTool();
	~CGeoKernalDensTool();
	//进行分析,所有的函数按顺序或嵌套调用，写在这里面
    int run_tool();

	//从layer中得到点要素
	QList<GeoPoint*> getGeoPoints(GeoLayer *layer);
	//1确定population字段
	QList<float> getPopulations(QList<GeoPoint*> points, GeoLayer *layer);
	//2确定默认带宽
	float getSearchRadius(QList<GeoPoint*> points, QList<float> populations, QRectF layerRect);
	//3确定默认象元大小
	float getCellSize(QRectF layerRect);
	//4根据选择的距离方式确定距离
	float getDis(GeoPoint pt1, QPointF pt2);


	QList<GeoPolyline*> getGeoPolyline(GeoLayer *layer);
	QList<float> getPopulations(QList<GeoPolyline*> polylines, GeoLayer *layer);
	QList<GeoPoint*> getPolylineMeanCenters(QList<GeoPolyline*>polylines);
	//5out_value的选择在核密度分析函数中体现

	//核密度分析函数
	QList<float> KernelDensity(QList<GeoPoint*> points, QList<float> populations,
		float output_cell_size, float search_radius, int area_unit, int method, QRectF layerRect);
	QList<float> KernelDensity_line(QList<GeoPolyline*> polylines, QList<float> populations,
		float output_cell_size, float search_radius, int area_unit, int method, QRectF layerRect);
	//累计点
	QList<int> CGeoKernalDensTool::KernelCount(QList<GeoPoint*> points, QList<float> populations,
		float cell_size, float search_radius, int area_unit, int method, QRectF layerRect);
	QList<int> CGeoKernalDensTool::KernelCount_line(QList<GeoPolyline*> polylines, QList<float> populations,
		float cell_size, float search_radius, int area_unit, int method, QRectF layerRect);
	//密度计算
	float getDensity(float search_radius, QList<float> populations, QList<float> dists);
	//写出结果
	void saveResultDense(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size);
	void saveResultCount(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size);
	//获取图层信息
	void setLayer(GeoLayer *layer1);
	GeoLayer* getLayer();

	//计算一组数的中值
	float getMedian(QList<float> nums);
	//数据标准化
	QList<uchar> MinMaxNormalization(QList<float> data, int scale);
	QList<uchar> MinMaxNormalization(QList<int> data, int scale);
	QList<float> MinMaxNormalization_pop(QList<float> data, float scale);


	int getWidthCellNum();
	int getHeightCellNum();
	float ** getKDResult();
	float getCellSize();
	QString getFullPath();
private:
	GeoLayer *layer;
	int nXSize;
	int nYSize;
	float ** KDResult;
	float cellSize;

};


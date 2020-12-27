#include "CGeoKernalDensTool.h"

CGeoKernalDensTool::CGeoKernalDensTool()
{
	GDALAllRegister();//注册所有驱动
	OGRRegisterAll();
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8", "NO");//支持中文路径
}

CGeoKernalDensTool::~CGeoKernalDensTool()
{
}

int CGeoKernalDensTool::run_tool()
{
	if (layer->getType() ==EnumType::POLYGON)
		return 3;//输入数据类型错误

	if (layer->getType() == EnumType::POINT)//点密度分析
	{
		//根据用户的输入获得所有参数
		QList<GeoPoint*>points = getGeoPoints(layer);
		QRectF layerRect = layer->getRect();
		if (points.size() == 0)//输入的数据无效
			return 2;

		if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
			COption* option = (COption*)this->option;
			QString output_file = option->output_file;
			float output_cell_size = getCellSize(layerRect);
			cellSize = output_cell_size;

			QList<float> populations = getPopulations(points, layer);
			if (populations.size() == 0)//字段不符合要求
				return 1;

			float search_radius = getSearchRadius(points, populations, layerRect);
			int area_unit = option->area_unit;
			int method = option->method_type;
			int outputvalue = option->output_value_type;

			//进行分析
			if (outputvalue == 0)//写出核密度
			{
				QList<float> KDResult = KernelDensity(points, populations, output_cell_size,
					search_radius, area_unit, method, layerRect);//得到结果
				QList<uchar> resultDensity = MinMaxNormalization(KDResult, 255);//归一化
				saveResultDense(output_file, resultDensity, layerRect, output_cell_size);//写出结果
			}
			else if (outputvalue == 1)//写出点数
			{
				QList<int> KDResult = KernelCount(points, populations, output_cell_size,
					search_radius, area_unit, method, layerRect);//得到结果
				QList<uchar> resultCount = MinMaxNormalization(KDResult, 255);//归一化
				saveResultCount(output_file, resultCount, layerRect, output_cell_size);//写出结果
			}
		}
			
			
	}
	else if (layer->getType() == EnumType::POLYLINE)
	{
		//根据用户的输入获得所有参数
		QList<GeoPolyline*>polylines = getGeoPolyline(layer);
		QRectF layerRect = layer->getRect();
		if (polylines.size() == 0)//输入的数据无效
			return 2;

		if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
			COption* option = (COption*)this->option;
			QString output_file = option->output_file;
			float output_cell_size = getCellSize(layerRect);
			cellSize = output_cell_size;
			QList<float> populations = getPopulations(polylines, layer);
			if (populations.size() == 0)//字段不符合要求
				return 1;

			QList<GeoPoint*>points = getPolylineMeanCenters(polylines);//得到所有polyline的meanCenter
			float search_radius = getSearchRadius(points, populations, layerRect);
			int area_unit = option->area_unit;
			int method = option->method_type;
			int outputvalue = option->output_value_type;

			//进行分析
			if (outputvalue == 0)//写出核密度
			{
				QList<float> KDResult = KernelDensity_line(polylines, populations, output_cell_size,
					search_radius, area_unit, method, layerRect);//得到结果
				QList<uchar> resultDensity = MinMaxNormalization(KDResult, 255);//归一化
				saveResultDense(output_file, resultDensity, layerRect, output_cell_size);//写出结果
			}
			else if (outputvalue == 1)//写出点数
			{
				QList<int> KDResult = KernelCount_line(polylines, populations, output_cell_size,
					search_radius, area_unit, method, layerRect);//得到结果
				QList<uchar> resultCount = MinMaxNormalization(KDResult, 255);//归一化
				saveResultCount(output_file, resultCount, layerRect, output_cell_size);//写出结果
			}
		}
			
	}

	return 0;
}

QList<GeoPoint*> CGeoKernalDensTool::getGeoPoints(GeoLayer * layer)
{
	QList<GeoPoint*>points;
	if (layer->getType() == EnumType::POINT)//点的核密度计算
	{
		QList<GeoFeature*>features = layer->getAllFeature();
		int featureNum = features.size();
		for (int i = 0; i < featureNum; i++)
		{
			points.append(static_cast<GeoPoint*>(features.at(i)->getGeometry()));
		}
	}
	return points;
}

QList<GeoPolyline*> CGeoKernalDensTool::getGeoPolyline(GeoLayer * layer)
{
	QList<GeoPolyline*>polylines;
	if (layer->getType() == EnumType::POLYLINE)//点的核密度计算
	{
		QList<GeoFeature*>features = layer->getAllFeature();
		int featureNum = features.size();
		for (int i = 0; i < featureNum; i++)
		{
			polylines.append(static_cast<GeoPolyline*>(features.at(i)->getGeometry()));
		}
	}
	return polylines;
}

QList<float> CGeoKernalDensTool::getPopulations(QList<GeoPoint*> points,GeoLayer *layer)
{
	QList<float> populations, populations_unNormd;
	//如果用户未指定population字段，则将population全部赋值为1
	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		QString field = option->population_field;
		if (option->population_field.isNull() || option->population_field == QString("NONE"))
		{
			for (int i = 0; i < points.size(); i++)
				populations.append(1.0f);
		}
		else
		{
			QList<QString> attris = layer->getAttributeNames();
			int attriNum = attris.size();
			for (int j = 0; j < points.size(); j++)//遍历所有要素
			{
				QVariant var = layer->getFeatureAt(j)->getAttributeMap()->value(option->population_field);
				if (var.toFloat() > MINFLOAT)
					populations_unNormd.append(var.toFloat());
			}
			populations = MinMaxNormalization_pop(populations_unNormd, 1.0f);//将pop字段归一化
		}
		return populations;
	}

	
}

QList<float> CGeoKernalDensTool::getPopulations(QList<GeoPolyline*> polylines, GeoLayer *layer)
{
	QList<float> populations, populations_unNormd;
	//如果用户未指定population字段，则将population全部赋值为1

	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		QString field = option->population_field;
		if (option->population_field.isNull() || option->population_field == QString("NONE"))
		{
			for (int i = 0; i < polylines.size(); i++)
				populations.append(1.0f);
		}
		else
		{
			QList<QString> attris = layer->getAttributeNames();
			int attriNum = attris.size();
			for (int j = 0; j < polylines.size(); j++)//遍历所有要素
			{
				QVariant var = layer->getFeatureAt(j)->getAttributeMap()->value(option->population_field);
				if (var.toFloat() > MINFLOAT)
					populations_unNormd.append(var.toFloat());
			}
			populations = MinMaxNormalization_pop(populations_unNormd, 1.0f);//将pop字段归一化
		}
	}
	
	return populations;
}

QList<GeoPoint*> CGeoKernalDensTool::getPolylineMeanCenters(QList<GeoPolyline*> polylines)
{
	QList<GeoPoint*> meanCenters;
	int polylineNum = polylines.size();
	for (int i = 0; i < polylineNum; i++)
		meanCenters.append(polylines.at(i)->getMeanCenter());
	return meanCenters;
}

float CGeoKernalDensTool::getSearchRadius(QList<GeoPoint*> points, QList<float> populations,QRectF layerRect)
{
	float searchRadius;
	//如果用户未指定任何内容，则计算默认带宽
	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		if (option->search_radius < MINFLOAT)
		{
			float SD = 0, Dm = 0, n = 0;
			float Xsd = 0, Ysd = 0, Xmean = 0, Ymean = 0;
			float pointNum = points.size();
			//计算平均中心（加权）
			for (int i = 0; i < pointNum; i++)
			{
				Xmean = Xmean + (points.at(i)->getXf())*populations.at(i);
				Ymean = Ymean + (points.at(i)->getYf())*populations.at(i);
			}
			Xmean = Xmean / pointNum;
			Ymean = Ymean / pointNum;
			QPointF centerPoint = QPointF(Xmean, Ymean);//加权平均中心

			QList<float> disToCenter;//计算所有点（加权）到平均中心的距离
			for (int i = 0; i < pointNum; i++)
			{
				disToCenter.append(getDis(*points.at(i), centerPoint)*populations.at(i));//此处还要不要加权？
				n = n + populations.at(i);//n是点数（没权），population字段的总和（加权）
				Xsd = Xsd + pow(points.at(i)->getXf() - Xmean, 2);
				Ysd = Ysd + pow(points.at(i)->getYf() - Ymean, 2);
			}
			Dm = getMedian(disToCenter);//计算这些距离的中值
			SD = pow(Xsd*(1 / pointNum) + Ysd * (1 / pointNum), 0.5);
			float Dm1 = pow(1 / log(2), 0.5)*Dm;
			float minD = SD;
			if (minD > Dm1)
				minD = Dm1;
			searchRadius = 0.9*minD*pow(n, -0.2);
		}
		//如果用户指定内容，则直接返回
		else
			searchRadius = option->search_radius;
	}
	
	return searchRadius;
}

float CGeoKernalDensTool::getCellSize(QRectF layerRect)
{
	float cellSize;
	//如果用户未指定任何内容，则象元大小会通过使用范围的宽度或高度中的较小值除以250来计算
	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		if (option->output_cell_size < MINFLOAT)
		{
			float min = abs(layerRect.height());
			if (min > abs(layerRect.width()))
				min = abs(layerRect.width());
			cellSize = min / 100;
		}
		//如果用户指定内容，则直接返回
		else
			cellSize = option->output_cell_size;
	}
	
	return cellSize;
}

float CGeoKernalDensTool::getDis(GeoPoint pt1, QPointF pt2)
{
	float dis;
	float R = 6378137;
	//如果method_type为0则使用平面距离
	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		if (option->method_type == 0)
		{
			float dx = pt1.getXf() - pt2.x();
			float dy = pt1.getYf() - pt2.y();
			dis = pow(dx * dx + dy * dy, 0.5);
		}
		//如果method_type为1则使用大地线距离
		else if (option->method_type == 1)
		{
			float dB = (pt1.getYf() - pt2.x())*PI / 180;
			float dL = (pt1.getXf() - pt2.y())*PI / 180;
			float a = sinf(dL / 2)*sinf(dB / 2) + cosf(pt1.getXf()*PI / 180)*cosf(pt2.x()*PI / 180)*sinf(dL / 2)*sinf(dL / 2);
			float c = 2 * atan2f(pow(a, 0.5), pow((1 - a), 0.5));
			dis = R * c;
		}
	}
	
	return dis;
}

QList<float> CGeoKernalDensTool::KernelDensity(QList<GeoPoint*> points, QList<float> populations,
	float cell_size, float search_radius, int area_unit, int method,QRectF layerRect)
{
	//根据cellsize得到行数和列数（取整）
	nYSize = abs(layerRect.height()) / cell_size;
	nXSize = abs(layerRect.width()) / cell_size;

	float *KDResult_final = new float[nXSize*nYSize];

	//创建数据存储空间,并为每一个栅格赋初值0
	KDResult = new float *[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		KDResult[y] = new float[nXSize];
		for (int x = 0; x < nXSize; x++)
			KDResult[y][x] = MINFLOAT;
	}
	//创建每一栅格中心点对应的x坐标 y坐标矩阵
	float **LocX = new float*[nYSize];
	float **LocY = new float*[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		LocY[y] = new float[nXSize];
		LocX[y] = new float[nXSize];
		for (int x = 0; x < nXSize; x++)
		{
			LocX[y][x] = layerRect.left() + (0.5 + x)*cell_size;
			LocY[y][x] = layerRect.top() - (0.5 + y)*cell_size;
		}
	}

		//计算每一个栅格的数值,point的顺序与population的顺序一致
	    QList<float>KDResult_forOutPut;
		int pointNum = points.size();
		for (int y = 0; y < nYSize; y++)
		{
			for (int x = 0; x < nXSize; x++)
			{
				QPointF gridPoint(LocX[y][x], LocY[y][x]);
				QList<float>pops;
				QList<float>dists;
				float pop, dist;
				for (int i = 0; i < pointNum; i++)//遍历每一个要素点，若在搜索半径范围内，则加入
				{
					dist = getDis(*points.at(i), gridPoint);
					pop = populations.at(i);
					if (dist < search_radius)
					{
						pops.append(pop);
						dists.append(dist);
					}
				}
				if (pops.size() > 0)
				{
					KDResult[y][x] = getDensity(search_radius, pops, dists);
					KDResult_forOutPut.append(getDensity(search_radius, pops, dists));
				}
				else
				{
					KDResult[y][x] = 0.0f;
					KDResult_forOutPut.append(0.0f);
				}
			}
		}

	return KDResult_forOutPut;
}

QList<float> CGeoKernalDensTool::KernelDensity_line(QList<GeoPolyline*> polylines, QList<float> populations, float cell_size, float search_radius, int area_unit, int method, QRectF layerRect)
{
	//根据cellsize得到行数和列数（取整）
	nYSize = abs(layerRect.height()) / cell_size;
	nXSize = abs(layerRect.width()) / cell_size;

	float *KDResult_final = new float[nXSize*nYSize];

	//创建数据存储空间,并为每一个栅格赋初值0
	KDResult = new float *[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		KDResult[y] = new float[nXSize];
		for (int x = 0; x < nXSize; x++)
			KDResult[y][x] = MINFLOAT;
	}
	//创建每一栅格中心点对应的x坐标 y坐标矩阵
	float **LocX = new float*[nYSize];
	float **LocY = new float*[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		LocY[y] = new float[nXSize];
		LocX[y] = new float[nXSize];
		for (int x = 0; x < nXSize; x++)
		{
			LocX[y][x] = layerRect.left() + (0.5 + x)*cell_size;
			LocY[y][x] = layerRect.top() - (0.5 + y)*cell_size;
		}
	}

	//计算每一个栅格的数值,point的顺序与population的顺序一致
	QList<float>KDResult_forOutPut;
	int polylineNum = polylines.size();
	for (int y = 0; y < nYSize; y++)
	{
		for (int x = 0; x < nXSize; x++)
		{
			//QPointF gridPoint(LocX[y][x], LocY[y][x]);
			GeoPoint *pt = new GeoPoint();
			pt->setXf(LocX[y][x]), pt->setYf(LocY[y][x]);
			QList<float>pops;
			QList<float>dists;
			float pop, dist;
			for (int i = 0; i < polylineNum; i++)//遍历每一个要素线，若在搜索半径范围内，则加入
			{
				dist = polylines.at(i)->disToPoint(pt);
				pop = populations.at(i);
				if (dist < search_radius)
				{
					pops.append(pop);
					dists.append(dist);
				}
			}
			if (pops.size() > 0)
			{
				KDResult[y][x] = getDensity(search_radius, pops, dists);
				KDResult_forOutPut.append(getDensity(search_radius, pops, dists));
			}
			else
			{
				KDResult[y][x] = 0.0f;
				KDResult_forOutPut.append(0.0f);
			}
		}
	}

	return KDResult_forOutPut;
}

QList<int> CGeoKernalDensTool::KernelCount(QList<GeoPoint*> points, QList<float> populations,
	float cell_size, float search_radius, int area_unit, int method, QRectF layerRect)
{
	//根据cellsize得到行数和列数（取整）
	nYSize = abs(layerRect.height()) / cell_size;
	nXSize = abs(layerRect.width()) / cell_size;

	int *KDResult_final = new int[nXSize*nYSize];
	//创建数据存储空间,并为每一个栅格赋初值0
	int **KDResult = new int *[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		KDResult[y] = new int[nXSize];
		for (int x = 0; x < nXSize; x++)
			KDResult[y][x] = MINFLOAT;
	}
	//创建每一栅格中心点对应的x坐标 y坐标矩阵
	float **LocX = new float*[nYSize];
	float **LocY = new float*[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		LocY[y] = new float[nXSize];
		LocX[y] = new float[nXSize];
		for (int x = 0; x < nXSize; x++)
		{
			LocX[y][x] = layerRect.left() + (0.5 + x)*cell_size;
			LocY[y][x] = layerRect.top() - (0.5 + y)*cell_size;
		}
	}
	    QList<int> KDResut_forOutput;
		int pointNum = points.size();
		for (int y = 0; y < nYSize; y++)
		{
			for (int x = 0; x < nXSize; x++)
			{
				int count = 0;
				QPointF gridPoint(LocX[y][x], LocY[y][x]);
				float dist;
				for (int i = 0; i < pointNum; i++)//遍历每一个要素点，若在搜索半径范围内，则加入
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

QList<int> CGeoKernalDensTool::KernelCount_line(QList<GeoPolyline*> polylines, QList<float> populations, float cell_size, float search_radius, int area_unit, int method, QRectF layerRect)
{
	//根据cellsize得到行数和列数（取整）
	nYSize = abs(layerRect.height()) / cell_size;
	nXSize = abs(layerRect.width()) / cell_size;

	int *KDResult_final = new int[nXSize*nYSize];
	//创建数据存储空间,并为每一个栅格赋初值0
	int **KDResult = new int *[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		KDResult[y] = new int[nXSize];
		for (int x = 0; x < nXSize; x++)
			KDResult[y][x] = MINFLOAT;
	}
	//创建每一栅格中心点对应的x坐标 y坐标矩阵
	float **LocX = new float*[nYSize];
	float **LocY = new float*[nYSize];
	for (int y = 0; y < nYSize; y++)
	{
		LocY[y] = new float[nXSize];
		LocX[y] = new float[nXSize];
		for (int x = 0; x < nXSize; x++)
		{
			LocX[y][x] = layerRect.left() + (0.5 + x)*cell_size;
			LocY[y][x] = layerRect.top() - (0.5 + y)*cell_size;
		}
	}
	QList<int> KDResut_forOutput;
	int polylineNum = polylines.size();
	for (int y = 0; y < nYSize; y++)
	{
		for (int x = 0; x < nXSize; x++)
		{
			int count = 0;
			GeoPoint *pt = new GeoPoint();
			pt->setXf(LocX[y][x]), pt->setYf(LocY[y][x]);
			//QPointF gridPoint(LocX[y][x], LocY[y][x]);
			float dist;
			for (int i = 0; i < polylineNum; i++)//遍历每一个要素点，若在搜索半径范围内，则加入
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

float CGeoKernalDensTool::getDensity(float search_radius, QList<float> pops, QList<float> dists)
{
	//一共有n个要素点在所计算栅格的搜索半径内
	//pops为在半径内要素点的字段值，dists为计算栅格点与半径内要素点的距离
	int n = pops.size();
	float density = 0;
	float dens = 0;
	if (n != 0)
	{
		for (int i = 0; i < n; i++)
		{
			dens = dens + (3 / PI)* pops.at(i)*pow((1 - pow((dists.at(i) / search_radius), 2)), 2);
		}
		density = (1 / pow(search_radius, 2))*dens;
	}
	return density;
}

void CGeoKernalDensTool::saveResultDense(QString output_file,QList<uchar> result,QRectF layerRect,float cell_size)
{
    ////定义参数，配置图像信息
    //QByteArray ba = output_file.toLocal8Bit();
    //const char *outfilePath = ba.resource();
    //int nYSize = abs(layerRect.height()) / cell_size;
    //int nXSize = abs(layerRect.width()) / cell_size;
    //int nBands = 1;
    //char **ppszOptions = NULL;
    //char **raster_creation_options = NULL;

    ////创建栅格数据集，如果创建后什么都不做，GDAL会自动写入0像素值
    //GDALDataset *dataset;
    ////GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");//图像驱动
    //GDALDriver *driver;
	//dataset = driver->Create(outfilePath, nXSize, nYSize, nBands, GDT_Float32, raster_creation_options);

	////写入栅格数据信息
	//dataset->RasterIO(GF_Write, 0, 0, nXSize, nYSize, KDResult, nXSize, nYSize, GDT_Float32, 1, NULL, 0, 0, 0);

	////关闭打开的文件
	//GDALClose(dataset);

	int resultLength = result.size();
	uchar *KDResult = new uchar[resultLength];

	//保存8位灰度图
	for (int i = 0; i < resultLength; i++)
		KDResult[i] = result.at(i);
	int bytePerLine = nXSize * 1;
	QImage denseResult(KDResult, nXSize, nYSize, bytePerLine, QImage::Format_Grayscale8, nullptr, nullptr);
	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		if (option->output_file.contains(QString("jpg")))
			denseResult.save(output_file, "JPG", 100);
		else if (option->output_file.contains(QString(".png")))
			denseResult.save(output_file, "PNG", 100);
		else if (option->output_file.contains(QString(".bmp")))
			denseResult.save(output_file, "BMP", 100);
	}
	
}

void CGeoKernalDensTool::saveResultCount(QString output_file, QList<uchar> result, QRectF layerRect, float cell_size) {
    ////定义参数，配置图像信息
    //QByteArray ba = output_file.toLocal8Bit();
    //const char *outfilePath = ba.resource();
    //int nYSize = abs(layerRect.height()) / cell_size;
    //int nXSize = abs(layerRect.width()) / cell_size;
    //int nBands = 1;
    //char **ppszOptions = NULL;
    //char **raster_creation_options = NULL;

    ////创建栅格数据集，如果创建后什么都不做，GDAL会自动写入0像素值
    //GDALDataset *dataset;
    //GDALDriver *driver = GetGDALDriverManager()->GetDriverByName("GTiff");//图像驱动
    ////GDALDriver *driver;
	//dataset = driver->Create(outfilePath, nXSize, nYSize, nBands, GDT_Int32 , raster_creation_options);

	////写入栅格数据信息
	//dataset->RasterIO(GF_Write, 0, 0, nXSize, nYSize, KDResult, nXSize, nYSize, GDT_Int32, 1, NULL, 0, 0, 0);

	////关闭打开的文件
	//GDALClose(dataset);

	//int resultLength = result.size();
	//uchar *KDResult = new uchar[resultLength];
	//for (int i = 0; i < resultLength; i++)
	//	KDResult[i] = result.at(i);

	int resultLength = result.size();
	uchar *KCResult = new uchar[resultLength];
    
	//保存8位灰度图
	for (int i = 0; i < resultLength; i++)
		KCResult[i] = result.at(i);
	int bytePerLine = nXSize * 1;
	QImage denseResult(KCResult, nXSize, nYSize, bytePerLine, QImage::Format_Grayscale8, nullptr, nullptr);
	if (option->getToolType() == EnumType::sparitalAnalysisTool::KERNEL_DENSITY_ANALYSIS) {
		COption* option = (COption*)this->option;
		if (option->output_file.contains(QString("jpg")))
			denseResult.save(output_file, "JPG", 100);
		else if (option->output_file.contains(QString(".png")))
			denseResult.save(output_file, "PNG", 100);
		else if (option->output_file.contains(QString(".bmp")))
			denseResult.save(output_file, "BMP", 100);
	}
	
}

void CGeoKernalDensTool::setLayer(GeoLayer * layer1)
{
	layer = layer1;
}

GeoLayer * CGeoKernalDensTool::getLayer()
{
	return layer;
}

float CGeoKernalDensTool::getMedian(QList<float> nums)
{
	float median;
	float temp;
	int size = nums.size();
	//冒泡排序法
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - 1 - i; j++)
		{
			if (nums.at(j) > nums.at(j + 1))
				nums.swapItemsAt(j, j+1);
		}
	}
	//寻找中值
	if (size % 2 == 0)
		median = 0.5*(nums.at(size*0.5) + nums.at(size*0.5 - 1));
	else
		median = nums.at(floor(size *0.5));
	return median;
}

QList<uchar> CGeoKernalDensTool::MinMaxNormalization(QList<float> data,int scale)
{
	int length = data.size();
	QList<uchar> results;
	//找到最大值和最小值
	float min, max;
	for (int i = 0; i < length; i++)
	{
		if (i == 0)
		{
			min = data.at(i);
			max = data.at(i);
		}
		if (min > data.at(i))
			min = data.at(i);
		if (max < data.at(i))
			max = data.at(i);
	}
	//归一化到0-255之间
	for (int i = 0; i < length; i++)
	{
		results.append(floor(((data[i] - min) / (max - min)) * scale));
	}
	return results;
}

QList<uchar> CGeoKernalDensTool::MinMaxNormalization(QList<int> data,int scale)
{
	QList<uchar> results;
	int length = data.size();
	//找到最大值和最小值
	float min, max;
	for (int i = 0; i < length; i++)
	{
		if (i == 0)
		{
			min = data.at(i);
			max = data.at(i);
		}
		if (min > data.at(i))
			min = data.at(i);
		if (max < data.at(i))
			max = data.at(i);
	}
	//归一化到0-255之间
	for (int i = 0; i < length; i++)
	{
		results.append(floor(((float(data[i]) - min) / (max - min)) * scale));
	}
	return results;
}

QList<float> CGeoKernalDensTool::MinMaxNormalization_pop(QList<float> data, float scale)
{
	QList<float> results;
	int length = data.size();
	//找到最大值和最小值
	float min, max;
	for (int i = 0; i < length; i++)
	{
		if (i == 0)
		{
			min = data.at(i);
			max = data.at(i);
		}
		if (min > data.at(i))
			min = data.at(i);
		if (max < data.at(i))
			max = data.at(i);
	}
	//归一化到0-255之间
	for (int i = 0; i < length; i++)
	{
		results.append(((data[i] - min) / (max - min)) * scale);
	}
	return results;
}

int CGeoKernalDensTool::getWidthCellNum()
{
	return nXSize;
}

int CGeoKernalDensTool::getHeightCellNum()
{
	return nYSize;
}

float ** CGeoKernalDensTool::getKDResult()
{
	return KDResult;
}

float CGeoKernalDensTool::getCellSize()
{
	return cellSize;
}

QString CGeoKernalDensTool::getFullPath()
{
	return ((COption*)this->option)->output_file;
}




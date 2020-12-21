#include "GdalTool.h"
using namespace std;
GdalTool::GdalTool(void)
{
}


GdalTool::~GdalTool(void)
{
}


gpc_vertex GdalTool::BuildVertex(float x, float y)
{
	gpc_vertex vertex; 
	vertex.x = x; 
	vertex.y = y; 
	return vertex;
}

/**
*	将shp解析为GeoJson格式
*/
void GdalTool::getGeoJson(const char* filename){
	// 注册
	GDALAllRegister();
	// 新建数据集对象
	GDALDataset *poDS;
	// 解决中文路径
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	// 解决中文乱码问题
	CPLSetConfigOption("SHAPE_ENCODING","");
    // 读取shp文件
    poDS = (GDALDataset *) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
    if (poDS == NULL) {
        printf("Open failed.\n");
        exit(1);
    }
    // 新建驱动
    OGRSFDriverH driver = OGRGetDriverByName("GeoJSON");
    // 输出文件
    OGR_Dr_CopyDataSource(driver, poDS, "tests.geojson", NULL);
    // 关闭文件
    GDALClose(poDS);
}
/**
*	解析属性表文件
*/
void GdalTool::getDBF(const char* filename){
	// 注册
	GDALAllRegister();
	// 新建数据集对象
	GDALDataset *poDS;
	// 解决中文路径
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	// 解决中文乱码问题
	CPLSetConfigOption("SHAPE_ENCODING","");  
	// 读取shp文件
	poDS = (GDALDataset*) GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL );
	if( poDS == NULL )
	{
		printf( "Open failed.\n" );
		exit( 1 );
	}
	// 新建txt文件
	ofstream dataFile;
	fstream file("dataFile.txt", ios::out);
	dataFile.open("dataFile.txt", ofstream::app);
	if(dataFile!=NULL)
		dataFile.clear();
	dataFile << "{" << endl;

	// 得到图层数
	int layerCount = poDS->GetLayerCount();
	for(int k=0;k<layerCount;k++){
		// 图层类对象
		OGRLayer *poLayer;
		poLayer = poDS->GetLayer(k); //读取层
		// 要素描述类对象
		OGRFeatureDefn *poFeaDefn;
		poFeaDefn = poLayer->GetLayerDefn();
		// 要素类对象
		OGRFeature *poFeature;
		poLayer->ResetReading();
		int i=0;
		while( (poFeature = poLayer->GetNextFeature()) != NULL )
		{
			i=i++;
			cout<<i<<"  ";
			dataFile << i<<":{"<<endl;
			int n=poFeaDefn->GetFieldCount(); //获得字段的数目，不包括前两个字段（FID,Shape);
			for(int iField = 0; iField <n; iField++ )
			{
				// 得到列名
				dataFile<<poFeaDefn->GetFieldDefn(iField)->GetNameRef()<<":";
				//输出每个字段的值
				cout<<poFeature->GetFieldAsString(iField)<<"    ";
				// 朝TXT文档中写入数据
				dataFile << poFeature->GetFieldAsString(iField)<< ","<<endl;
			}
			dataFile << "}"<<endl;
			cout<<endl;
			OGRFeature::DestroyFeature( poFeature );
		}
	}
	dataFile << "}" << endl;
	GDALClose( poDS );
	// 关闭文档
	dataFile.close();
}

CGeoLayer* GdalTool::readShape(const char* filename){
	// 注册
	GDALAllRegister();
	// 解决中文路径
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	// 解决中文乱码问题
	CPLSetConfigOption("SHAPE_ENCODING","");  
	// 读取
	GDALDataset* dataset = (GDALDataset*)GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
	if( dataset == NULL )
	{
		printf( "Open failed.\n" );
		exit( 1 );
	}
	// 图层类对象
	OGRLayer *poLayer;
	CGeoLayer *geolayer = new CGeoLayer();
	poLayer = dataset->GetLayer(0); //读取层
	// 要素描述类对象
	OGRFeatureDefn *poFeaDefn;
	poFeaDefn = poLayer->GetLayerDefn();
	geolayer->setLayerName(QString::fromLocal8Bit(poLayer->GetName()));
	OGREnvelope *envelope = new OGREnvelope;
	poLayer->GetExtent(envelope);
	geolayer->setRect(QRectF(QPointF(envelope->MinX,envelope->MaxY),QPointF(envelope->MaxX,envelope->MinY)));
	// 要素类对象
	OGRFeature *poFeature;
	int n=poFeaDefn->GetFieldCount(); //获得字段的数目，不包括前两个字段（FID,Shape);
	// 确保是从开始读的
	poLayer->ResetReading();
	int i=0;
	while( (poFeature = poLayer->GetNextFeature()) != NULL )
	{
		CGeoObject *object;
		OGRGeometry *geo = poFeature->GetGeometryRef();
		if( geo != NULL
			&& wkbFlatten(geo->getGeometryType()) == wkbPoint )
		{
			OGRPoint *poPoint = (OGRPoint *) geo;
			object = new CGeoPoint();
			((CGeoPoint *)object)->setType(QString("Point"));
			QPointF pt;
			pt.setX(poPoint->getX());
			pt.setY(poPoint->getY());
			((CGeoPoint *)object)->setPoint(pt);
			((CGeoPoint *)object)->pts.append(QPointF(pt.x()-0.001*pt.x(),pt.y()+0.001*pt.y()));
			((CGeoPoint *)object)->pts.append(QPointF(pt.x()-0.001*pt.x(),pt.y()-0.001*pt.y()));
			((CGeoPoint *)object)->pts.append(QPointF(pt.x()+0.001*pt.x(),pt.y()-0.001*pt.y()));
			((CGeoPoint *)object)->pts.append(QPointF(pt.x()+0.001*pt.x(),pt.y()+0.001*pt.y()));
			((CGeoPoint *)object)->pts.append(QPointF(pt.x()-0.001*pt.x(),pt.y()+0.001*pt.y()));

			geolayer->type = 0;

		}
		else if(geo != NULL
			&& wkbFlatten(geo->getGeometryType()) == wkbPolygon )
		{
			OGRPolygon *polygon = (OGRPolygon*) geo;
			object = new CGeoPolygon();
			((CGeoPolygon *)object)->setType(QString("Polygon"));
			OGRLinearRing *ring = polygon->getExteriorRing();
			int pointNum = ring->getNumPoints(); // 点个数
			OGRRawPoint *points = new OGRRawPoint[pointNum];
			ring->getPoints(points);

			for(int i=0;i<pointNum;i++){
				QPointF pt;
				pt.setX(points[i].x);
				pt.setY(points[i].y);
				((CGeoPolygon *)object)->addPoint(pt);
			}
			geolayer->type = 2;

		}
		else if(geo != NULL
			&& wkbFlatten(geo->getGeometryType()) == wkbLineString )
		{
			OGRLineString *polyline = (OGRLineString*) geo;
			object = new CGeoPolyline();
			((CGeoPolyline *)object)->setType(QString("Polyline"));
			int pointNum = polyline->getNumPoints(); // 点个数

			for(int i=0;i<pointNum;i++){
				QPointF pt;
				pt.setX(polyline->getX(i));
				pt.setY(polyline->getY(i));
				((CGeoPolyline *)object)->addPoint(pt);
			}
			geolayer->type = 1;

		}else{
			QMessageBox::critical(NULL, QString::fromLocal8Bit("不支持的类型"), QString::fromLocal8Bit("该要素图层不为点、线、面格式，暂不支持!"), QMessageBox::Yes, QMessageBox::Yes);  
			return nullptr;
		}

		QMap<QString,QString> str;
		// 设置属性
		for(int iField = 0; iField <n; iField++ )
		{
			str.insert(QString::fromLocal8Bit(poFeaDefn->GetFieldDefn(iField)->GetNameRef()),QString::fromLocal8Bit(poFeature->GetFieldAsString(iField)));
		}
		object->setProps(str);

		geolayer->addObjects(object);
		OGRFeature::DestroyFeature( poFeature );

	}
	GDALClose( dataset );
	MyXMLReader xmlReader;
	xmlReader.readSLDFile("G:\\finally\\polygon.xml",geolayer);
	geolayer->setPropsKey();
	makeIndex(geolayer);
	// 如果是Polygon，进行剖分
	if(geolayer->type==2){
		CGeoLayer *tessaLayer = subvision(geolayer);
		geolayer->tessaLayer = tessaLayer;
	}
	return geolayer;
}


CGeoLayer* GdalTool::readShapeWithoutTriangle(const char* filename){
	// 注册
	GDALAllRegister();
	// 解决中文路径
	CPLSetConfigOption("GDAL_FILENAME_IS_UTF8","NO");
	// 解决中文乱码问题
	CPLSetConfigOption("SHAPE_ENCODING","");  
	// 读取
	GDALDataset* dataset = (GDALDataset*)GDALOpenEx(filename, GDAL_OF_VECTOR, NULL, NULL, NULL);
	if( dataset == NULL )
	{
		printf( "Open failed.\n" );
		exit( 1 );
	}
	// 图层类对象
	OGRLayer *poLayer;
	CGeoLayer *geolayer = new CGeoLayer();
	poLayer = dataset->GetLayer(0); //读取层
	// 要素描述类对象
	OGRFeatureDefn *poFeaDefn;
	poFeaDefn = poLayer->GetLayerDefn();
	geolayer->setLayerName(QString::fromLocal8Bit(poLayer->GetName()));
	OGREnvelope *envelope = new OGREnvelope;
	poLayer->GetExtent(envelope);
	geolayer->setRect(QRectF(QPointF(envelope->MinX,envelope->MaxY),QPointF(envelope->MaxX,envelope->MinY)));
	// 要素类对象
	OGRFeature *poFeature;
	int n=poFeaDefn->GetFieldCount(); //获得字段的数目，不包括前两个字段（FID,Shape);
	// 确保是从开始读的
	poLayer->ResetReading();
	int i=0;
	while( (poFeature = poLayer->GetNextFeature()) != NULL )
	{
		CGeoObject *object;
		OGRGeometry *geo = poFeature->GetGeometryRef();
		if( geo != NULL
			&& wkbFlatten(geo->getGeometryType()) == wkbPoint )
		{
			OGRPoint *poPoint = (OGRPoint *) geo;
			object = new CGeoPoint();
			((CGeoPoint *)object)->setType(QString("Point"));
			QPointF pt;
			pt.setX(poPoint->getX());
			pt.setY(poPoint->getY());
			((CGeoPoint *)object)->setPoint(pt);
			geolayer->type = 0;

		}
		else if(geo != NULL
			&& wkbFlatten(geo->getGeometryType()) == wkbPolygon )
		{
			OGRPolygon *polygon = (OGRPolygon*) geo;
			OGRPoint *point = new OGRPoint();
			object = new CGeoPolygon();
			((CGeoPolygon *)object)->setType(QString("Polygon"));
			((CGeoPolygon *)object)->centriod.setX(point->getX());
			((CGeoPolygon *)object)->centriod.setY(point->getY());
			OGRLinearRing *ring = polygon->getExteriorRing();
			ring->Centroid(point);
			int pointNum = ring->getNumPoints(); // 点个数
			OGRRawPoint *points = new OGRRawPoint[pointNum];
			ring->getPoints(points);
			for(int i=0;i<pointNum;i++){
				QPointF pt;
				pt.setX(points[i].x);
				pt.setY(points[i].y);
				((CGeoPolygon *)object)->addPoint(pt);
			}
			geolayer->type = 2;

		}
		else if(geo != NULL
			&& wkbFlatten(geo->getGeometryType()) == wkbLineString )
		{
			OGRLineString *polyline = (OGRLineString*) geo;
			object = new CGeoPolyline();
			((CGeoPolyline *)object)->setType(QString("Polyline"));

			int pointNum = polyline->getNumPoints(); // 点个数
			for(int i=0;i<pointNum;i++){
				QPointF pt;
				pt.setX(polyline->getX(i));
				pt.setY(polyline->getY(i));
				((CGeoPolyline *)object)->addPoint(pt);
			}
			geolayer->type = 1;

		}else{
			QMessageBox::critical(NULL, QString::fromLocal8Bit("不支持的类型"), QString::fromLocal8Bit("该要素图层不为点、线、面格式，暂不支持!"), QMessageBox::Yes, QMessageBox::Yes);  
			return nullptr;
		}

		QMap<QString,QString> str;
		// 设置属性
		for(int iField = 0; iField <n; iField++ )
		{
			str.insert(QString::fromLocal8Bit(poFeaDefn->GetFieldDefn(iField)->GetNameRef()),QString::fromLocal8Bit(poFeature->GetFieldAsString(iField)));
		}
		object->setProps(str);
		// 设置范围
		OGREnvelope *envelope2 = new OGREnvelope;
		geo->getEnvelope(envelope2);
		object->setRect(QRectF(QPointF(envelope2->MinX,envelope2->MaxY),QPointF(envelope2->MaxX,envelope2->MinY)));
		geolayer->addObjects(object);
		OGRFeature::DestroyFeature( poFeature );

	}
	GDALClose( dataset );
	geolayer->setPropsKey();
	return geolayer;
}


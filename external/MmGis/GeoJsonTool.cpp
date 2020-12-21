#include "GeoJsonTool.h"


GeoJsonTool::GeoJsonTool(void)
{
}


GeoJsonTool::~GeoJsonTool(void)
{
}
/*
CGeoLayer* GeoJsonTool::readGeoJSON(const char* filename){
ifstream ifs(filename);
IStreamWrapper isw(ifs);
Document document;
document.ParseStream(isw);
CGeoLayer *geolayer = new CGeoLayer();
// 设置layer名
geolayer->setLayerName(QString("tests"));
// 获得所有的features
const Value& f = document["features"].GetArray();
for(int i=0;i<f.Size();i++){
// 获得geometry的类型
const char* type = f[i]["geometry"]["type"].GetString();
CGeoObject *obj;
// 如果是点
if(strcmp(type, "Point") == 0){
obj = new CGeoPoint();
((CGeoPoint *)obj)->setType(QString("Point"));
const Value& c = f[i]["geometry"]["coordinates"];
QPointF pt;
pt.setX(c[0][0][0].GetDouble());
pt.setY(c[0][0][1].GetDouble());
((CGeoPoint *)obj)->setPoint(pt);
}
else if(strcmp(type, "LineString")==0){
obj = new CGeoPolyline();
((CGeoPolyline *)obj)->setType(QString("Polyline"));
const Value& c = f[i]["geometry"]["coordinates"];
for (SizeType i = 0; i < c[0].Size(); i++){ // 使用 SizeType 而不是 size_t
QPointF pt;
pt.setX(c[0][i][0].GetDouble());
pt.setY(c[0][i][1].GetDouble());
((CGeoPolyline *)obj)->addPoint(pt);
}
}
else if(strcmp(type, "Polygon")==0){
obj = new CGeoPolygon();
((CGeoPolygon *)obj)->setType(QString("Polygon"));
const Value& c = f[i]["geometry"]["coordinates"];
for (SizeType i = 0; i < c[0].Size(); i++){ // 使用 SizeType 而不是 size_t
QPointF pt;
pt.setX(c[0][i][0].GetDouble());
pt.setY(c[0][i][1].GetDouble());
((CGeoPolygon *)obj)->addPoint(pt);
}
}
// 存储属性串
const Value& p = f[i]["properties"];
QString str;
for (Value::ConstMemberIterator itr = p.MemberBegin(); itr != p.MemberEnd(); ++itr)
{
str += QString::fromLocal8Bit(itr->name.GetString());
str += ":";
if(itr->value.IsDouble()){
str += "\"";
double x =itr->value.GetDouble();
str += QString::number(x);
str += "\"";
}
else if(itr->value.IsString())
str += QString::fromLocal8Bit(itr->value.GetString());
else if(itr->value.IsInt()){
str += "\"";
int x = itr->value.GetInt();
str += QString::number(x);
str += "\"";
}
str += ";";
}
obj->setProps(str);
geolayer->addObjects(obj);
}
return geolayer;
}
*/

CGeoLayer* GeoJsonTool::readGeoJSON(const char* filename){
	// 注册
	GDALAllRegister();
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
		if(object->getType().compare("Point")!=0){
			// 设置范围
			OGREnvelope *envelope2 = new OGREnvelope;
			geo->getEnvelope(envelope2);
			object->setRect(QRectF(QPointF(envelope2->MinX,envelope2->MaxY),QPointF(envelope2->MaxX,envelope2->MinY)));
			object->centriod = object->getRect().center();
		}
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
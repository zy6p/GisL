#include "GeoLayer.h"


CGeoLayer::CGeoLayer(void)
{
	paintLoc = false;
	showIndexGrid = false;
	tree = new QuadTree();
}


CGeoLayer::~CGeoLayer(void)
{
	geoObjects.clear();
	ReleaseQuadTree(&tree->root);
}

void CGeoLayer::setRect(QRectF qRect){
	this->qRect = qRect;
}
QRectF CGeoLayer::getRect(){
	return this->qRect;
}

void CGeoLayer::setLayerName(QString layerName){
	this->layerName = layerName;
}
QString CGeoLayer::getLayerName(){
	return this->layerName;
}

void CGeoLayer::setVisible(bool isVisible){
	this->isVisible = isVisible;
}
bool CGeoLayer::getVisible(){
	return this->isVisible;
}

void CGeoLayer::addObjects(CGeoObject* obj){
	geoObjects.append(obj);
}
void CGeoLayer::deleteObjectAt(int index){
	geoObjects.removeAt(index);
}
void CGeoLayer::deleteObjectAll(){
	geoObjects.clear();
}

void CGeoLayer::paint(QPainter *paint){
	for(int i=0;i<geoObjects.size();i++)
		geoObjects[i]->paint(paint);
}

float* CGeoLayer::getVert(float *vert,int *count){
	for(int i=0;i<geoObjects.size();i++){
		vert = geoObjects[i]->getVert(vert,count);
	}
	return vert;
}


QRectF CGeoLayer::getScope(){
	QRectF rect;
	float maxx=0,minx=FLT_MAX,maxy=0,miny=FLT_MAX;
	for(int i=0;i<geoObjects.size();i++){
		QRectF r = geoObjects[i]->getScope();
		if(rect.width()==0){
			rect = r;
		}
		if(r.top()>maxy&&r.top()<1e10){
			maxy = r.top();
		}
		if(r.right()>maxx&&r.right()<1e10){
			maxx = r.right();
		}
		if(r.left()<minx){
			minx = r.left();
		}
		if(r.bottom()<miny){
			miny = r.bottom();
		}
		rect=QRectF(QPointF(minx,maxy),QPointF(maxx,miny));

	}
	this->qRect = rect;
	return rect;
}

void CGeoLayer::setPropsKey(){
	if(geoObjects.size()>0){
		QMap<QString,QString> properties = geoObjects[0]->getProps();
		QMapIterator<QString, QString> i(properties);
		while (i.hasNext()) {
			i.next();
			propsKey.append(i.key());
		}
	}
}

QList<QString> CGeoLayer::getPropsKey(){
	return this->propsKey;
}
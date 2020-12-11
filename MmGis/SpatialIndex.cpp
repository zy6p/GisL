#include "SpatialIndex.h"
using namespace std;

void makeIndex(CGeoLayer*layer){
	QuadTree* pQuadTree = new QuadTree();
	CreateQuadTree(6,layer,pQuadTree);
	layer->tree = pQuadTree;
}

double getDistance(QPointF p1,QPointF p2){
	return sqrt((p1.x()-p2.x())*(p1.x()-p2.x())+(p1.y()-p2.y())*(p1.y()-p2.y()));
}
#pragma once
#include"Index.h"
#include"QuadNode.h"
#include"GeoPoint.h"
#include"GeoPolyline.h"
#include"GeoPolygon.h"
#include"EnumType.h"
#include<qpolygon.h>
#include<qdebug.h>

//地理对象只储存在叶子节点中，是满四叉树
class QuadTree:public Index
{
public:
	QuadTree();
	~QuadTree();//释放四叉树内存
	void CreateQuadTree(QRectF layerRect, QList<GeoFeature*> features);//创建四叉树
	void CreateQuadBranch(int depth, QRectF layerRect, QuadNode *node, QList<GeoFeature*> features);//递归创建各个分支
	GeoFeature* SearchQuadTree(GeoPoint *point, float thresholed);//四叉树索引查询
	GeoFeature* SearchQuadBranch(int depth, QuadNode *node, GeoPoint *point, float threshole);//递归查询各个分支
	void ReleaseQuadTree();//释放四叉树内存
	void ReleaseQuadBranch(int depth, QuadNode *node);//递归释放各个分支内存
	
private:
	QuadNode *root;
	int treeDepth = 4;//默认为3层
};


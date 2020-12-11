#pragma once

#include"Index.h"
#include"QuadNode.h"
#include"GeoPoint.h"
#include"GeoPolyline.h"
#include"GeoPolygon.h"
#include"EnumType.h"
#include<qpolygon.h>
#include<qdebug.h>

//�������ֻ������Ҷ�ӽڵ��У������Ĳ���
class QuadTree : public Index {
public:
    QuadTree();

    ~QuadTree();//�ͷ��Ĳ����ڴ�
    void CreateQuadTree(QRectF layerRect, QList<GeoFeature *> features);//�����Ĳ���
    void CreateQuadBranch(int depth, QRectF layerRect, QuadNode *node, QList<GeoFeature *> features);//�ݹ鴴��������֧
    GeoFeature *SearchQuadTree(GeoPoint *point, float thresholed);//�Ĳ���������ѯ
    GeoFeature *SearchQuadBranch(int depth, QuadNode *node, GeoPoint *point, float threshole);//�ݹ��ѯ������֧
    void ReleaseQuadTree();//�ͷ��Ĳ����ڴ�
    void ReleaseQuadBranch(int depth, QuadNode *node);//�ݹ��ͷŸ�����֧�ڴ�

private:
    QuadNode *root;
    int treeDepth = 4;//Ĭ��Ϊ3��
};


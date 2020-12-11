#ifndef __QUADTREE_H_59CAE94A_E937_42AD_AA27_794E467715BB__
#define __QUADTREE_H_59CAE94A_E937_42AD_AA27_794E467715BB__

#include "GeoLayer.h"
#include <qrect.h>
#include <vector>
#include <deque>

using namespace std;

class CGeoLayer;

/* һ��������������޻��֣�:

UL(1)   |    UR(0) 
----------|----------- 
LL(2)   |    LR(3) 
���¶Ը��������͵�ö�� 
*/
typedef enum {
    UR = 0,
    UL = 1,
    LL = 2,
    LR = 3
} QuadrantEnum;

/*�ռ����MBR��Ϣ*/
typedef struct SHPMBRInfo {
    int nID;        //�ռ����ID��
    QPolygonF Box;    //�ռ����MBR��Χ����
} SHPMBRInfo;

/* �Ĳ����ڵ����ͽṹ */
typedef struct QuadNode {
    QRectF Box;            //�ڵ�������ľ�������
    int nShpCount;      //�ڵ������������пռ�������
    SHPMBRInfo *pShapeObj;      //�ռ����ָ������
    int nChildCount;        //�ӽڵ����
    QuadNode *children[4];     //ָ��ڵ���ĸ�����
} QuadNode;

/* �Ĳ������ͽṹ */
typedef struct quadtree_t {
    QuadNode *root;
    int depth;           // �Ĳ��������
} QuadTree;


//��ʼ���Ĳ����ڵ�  
QuadNode *InitQuadNode();

//��δ����Ĳ������������Ĳ�����  
void CreateQuadTree(int depth, CGeoLayer *poLayer, QuadTree *pQuadTree);

//����������֧  
void CreateQuadBranch(int depth, QRectF &rect, QuadNode **node);

//�����Ĳ����ռ�����  
//void BuildQuadTree(CGeoLayer*poLayer,QuadTree* pQuadTree);  

//�Ĳ���������ѯ(���β�ѯ)  
//void SearchQuadTree(QuadNode* node,QPolygonF &queryRect,vector<int>& ItemSearched);  

//�Ĳ����Ĳ�ѯ�����ѯ��  
void PtSearchQTree(QuadNode *node, double cx, double cy, vector<int> &ItemSearched);

//��ָ���Ŀռ������뵽�Ĳ�����  
//void Insert(long key,QPolygonF &itemRect,QuadNode* pNode);  

//��ָ���Ŀռ������뵽�Ĳ�����  
void InsertQuad(long key, QPolygonF &itemRect, QuadNode *pNode);

//��ָ���Ŀռ������뵽�Ĳ�����  
//void InsertQuad2(long key,QPolygonF &itemRect,QuadNode* pNode);  

//�ж�һ���ڵ��Ƿ���Ҷ�ӽڵ�  
bool IsQuadLeaf(QuadNode *node);

//ɾ������Ľڵ�  
bool DelFalseNode(QuadNode *node);

//�Ĳ�������(����Ҫ��)  
void TraversalQuadTree(QuadNode *quadTree, vector<int> &resVec);

//�Ĳ������������нڵ㣩  
void TraversalQuadTree(QuadNode *quadTree, vector<QuadNode *> &arrNode);

//�ͷ������ڴ�ռ�  
void ReleaseQuadTree(QuadNode **quadTree);

//�����Ĳ�����ռ���ֽڵĴ�С  
long CalByteQuadTree(QuadNode *quadTree, long &nSize);


#endif
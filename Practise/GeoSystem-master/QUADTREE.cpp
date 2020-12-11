#include "QUADTREE.h"
#include <assert.h>
#include "geos.h"

QuadNode *InitQuadNode() {
    QuadNode *node = new QuadNode;
    node->Box.setLeft(0);
    node->Box.setRight(0);
    node->Box.setBottom(0);
    node->Box.setTop(0);

    for (int i = 0; i < 4; i++) {
        node->children[i] = NULL;
    }
    node->nChildCount = 0;
    node->nShpCount = 0;
    node->pShapeObj = NULL;

    return node;
}

void CreateQuadTree(int depth, CGeoLayer *poLayer, QuadTree *pQuadTree) {
    pQuadTree->depth = depth;

    QRectF env = poLayer->getRect();

    QRectF rect = env;

    //����������֧
    CreateQuadBranch(depth, rect, &(pQuadTree->root));

    int nCount = poLayer->geoObjects.size();
    if (poLayer->type == 0) {// ��
        QPolygonF Box;    //�ռ����MBR��Χ����
        for (int i = 0; i < nCount; i++) {
            Box = ((CGeoPoint *) poLayer->geoObjects[i])->pts;
            InsertQuad(i, Box, pQuadTree->root);
        }
    } else if (poLayer->type == 1) {// ��
        QPolygonF Box;    //�ռ����MBR��Χ����
        for (int i = 0; i < nCount; i++) {
            Box = ((CGeoPolyline *) poLayer->geoObjects[i])->pts;
            InsertQuad(i, Box, pQuadTree->root);
        }
    } else if (poLayer->type == 2) {// ��
        QPolygonF Box;    //�ռ����MBR��Χ����
        for (int i = 0; i < nCount; i++) {
            Box = ((CGeoPolygon *) poLayer->geoObjects[i])->pts;
            InsertQuad(i, Box, pQuadTree->root);
        }
    }


    //DelFalseNode(pQuadTree->root);
}

void CreateQuadBranch(int depth, QRectF &rect, QuadNode **node) {
    if (depth != 0) {
        *node = InitQuadNode(); //��������
        QuadNode *pNode = *node;
        pNode->Box = rect;
        pNode->nChildCount = 4;

        QRectF boxs[4];
        boxs[UR].setTopRight(pNode->Box.topRight());
        boxs[UR].setBottomLeft(pNode->Box.center());
        boxs[UL].setTopLeft(pNode->Box.topLeft());
        boxs[UL].setBottomRight(pNode->Box.center());
        boxs[LL].setTopRight(pNode->Box.center());
        boxs[LL].setBottomLeft(pNode->Box.bottomLeft());
        boxs[LR].setTopLeft(pNode->Box.center());
        boxs[LR].setBottomRight(pNode->Box.bottomRight());
        for (int i = 0; i < 4; i++) {
            //�����ĸ��ڵ㲢������Ӧ��MBR
            pNode->children[i] = InitQuadNode();
            pNode->children[i]->Box = boxs[i];

            CreateQuadBranch(depth - 1, boxs[i], &(pNode->children[i]));
        }
    }
}
/*
void BuildQuadTree(CGeoLayer *poLayer,QuadTree* pQuadTree)  
{  
assert(poLayer);  
QRectF env = poLayer->getRect();    //����ͼ���MBR  
pQuadTree->root = InitQuadNode();  

QuadNode* rootNode = pQuadTree->root;  

rootNode->Box = env;  

//�����������(   ���ݵȱ����е���͹�ʽ)  
//pQuadTree->depth = log(poLayer->GetFeatureCount()*3/8.0+1)/log(4.0);  
int nCount = poLayer->geoObjects.size();  

QRectF rect;  
for (int i = 0; i < nCount; i ++)  
{  
rect = poLayer->geoObjects[i]->getRect(); 
InsertQuad2(i,rect,rootNode);  
}  

DelFalseNode(pQuadTree->root);  
}  
*/
/*
void SearchQuadTree(QuadNode* node,QRectF &queryRect,vector<int>& ItemSearched)  
{  
assert(node);  

//int coreNum = omp_get_num_procs();  
//vector<int> * pResArr = new vector<int>[coreNum];  

if (NULL != node)  
{  
for (int i = 0; i < node->nShpCount; i ++)  
{  
if (queryRect.contains(node->pShapeObj[i].Box)  
|| queryRect.intersects(node->pShapeObj[i].Box))  
{  
ItemSearched.push_back(node->pShapeObj[i].nID);  
}  
}  

//���������ĸ����ӽڵ�  
/*#pragma omp parallel sections 
{ 
#pragma omp section 
if ((node->children[0] != NULL) &&  
(node->children[0]->Box.Contains(queryRect) 
|| node->children[0]->Box.Intersects(queryRect))) 
{ 
int tid = omp_get_thread_num(); 
SearchQuadTree(node->children[0],queryRect,pResArr[tid]); 
} 

#pragma omp section 
if ((node->children[1] != NULL) &&  
(node->children[1]->Box.Contains(queryRect) 
|| node->children[1]->Box.Intersects(queryRect))) 
{ 
int tid = omp_get_thread_num(); 
SearchQuadTree(node->children[1],queryRect,pResArr[tid]); 
} 

#pragma omp section 
if ((node->children[2] != NULL) &&  
(node->children[2]->Box.Contains(queryRect) 
|| node->children[2]->Box.Intersects(queryRect))) 
{ 
int tid = omp_get_thread_num(); 
SearchQuadTree(node->children[2],queryRect,pResArr[tid]); 
} 

#pragma omp section 
if ((node->children[3] != NULL) &&  
(node->children[3]->Box.Contains(queryRect) 
|| node->children[3]->Box.Intersects(queryRect))) 
{ 
int tid = omp_get_thread_num(); 
SearchQuadTree(node->children[3],queryRect,pResArr[tid]); 
} 
}*/
/*
for (int i = 0; i < 4; i ++)  
{  
if ((node->children[i] != NULL) &&   
(node->children[i]->Box.contains(queryRect)  
|| node->children[i]->Box.intersects(queryRect)))  
{  
SearchQuadTree(node->children[i],queryRect,ItemSearched);  
//node = node->children[i];  //�ǵݹ�  
}  
}  
}  

/*for (int i = 0 ; i < coreNum; i ++) 
{ 
ItemSearched.insert(ItemSearched.end(),pResArr[i].begin(),pResArr[i].end()); 
}*/
/*
}  
*/

void PtSearchQTree(QuadNode *node, double cx, double cy, vector<int> &ItemSearched) {
    assert(node);
    if (node->nShpCount > 0)       //�ڵ�
    {
        for (int i = 0; i < node->nShpCount; i++) {
            /*
            // ����õ�������
            typedef Coordinate PT;
            GeometryFactory factory;
            CoordinateArraySequenceFactory csf; //������һ������p1
            CoordinateSequence* cs1 = csf.create(node->pShapeObj[i].Box.size(),2);//��ά�㣬����ά��zʼ��Ϊ0
            for(int j=0;j<node->pShapeObj[i].Box.size();j++){
                cs1->setAt(PT(node->pShapeObj[i].Box[j].x(),node->pShapeObj[i].Box[j].y()),j);
            }
            LinearRing* ring1 = factory.createLinearRing(cs1); //�㹹����
            Geometry* p1 = factory.createPolygon(ring1,NULL); //�߹�����
            Geometry *p2 = factory.createPoint(PT(cx,cy));
            */
            if (node->pShapeObj[i].Box.containsPoint(QPointF(cx, cy), Qt::OddEvenFill)) {
                ItemSearched.push_back(node->pShapeObj[i].nID);
                return;
            }
        }
    }

    if (node->nChildCount > 0)                //�ڵ�
    {
        for (int i = 0; i < 4; i++) {
            if (node->children[i]->Box.contains(QPointF(cx, cy))) {
                PtSearchQTree(node->children[i], cx, cy, ItemSearched);
            }
        }
    }

}

/*
void Insert(long key, QRectF &itemRect,QuadNode* pNode)  
{  
QuadNode *node = pNode;     //�������ڵ㸱��  
SHPMBRInfo pShpInfo;  

//�ڵ��к���  
if (0 < node->nChildCount)  
{  
for (int i = 0; i < 4; i ++)  
{    
//����������ཻ���򽫽ڵ���뵽�˽ڵ�  
if (node->children[i]->Box.contains(itemRect)  
|| node->children[i]->Box.intersects(itemRect))  
{  
//node = node->children[i];  
Insert(key,itemRect,node->children[i]);  
}  
}  
}  

//�����ǰ�ڵ����һ���ӽڵ�ʱ  
else if (1 == node->nShpCount)  
{  
QRectF boxs[4];  

boxs[UR].setTopRight(node->Box.topRight());
boxs[UR].setBottomLeft(node->Box.center());
boxs[UL].setTopLeft(node->Box.topLeft());
boxs[UL].setBottomRight(node->Box.center());
boxs[LL].setTopRight(node->Box.center());
boxs[LL].setBottomLeft(node->Box.bottomLeft());
boxs[LR].setTopLeft(node->Box.center());
boxs[LR].setBottomRight(node->Box.bottomRight());
//�����ĸ��ڵ㲢������Ӧ��MBR  
node->children[UR] = InitQuadNode();  
node->children[UL] = InitQuadNode();  
node->children[LL] = InitQuadNode();  
node->children[LR] = InitQuadNode();  

node->children[UR]->Box = boxs[0];  
node->children[UL]->Box = boxs[1];  
node->children[LL]->Box = boxs[2];  
node->children[LR]->Box = boxs[3];  
node->nChildCount = 4;  

for (int i = 0; i < 4; i ++)  
{    
//����ǰ�ڵ��е�Ҫ���ƶ�����Ӧ���ӽڵ���  
for (int j = 0; j < node->nShpCount; j ++)  
{  
if (node->children[i]->Box.contains(node->pShapeObj[j].Box)  
|| node->children[i]->Box.intersects(node->pShapeObj[j].Box))  
{  
node->children[i]->nShpCount += 1;  
node->children[i]->pShapeObj =   
(SHPMBRInfo*)malloc(node->children[i]->nShpCount*sizeof(SHPMBRInfo));  

memcpy(node->children[i]->pShapeObj,&(node->pShapeObj[j]),sizeof(SHPMBRInfo));  

free(node->pShapeObj);  
node->pShapeObj = NULL;  
node->nShpCount = 0;  
}  
}  
}  

for (int i = 0; i < 4; i ++)  
{    
//����������ཻ���򽫽ڵ���뵽�˽ڵ�  
if (node->children[i]->Box.contains(itemRect)  
|| node->children[i]->Box.intersects(itemRect))  
{  
if (node->children[i]->nShpCount == 0)     //���֮ǰû�нڵ�  
{  
node->children[i]->nShpCount += 1;  
node->pShapeObj =   
(SHPMBRInfo*)malloc(sizeof(SHPMBRInfo)*node->children[i]->nShpCount);  
}  
else if (node->children[i]->nShpCount > 0)  
{  
node->children[i]->nShpCount += 1;  
node->children[i]->pShapeObj =   
(SHPMBRInfo *)realloc(node->children[i]->pShapeObj,  
sizeof(SHPMBRInfo)*node->children[i]->nShpCount);  
}  

pShpInfo.Box = itemRect;  
pShpInfo.nID = key;  
memcpy(node->children[i]->pShapeObj,  
&pShpInfo,sizeof(SHPMBRInfo));  
}  
}  
}  

//��ǰ�ڵ�û�пռ����  
else if (0 == node->nShpCount)  
{  
node->nShpCount += 1;  
node->pShapeObj =   
(SHPMBRInfo*)malloc(sizeof(SHPMBRInfo)*node->nShpCount);  

pShpInfo.Box = itemRect;  
pShpInfo.nID = key;  
memcpy(node->pShapeObj,&pShpInfo,sizeof(SHPMBRInfo));  
}  
}  
*/

void InsertQuad(long key, QPolygonF &itemRect, QuadNode *pNode) {
    assert(pNode != NULL);

    if (!IsQuadLeaf(pNode))    //��Ҷ�ӽڵ�
    {
        int nCorver = 0;        //��Խ���ӽڵ����
        int iIndex = -1;        //���ĸ��ӽڵ���ȫ������������
        for (int i = 0; i < 4; i++) {
            QRectF rect = itemRect.boundingRect();
            if (pNode->children[i]->Box.contains(itemRect.boundingRect())
                && pNode->Box.contains(itemRect.boundingRect())) {
                nCorver += 1;
                iIndex = i;
            }
        }

        //�����ĳһ���ӽڵ�������������ӽڵ�
        if (/*pNode->Box.Contains(itemRect) ||
			pNode->Box.Intersects(itemRect)*/1 <= nCorver) {
            InsertQuad(key, itemRect, pNode->children[iIndex]);
        }

            //�����Խ�˶���ӽڵ㣬ֱ�ӷ�������ڵ���
        else if (nCorver == 0) {
            if (pNode->nShpCount == 0)    //���֮ǰû�нڵ�
            {
                pNode->nShpCount += 1;
                pNode->pShapeObj =
                        (SHPMBRInfo *) malloc(sizeof(SHPMBRInfo) * pNode->nShpCount);
            } else {
                pNode->nShpCount += 1;
                pNode->pShapeObj =
                        (SHPMBRInfo *) realloc(pNode->pShapeObj, sizeof(SHPMBRInfo) * pNode->nShpCount);
            }

            SHPMBRInfo pShpInfo;
            pShpInfo.Box = itemRect;
            pShpInfo.nID = key;
            memcpy(pNode->pShapeObj + pNode->nShpCount - 1, &pShpInfo, sizeof(SHPMBRInfo));
        }
    }

        //�����Ҷ�ӽڵ㣬ֱ�ӷŽ�ȥ
    else if (IsQuadLeaf(pNode)) {
        if (pNode->nShpCount == 0)    //���֮ǰû�нڵ�
        {
            pNode->nShpCount += 1;
            pNode->pShapeObj =
                    (SHPMBRInfo *) malloc(sizeof(SHPMBRInfo) * pNode->nShpCount);
        } else {
            pNode->nShpCount += 1;
            pNode->pShapeObj =
                    (SHPMBRInfo *) realloc(pNode->pShapeObj, sizeof(SHPMBRInfo) * pNode->nShpCount);
        }

        SHPMBRInfo pShpInfo;
        pShpInfo.Box = itemRect;
        pShpInfo.nID = key;
        memcpy(pNode->pShapeObj + pNode->nShpCount - 1, &pShpInfo, sizeof(SHPMBRInfo));
    }
}
/*
void InsertQuad2(long key,QRectF &itemRect,QuadNode* pNode)  
{  
QuadNode *node = pNode;     //�������ڵ㸱��  
SHPMBRInfo pShpInfo;  

//�ڵ��к���  
if (0 < node->nChildCount)  
{  
for (int i = 0; i < 4; i ++)  
{    
//����������ཻ���򽫽ڵ���뵽�˽ڵ�  
if (node->children[i]->Box.contains(itemRect)  
|| node->children[i]->Box.contains(itemRect))  
{  
//node = node->children[i];  
Insert(key,itemRect,node->children[i]);  
}  
}  
}  

//�����ǰ�ڵ����һ���ӽڵ�ʱ  
else if (0 == node->nChildCount)  
{  
QRectF boxs[4];  
boxs[UR].setTopRight(node->Box.topRight());
boxs[UR].setBottomLeft(node->Box.center());
boxs[UL].setTopLeft(node->Box.topLeft());
boxs[UL].setBottomRight(node->Box.center());
boxs[LL].setTopRight(node->Box.center());
boxs[LL].setBottomLeft(node->Box.bottomLeft());
boxs[LR].setTopLeft(node->Box.center());
boxs[LR].setBottomRight(node->Box.bottomRight());
int cnt = -1;  
for (int i = 0; i < 4; i ++)  
{    
//����������ཻ���򽫽ڵ���뵽�˽ڵ�  
if (boxs[i].contains(itemRect))  
{  
cnt = i;  
}  
}  

//�����һ�����ΰ����˶����򴴽��ĸ����ӽڵ�  
if (cnt > -1)  
{  
for (int i = 0; i < 4; i ++)  
{  
//�����ĸ��ڵ㲢������Ӧ��MBR  
node->children[i] = InitQuadNode();  
node->children[i]->Box = boxs[i];  
}  
node->nChildCount = 4;  
InsertQuad2(key,itemRect,node->children[cnt]);   //�ݹ�  
}  

//���������������ֱ�ӽ��������˽ڵ�  
if (cnt == -1)  
{  
if (node->nShpCount == 0)     //���֮ǰû�нڵ�  
{  
node->nShpCount += 1;  
node->pShapeObj =   
(SHPMBRInfo*)malloc(sizeof(SHPMBRInfo)*node->nShpCount);  
}  
else if (node->nShpCount > 0)  
{  
node->nShpCount += 1;  
node->pShapeObj =   
(SHPMBRInfo *)realloc(node->pShapeObj,  
sizeof(SHPMBRInfo)*node->nShpCount);  
}  

pShpInfo.Box = itemRect;  
pShpInfo.nID = key;  
memcpy(node->pShapeObj,  
&pShpInfo,sizeof(SHPMBRInfo));  
}  
}  
*/
//��ǰ�ڵ�û�пռ����  
/*else if (0 == node->nShpCount) 
{ 
node->nShpCount += 1; 
node->pShapeObj =  
(SHPMBRInfo*)malloc(sizeof(SHPMBRInfo)*node->nShpCount); 

pShpInfo.Box = itemRect; 
pShpInfo.nID = key; 
memcpy(node->pShapeObj,&pShpInfo,sizeof(SHPMBRInfo)); 
}*/
/*
}  
*/
bool IsQuadLeaf(QuadNode *node) {
    if (NULL == node) {
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        if (node->children[i] != NULL) {
            return 0;
        }
    }

    return 1;
}

bool DelFalseNode(QuadNode *node) {
    //���û���ӽڵ���û��Ҫ��
    if (node->nChildCount == 0 && node->nShpCount == 0) {
        ReleaseQuadTree(&node);
    }

        //������ӽڵ�
    else if (node->nChildCount > 0) {
        for (int i = 0; i < 4; i++) {
            DelFalseNode(node->children[i]);
        }
    }

    return 1;
}

void TraversalQuadTree(QuadNode *quadTree, vector<int> &resVec) {
    QuadNode *node = quadTree;
    int i = 0;
    if (NULL != node) {
        //�����ڵ��еĿռ����洢������
        for (i = 0; i < node->nShpCount; i++) {
            resVec.push_back((node->pShapeObj + i)->nID);
        }

        //�������ӽڵ�
        for (i = 0; i < node->nChildCount; i++) {
            if (node->children[i] != NULL) {
                TraversalQuadTree(node->children[i], resVec);
            }
        }
    }

}

void TraversalQuadTree(QuadNode *quadTree, vector<QuadNode *> &arrNode) {
    deque<QuadNode *> nodeQueue;
    if (quadTree != NULL) {
        nodeQueue.push_back(quadTree);
        while (!nodeQueue.empty()) {
            QuadNode *queueHead = nodeQueue.at(0);  //ȡ����ͷ���
            arrNode.push_back(queueHead);
            nodeQueue.pop_front();
            for (int i = 0; i < 4; i++) {
                if (queueHead->children[i] != NULL) {
                    nodeQueue.push_back(queueHead->children[i]);
                }
            }
        }
    }
}

void ReleaseQuadTree(QuadNode **quadTree) {
    int i = 0;
    QuadNode *node = *quadTree;
    if (NULL == node) {
        return;
    } else {
        for (i = 0; i < 4; i++) {
            ReleaseQuadTree(&node->children[i]);
        }
        free(node);
        node = NULL;
    }

    node = NULL;
}

long CalByteQuadTree(QuadNode *quadTree, long &nSize) {
    if (quadTree != NULL) {
        nSize += sizeof(QuadNode) + quadTree->nChildCount * sizeof(SHPMBRInfo);
        for (int i = 0; i < 4; i++) {
            if (quadTree->children[i] != NULL) {
                nSize += CalByteQuadTree(quadTree->children[i], nSize);
            }
        }
    }

    return 1;
}
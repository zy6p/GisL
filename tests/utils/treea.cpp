#include <stdio.h>

#include <stdlib.h>
#include <string.h>
//#include<conio.h>

typedef struct CityInfo {
  int id;
  char cityName[50];
  char cityPinyin[50];
  float x, y;
} CITYINFO;

typedef struct LinkcityNode {
  CITYINFO city;
  struct LinkcityNode* next;
} L_CITYNODE; //链表

typedef struct TreeCityNode {
  CITYINFO city;
  struct TreeCityNode* left;
  struct TreeCityNode* right;
} T_CITYNODE; //树

void Initiate(T_CITYNODE** root)
//初始化建立二叉树的头结点
{
  *root = new T_CITYNODE;
  (*root)->left = NULL;
  (*root)->right = NULL;
}

//左插入结点
T_CITYNODE* InsertLeftNode(T_CITYNODE* curr, T_CITYNODE x) {
  T_CITYNODE *s, *t;
  if (curr == NULL)
    return NULL;
  t = curr->left;
  s = new T_CITYNODE;
  s->city = x.city;
  s->left = t;
  s->right = NULL;
  curr->left = s;
  return curr->left;
}

//右插入结点
T_CITYNODE* InsertRightNode(T_CITYNODE* curr, T_CITYNODE x) {
  T_CITYNODE *s, *t;
  if (curr == NULL)
    return NULL;
  t = curr->right;
  s = new T_CITYNODE;
  s->city = x.city;
  s->right = t;
  s->left = NULL;
  curr->right = s;
  return curr->left;
}

//添加结点
void InsertTreeNode(T_CITYNODE** rt, T_CITYNODE* node) {
  if (*rt == NULL)
  //创建内存结点，并初始化为根节点
  {
    *rt = node;
    return;
  }

  if (strcmp((*rt)->city.cityName, node->city.cityName) >= 0)
    InsertTreeNode(&((*rt)->left), node);
  else
    InsertTreeNode(&((*rt)->right), node);
  printf(
      "城市信息为：%d,%s(%0.2f,%0.2f)\n",
      (*rt)->city.id,
      (*rt)->city.cityName,
      (*rt)->city.x,
      (*rt)->city.y);
}

void AddCityToTree(T_CITYNODE** node) {
  FILE* fp = fopen("../tests/a.txt", "r");
  if (fp == NULL) {
    printf("open file error!");
    return;
  }
  int idx = 0;
  while (!feof(fp) && idx < 5) {

    idx++;
    T_CITYNODE* cn;
    cn = new T_CITYNODE;
    if (cn == NULL) {
      printf("指针分配失败！");
      return;
    }

    fscanf(
        fp,
        "%d%f%f%s",
        &cn->city.id,
        &cn->city.x,
        &cn->city.y,
        cn->city.cityName);
    cn->left = NULL;
    cn->right = NULL;
    if (*node == NULL)
      *node = cn;
    else
      InsertTreeNode(node, cn);
  }
  fclose(fp);
}

//前序遍历结点
void preTreeNode(T_CITYNODE** rt) {
  if (*rt == NULL)
    return;
  printf(
      "城市信息为：%d\t%s(%.2f,%.2f)\n",
      (*rt)->city.id,
      (*rt)->city.cityName,
      (*rt)->city.x,
      (*rt)->city.y);
  preTreeNode(&((*rt)->left));
  preTreeNode(&((*rt)->right));
}

//中序遍历结点
void midTreeNode(T_CITYNODE** rt) {
  if (*rt == NULL)
    return;
  midTreeNode(&((*rt)->left));
  printf(
      "城市信息为：%d\t%s(%.2f,%.2f)\n",
      (*rt)->city.id,
      (*rt)->city.cityName,
      (*rt)->city.x,
      (*rt)->city.y);
  midTreeNode(&((*rt)->right));
}

//后序遍历结点
void aftTreeNode(T_CITYNODE** rt) {
  if (*rt == NULL)
    return;
  aftTreeNode(&((*rt)->left));
  aftTreeNode(&((*rt)->right));
  printf(
      "城市信息为：%d\t%s(%.2f,%.2f)\n",
      (*rt)->city.id,
      (*rt)->city.cityName,
      (*rt)->city.x,
      (*rt)->city.y);
}

int main(int argc, char* argv[]) {
  // 1.构建树
  // 2.遍历（前序，中序，后序）
  // 3.删除or插入某个节点
  // 4.（霍夫曼编码）
  // 5.删除整个树
  T_CITYNODE* root = NULL;
  AddCityToTree(&root);
  printf("**********输出二叉树中信息为：前序遍历*************\n");
  preTreeNode(&root);
  //    getch();
  printf("**********输出二叉树中信息为：中序遍历*************\n");
  midTreeNode(&root);
  //    getch();
  printf("**********输出二叉树中信息为：后序遍历*************\n");
  aftTreeNode(&root);

  return 0;
}

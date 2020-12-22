//#include "stdafx.h"
#include<stdlib.h>
#include<stdio.h>

using namespace std;
typedef struct Point {
    float x, y;
} POINT;

typedef struct cityinfo {
    int id;
    POINT pt;
    char name[100];
    struct cityinfo *next;
} CityLink;


int main(int argc, char *argv[]) {
    printf("Hello World!\n");
    CityLink *hd, *rear, *link;
    hd = rear = link = NULL;
    FILE *fp = fopen("../tests/a.txt", "r");
    if (fp == NULL) {
        printf("矢量数据文件打开有误！");
        exit;
    } else
        while (!feof(fp)) {
            link = ((CityLink *) malloc(sizeof(CityLink)));
            fscanf(fp, "%d%f%f%s", &link->id, &link->pt.x, &link->pt.y, link->name);

            if (hd == NULL) {
                hd = link;
                rear = link;
                continue;
            }
            if (hd == rear) {
                rear = link;
                hd->next = rear;
            } else {
                rear->next = link;
                rear = link;
            }
            printf("%d %f %f %s\n", link->id, link->pt.x, link->pt.y, link->name);
        }
    if (rear != NULL)
        rear->next = NULL;

    fclose(fp);
    free(hd);

    return 0;
}


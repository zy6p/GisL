#include<string.h>
//#include<conio.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct CityInfo {
    int id;
    char cityName[50];
    char cityPinyin[50];
    float x, y;
} CITYINFO;

typedef struct LinkcityNode {
    CITYINFO city;
    struct LinkcityNode *next;
} L_CITYNODE;//链表

typedef struct TreeCityNode {
    CITYINFO city;
    struct TreeCityNode *left;
    struct TreeCityNode *right;
} T_CITYNODE;//树

void readFileToArray(CITYINFO cities[], int *size) {
    FILE *fp = fopen("../tests/a.txt", "r");
    if (fp == NULL) {
        printf("open file error!");
        return;
    }
    int idx = 0;
    while (!feof(fp)) {
        char *a = cities[idx].cityName;
        fscanf(fp, "%d%f%f%s", &cities[idx].id, &cities[idx].x, &cities[idx].y, a);
//        fscanf(fp, "%d%f%f%s", &cn->city.id, &cn->city.x, &cn->city.y, cn->city.cityName);

        idx++;
    }
    *size = idx;
    fclose(fp);
}


//***************排序***************
void outputCities(CITYINFO cities[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d\t%s(%.2f,%.2f)\n", cities[i].id, cities[i].cityName, cities[i].x, cities[i].y);
}

//选择法排序
void sort_Select(CITYINFO cities[], int size) {
    int i, j, idx;
    CITYINFO info1;
    for (i = 0; i < size - 1; i++) {
        idx = i;
        for (j = i + 1; j < size; j++) {
            if (strcmp(cities[idx].cityName, cities[j].cityName) > 0)
                idx = j;
        }
        //交换结构体对应数据

        info1 = cities[i];
        cities[i] = cities[idx];
        cities[idx] = info1;

    }
}

//直接插入排序
void sort_Insert(CITYINFO cities[], int size) {
    int i, j;
    CITYINFO temp;
    for (i = 0; i < size - 1; i++) {
        temp = cities[i + 1];
        j = i;
        while (j > -1 && (strcmp(temp.cityName, cities[j].cityName) < 0)) {
            cities[j + 1] = cities[j];
            j--;
        }
        cities[j + 1] = temp;
    }
}

//冒泡法排序
void sort_Bubble(CITYINFO cities[], int size) {
    int i, j;
    CITYINFO temp;
    int flag = 0;
    for (i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (strcmp(cities[i].cityName, cities[j].cityName) > 0) {
                temp = cities[i];
                cities[i] = cities[j];
                cities[j] = temp;
                flag = 1;
            }
        }
        if (!flag)
            break;
    }
}


int main(int argc, char *argv[]) {
    int size;
    CITYINFO cities[100];
    readFileToArray(cities, &size);
    printf("*****数组排序，原始输出结果：***********\n");
    outputCities(cities, 5);
//    getch();
    printf("*****数组排序，选择法排序后输出结果：***********\n");
    sort_Select(cities, 5);
    outputCities(cities, 5);
//    getch();
    printf("*****数组排序，直接插入排序后输出结果：***********\n");
    sort_Insert(cities, 5);
    outputCities(cities, 5);
//    getch();
    printf("*****数组排序，冒泡法排序后输出结果：***********\n");
    sort_Bubble(cities, 5);
    outputCities(cities, 5);
//    getch();
    return 0;
}


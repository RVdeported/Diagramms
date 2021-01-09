#include <stdlib.h>
#include <stdio.h>
#include <math.h>


void showInt(int *test){
    for (int x= 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            printf("%d", *(test + (x*3) + y));
        }
        printf("\n");
    }
}
void initArr(int *test){
    printf("Begin\n");
        for (int x= 0; x < 3; ++x)
            {
        for (int y = 0; y < 3; ++y)
            {
                *(test + (y*3) + x) = x + y;
            }
    }
}



void fillRandom(long *arr, int lengh, int border){
    for (int i = 0; i < lengh; ++i){
        *(arr + i) = (rand() * rand()) % border;
    }
}

void bubbleSort(int *arr, int len){
    for (int i = 0; i < len-1; i++){
        //printf("Trying: %d\n",i);
        if (*(arr + i) < *(arr + i + 1)){
            swap(arr, i, i + 1);
            i = -1;
        }
    }
}

void swap (int *arr, int from, int to){
    int buff = *(arr + from);
    *(arr + from) = *(arr + to);
    *(arr + to) = buff;
}

void printArr(int *arr, int len, int maxx){
    if (len > maxx)
        len = maxx;
    for (int i = 0; i < len ; ++i){
        printf("%4d ", *(arr + i));
        if (i%10 == 9)
            printf("\n");
    }
    printf("\n----------------------\n");
}

void insertSort(int *arr, int len){
    for (int i = 1; i < len; i++)
    {
        int buff = *(arr + i);
        for (int t = 0; t < i; t++){
            if (buff > *(arr + t)){
                for (int n = i; n > t; n--)
                    *(arr + n) = *(arr + n - 1);
                *(arr + t) = buff;
                break;
            }
        }
    }
}

void QuickSort(long *arr, int len, int min, int globLen){
    //printf("Input Arr: ");
   // printArr(arr, len,100);
    if (len <= min)
    {
        insertSort(arr, len);
        return;
    }
    int border = *(arr + rand()%(len));
    int id1 = 0;
    int id2 = 0;
    for (int i = 0; i < len; i++)
    {
        if (*(arr + i) != border)
            break;
        else if (i == len -1)
            return;
    }
    for (int i = 0; i < len; i++){
        if (*(arr + i) > border)
        {
            *(arr + id1) = *(arr + i);
            id1++;
        }
        else
        {
            *(arr + globLen + id2) = *(arr + i);
            id2++;
        }
    }
    for (int i = 0; i < id2; i++)
        *(arr + id1 + i) = *(arr + globLen + i);
    //printArr(arr, id1, 200);
    //printArr(arr + globLen, id2, 200);
    //printArr(arr, len, 200);
    //printf("======================\n");
    QuickSort(arr, id1, min, globLen);
    //printf("Second pair\n");
    QuickSort(arr + id1, id2, min, globLen);
    /*
    for (int i = 0; i < id1; i++)
        *(arr + i) = arr1[i];
    for (int i = 0; i < id2; i++)
        *(arr + id1 + i) = arr2[i];
        */
}
/*
int main(){
    int SIZE = 10000000;
    static long arr[20000000];
    fillRandom(&arr, SIZE, 2550000);
    printArr(&arr, SIZE, 100);
    QuickSort(&arr, SIZE, 2, SIZE);
    printArr(&arr, SIZE, 100);
    int t = 50;
}
*/

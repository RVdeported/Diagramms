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

void swapInt (int *from, int *to){
    int buff = *from;
    *from = *to;
    *to = buff;
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

void QuickSortWithHoupAndBlocks(long *arr, int len, int min){
    if (len <= min) // if there just few numbers left, do other type of sort
    {
        insertSort(arr, len);
        return;
    }
    int border = *(arr + rand()%(len)); //selecting random border
    int id1 = 0; // left-side indicator
    int id2 = len - 1; // right-side indicator
    int id3 = 0; // indicator of storage with nums == border
    for (int i = 0; i < len; i++) // storing numbers equal to border to left side of the arr
        if (*(arr + i) == border)
            swapInt((arr + i), (arr + id3++));

    for (id1 = id3; id1 != id2 + 1;) // as elements [0:id3] booked with nums == border, begin sort with id3
        if (*(arr + id1) > border)
            swapInt((arr + id1), (arr + id2--));
        else
            id1++; // element is already on required side

    for(int i = 0; i < id3; i++) // putting nums == border to the middle of arr
        if (*(arr + i) !=  *(arr + id1 - i - 1))
            swapInt((arr + i), (arr + id1 - i - 1)); // the loop lines can be replace by this one, but in many cases this variant is faster
        else
            break;

    QuickSortWithHoupAndBlocks(arr, id1 - id3, min); // id1 - id3 is lengh of left-side (without nums == border)
    QuickSortWithHoupAndBlocks(arr + id1, len - id1, min);
}

void count_sort_pineapple (int *arr, int len, int const max)
{
    int min = find_min(arr, &len);
    int counts[max - min + 1];
    for (int i = min; i < max; i++)
        counts[i - min] = 0;
    for (int i = 0; i < len; i++)
        counts[*(arr + i)]++;
    int ind = 0;
    for (int i = 0; i < max; i++)
        while (counts[i] > 0)
        {
            *(arr + ind++) = i + min;
            counts[i]--;
        }
}

void block_sort(int *arr, int len){
    int b = 10;
    int baskets[b][len + 1];
    for(int i = 0; i < b; i++)
        baskets[i][len] = 0;
    for (int d = 1; d < 1000000; d *= 10)
    {
        for ( int i = 0; i < len; i++)
        {
            int bask = (*(arr + i) / d) % b;
            baskets[bask][baskets[bask][len]++] = *(arr + i);
        }
        int ind = 0;
        for (int i = 0; i < b; i++)
        {
            for (int t = 0; t < baskets[i][len]; t++)
                *(arr + ind++) = baskets[i][t];
            baskets[i][len] = 0;
        }
    }
}

int sumArr(int *arr, int len)
{
    int res = 0;
    for( int i = 0; i < len; i++)
        res += *(arr + i);
    return res;
}

int find_min(int *arr, int *len)
{
    int min = *arr;
    for(int i = 1; i < *len; i++)
        if (*(arr + i) < min)
            min = *(arr + i);
    return min;
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

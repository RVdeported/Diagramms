#include <stdio.h>
#include <stdlib.h>

//-----------------------Part 1-----------------//
void bubbleSortMult(int *arr, int len1, int len2){
    bubbleSort(arr, len1*len2);
}

//-----------------------Part 2-----------------//
void Trabb_Prado_Knutt(int *arr, int len){
    for (int i = 0; i < len; i++){
            int X = *(arr + i);
            int score = sqrt(fabs(X)) + 5 * pow(X, 3);
        if ( score > 400)
            printf("The number %d with index %d scored %d\n",X,i,score);
    }
}

//----------------------------Utilities---------//
void swap (int *from, int *to){
    int buff = *(from);
    *(from) = *(to);
    *(to) = buff;
}

void printArr(int *arr, int len, int maxx, int pack){
    if (len > maxx)
        len = maxx;
    for (int i = 0; i < len ; ++i){
        printf("%5d ", *(arr + i));
        if ((i+1)%pack == 0)
            printf("\n");
    }
    printf("\n----------------------\n");
}

void fillRandom(long *arr, int lengh, int border){
    for (int i = 0; i < lengh; ++i){
        *(arr + i) = (rand() * rand()) % border;
    }
}

void invertArr(int *arr, int len){
    int temp[len];
    for (int i = 0; i < len; i++)
        temp[i] = *(arr + len - i - 1);
    for (int i = 0; i < len; i++)
        *(arr + i) = temp[i];
}

void bubbleSort(int *arr, int len){
    for (int i = 0; i < len-1; i++){
        if (*(arr + i) > *(arr + i + 1)){
            swap((arr + i), (arr + i + 1));
            i = -1;
        }
    }
}
int main(){
    int x = 3;
    int y = 3;
    static int arr_m[3][3] = {{1,2,3},{5,3,2},{9,3,5}};
    //---------------------Part 1--------------------//
    int SIZE = 50;
    static long arr[50];
    fillRandom(&arr, SIZE, 100);
    printf("Initial arr to sort:\n");
    printArr(&arr_m, x*y, 100, x);
    bubbleSortMult(&arr_m, x, y);
    printf("Result of bubble sort: \n");
    printArr(&arr_m, x*y, 100, x);
    //---------------------Part 2--------------------//
    printf("Please, enter 11 numbers [i didn't programmed cases with more or less nums, sorry]\n");
    SIZE = 11;
    static int arr_Trabb[11];
    for (int i = 0; i < SIZE; i++)
        scanf("%d", &arr_Trabb[i]);
    printf("Entered arr:\n");
    printArr(&arr_Trabb, SIZE,100, 10);
    bubbleSort(&arr_Trabb,SIZE);
    printf("Result of bubble sort: \n");
    printArr(&arr_Trabb, SIZE, 100, 10);
    printf("inverted arr:\n");
    invertArr(&arr_Trabb, SIZE);
    printArr(&arr_Trabb, SIZE, 100, 10);
    Trabb_Prado_Knutt(&arr_Trabb, SIZE);
}

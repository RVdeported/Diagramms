#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *arr, int len){
    for (int i = 0; i < len-1; i++){
        if (*(arr + i) > *(arr + i + 1)){
            swap((arr + i), (arr + i + 1));
            i = -1;
        }
    }
}

void swap (int *from, int *to){
    int buff = *(from);
    *(from) = *(to);
    *(to) = buff;
}

void printArr(int *arr, int len, int maxx){
    if (len > maxx)
        len = maxx;
    for (int i = 0; i < len ; ++i){
        printf("%5d ", *(arr + i));
        if (i%10 == 9)
            printf("\n");
    }
    printf("\n----------------------\n");
}

void fillRandom(long *arr, int lengh, int border){
    for (int i = 0; i < lengh; ++i){
        *(arr + i) = (rand() * rand()) % border;
    }
}


void Trabb_Prado_Knutt(int *arr, int len){
    for (int i = 0; i < len; i++){
            int X = *(arr + i);
            int score = sqrt(fabs(X)) + 5 * pow(X, 3);
        if ( score > 400)
            printf("The number %d with index %d scored %d\n",X,i,score);
    }
}

void invertArr(int *arr, int len){
    int temp[len];
    for (int i = 0; i < len; i++)
        temp[i] = *(arr + len - i - 1);
    for (int i = 0; i < len; i++)
        *(arr + i) = temp[i];
}

int main(){
    int SIZE = 50;
    static long arr[50];
    fillRandom(&arr, SIZE, 100);
    printf("Initial arr to sort:\n");
    printArr(&arr, SIZE, 100);
    bubbleSort(&arr, SIZE);
    printf("Result of bubble sort: \n");
    printArr(&arr, SIZE, 100);

    printf("Please, enter 11 numbers [i didn't programmed cases with more or less nums, sorry]\n");
    SIZE = 11;
    static int arr_Trabb[11];
    for (int i = 0; i < SIZE; i++)
        scanf("%d", &arr_Trabb[i]);
    printf("Entered arr:\n");
    printArr(&arr_Trabb, SIZE,100);
    bubbleSort(&arr_Trabb,SIZE);
    printf("Result of bubble sort: \n");
    printArr(&arr_Trabb, SIZE, 100);
    printf("inverted arr:\n");
    invertArr(&arr_Trabb, SIZE);
    printArr(&arr_Trabb, SIZE, 100);
    Trabb_Prado_Knutt(&arr_Trabb, SIZE);
}

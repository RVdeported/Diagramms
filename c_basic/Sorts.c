#include "./Arrays.c"
#include <stdio.h>






int main()
{
    int SIZE = 50;
    int MAX = 500;
    static int arr[200];
    fillRandom(&arr, SIZE, MAX);
    printArr(&arr, SIZE, 100);
    block_sort(&arr, SIZE);
    printArr(&arr, SIZE, 100);
}

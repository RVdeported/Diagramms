#include "./Arrays.c"
#include <stdio.h>

int find_min(int *arr, int *len)
{
    int min = *arr;
    for(int i = 1; i < *len; i++)
        if (*(arr + i) < min)
            min = *(arr + i);
    return min;
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

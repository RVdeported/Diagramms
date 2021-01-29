#include <stdio.h>

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

void block_sort(int *arr, int len){
    int b = 10;
    int baskets[b][len + 1];
    for(int i = 0; i < b; i++) // initializing bakets count
        baskets[i][len] = 0;
    for (int d = 1; d < 1000000; d *= 10)
    {
        for ( int i = 0; i < len; i++)
        {
            int bask = (*(arr + i) / d) % b;
            if (*(arr + i) % 2 == 0) // record only even numbers
                baskets[bask][baskets[bask][len]++] = *(arr + i);
        }
        int ind = 0;
        for (int i = 0; i < b; i++)
        {
            for (int t = 0; t < baskets[i][len]; t++)
            {
                if (*(arr + ind) % 2 == 0) // if the element is not even => try another element
                    *(arr + ind) = baskets[i][t];
                else
                    t--;
                ind++;
            }
            baskets[i][len] = 0;
        }
    }
}

//------------------------Utilities------------------------//
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

void swapInt (int *from, int *to){
    int buff = *from;
    *from = *to;
    *to = buff;
}

void fillRandom(long *arr, int lengh, int border){
    for (int i = 0; i < lengh; ++i){
        *(arr + i) = (rand() * rand()) % border;
    }
}

void insertSort(int *arr, int len){
    for (int i = 1; i < len; i++)
    {
        int buff = *(arr + i);
        for (int t = 0; t < i; t++){
            if (buff < *(arr + t)){
                for (int n = i; n > t; n--)
                    *(arr + n) = *(arr + n - 1);
                *(arr + t) = buff;
                break;
            }
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
//-------------------------------------------------------//

int main()
{
    int SIZE = 50;
    int MIN = 5; // minimum size to perform QuickSort. Other times it will be another sort method [see QuickSort function]
    static int arr[200]; // arr size should be more or equal to SIZE
    fillRandom(&arr, SIZE, 20);
    int checkSum = sumArr(&arr, SIZE);
    printf("Initial array:\n");
    printArr(&arr, SIZE, SIZE);
    QuickSortWithHoupAndBlocks(&arr, SIZE, 5);
    printf("Sorted with Upgraded Quick Sort:\n");
    printArr(&arr, SIZE, SIZE);
    printf("CheckSum is %d\n", checkSum - sumArr(&arr, SIZE));

    fillRandom(&arr, SIZE, 20);
    checkSum = sumArr(&arr, SIZE);
    printf("Initial array #2:\n");
    printArr(&arr, SIZE, SIZE);
    block_sort(&arr, SIZE);
    printf("Sorted with Even Block Sorter:\n");
    printArr(&arr, SIZE, SIZE);
    printf("CheckSum is %d\n", checkSum - sumArr(&arr, SIZE));
}

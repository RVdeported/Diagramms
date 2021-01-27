#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;


int SquareErr(int* X, int* Y, int len)
{
    int res = 0;
    for (int i = 0 ; i < len; i++){
        res += abs(X[i] - Y[i]);
        //printf("%d %d %d %d\n",abs(X[i] - Y[i]), X[i], Y[i], X[i] - Y[i]);
    }

    return res;
}

int MedianErr(int *X, int *Y, int len)
{
    int res = 0;
    for (int i = 0 ; i < len ; i++)
        res += X[i] - Y[i];
    return res;
}

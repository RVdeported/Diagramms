#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unordered_set>
#include <set>


using namespace std;


int SquareErr(int** data, int X, int Y, int len)
{
    int res = 0;
    for (int i = 1 ; i < len + 1; i++){
        res += abs(data[i][X] - data[i][Y]);
        //printf("%d %d %d %d\n",data[i][X]);
    }

    return res;
}

int MedianErr(int** data, int X, int Y, int len)
{
    int res = 0;
    for (int i = 1 ; i < len + 1; i++)
        res += data[i][X] - data[i][Y];
    return res;
}

int** ConfusionMatrix(int** data, int Y, int Ypred, int len, bool print = true)
{
    set<int> vals;
    for (int i = 1 ; i < len + 1 ; i++)
        vals.insert(data[i][Y]);
    set<int> :: iterator itr;
    int** matrix = new int*[vals.size()];
    for (int i = 0 ; i < vals.size(); i++)
        matrix[i] = (int*)calloc(vals.size(),sizeof(int));
    for (int i = 0; i < vals.size(); i++)
        for(int t = 0; t < vals.size(); t++)
            matrix[i][t] = 0;

    int ind1 = 0;
    int ind2 = 0;
    for (int i = 1 ; i < len + 1 ; i++)
    {
        for (itr = vals.begin(); itr != vals.end(); itr++){
            if (data[i][Y] == *itr)
                break;
            ind1++ ;
        }
        for (itr = vals.begin(); itr != vals.end(); itr++){
            if (data[i][Ypred] == *itr)
                break;
            ind2++;
        }
        matrix[ind1][ind2] += 1;
        ind1 = 0;
        ind2 = 0;
    }

    if (print){
        printf("  ");
        for (itr = vals.begin() ; itr != vals.end() ; itr++)
            printf(" %3d", *itr);
        printf("\n");
        itr = vals.begin();
        for (int i = 0 ; i < vals.size() ; i++)
        {
            printf("%d: ",*itr);
            itr++;
            for (int t = 0 ; t < vals.size(); t++)
                printf("%3d ", matrix[i][t]);
            printf("\n");
        }
    }
    vals.clear();
    return matrix;
}



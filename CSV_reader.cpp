#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <math.h>
#include <ctime>
#include <chrono>
#include "DataTools.cpp"

#define BUFF_SIZE 512

using namespace std;


int fromCharToInt(char* numeric);
char** splitString(char* str, char sep = ';', int sections = 2, int buff_size = 255);

int* ConvertToNums(char *str, char *sep, int cols)
{
    char *token;
    token = strtok(str, sep);
    int *res = (int*)calloc(cols,sizeof(int));
    int i = 0;

    while( token != NULL )
   {
      sscanf(token,"%d",&res[i++]);
      //newName[iCurName] = malloc (char *) (strlen(token) + 1);
      //strcpy(newName[iCurName],token);
      //iCurrName ++;
      token = strtok(NULL, sep);
   }
   free(token);
   return res;
}

int getSections (char* str, char sep = ';'){
    int res = 0;
    int i = 0;
    while (str[i] != NULL)
    {
        if (str[i++] == ';')
            res++;
    }
    return ++res;
}

int** ReadCSV(char* file_name, char separator = ';', int max_len = -1, int start_row = -1)
{
    FILE *f = fopen(file_name, "r");
    char *buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
    int rows = 1;
    int cols = 0;

    if (fscanf(f, "%s", buff) != -1){
        cols = getSections(buff);
    }
    else
        return 0;

    while (fscanf(f, "%s", buff) != -1)
    {
        rows++;
    }
    fclose(f);
    if (max_len >= 0)
    {
        if (start_row > 0)
            rows = min(rows - start_row, max_len);
        else
            rows = min(rows, max_len);
    }
    else if (start_row > 0)
        rows = rows - start_row;
    printf("creating a file\n");


    f = fopen(file_name,"r");
    int t = 0;
    if (start_row > 0)
    {
        while (t <  start_row)
        {
            fscanf(f,"%s", buff);
            t++;
        }

    }
    printf("%d %d\n", cols, rows);
    int** data;
    data = new int*[rows + 1];
    data[0] = new int[2];
    data[0][0] = cols;
    data[0][1] = rows;
    int i = 1;

    while (fscanf(f, "%s", buff) != -1)
    {
        data[i] = (int*)calloc(cols,sizeof(int));
        if (!data[i])
        {
            printf("Out of memory\n");
            break;
        }
        data[i] = ConvertToNums(buff, &separator, cols);
        i++;
        if (i == rows + 1)
            break;
    }
    fclose(f);
    free(buff);
    return data;
}

int main(){


    int** data = ReadCSV("Data.csv",';');
    printf("%d\n", sizeof(data));
    int *oneCol[2];
    oneCol[0] = (int*)calloc(data[0][1],sizeof(int));
    oneCol[1] = (int*)calloc(data[0][1],sizeof(int));
    /*
    for (int i = 1; i < data[0][1] + 1; i++){
        for(int t = 0; t < data[0][0]; t++){
            printf("%3d ",data[i][t]);
        }
        printf("\n");
    }
    */
    printf("Done reading\n");
    for (int i = 0; i < data[0][1]; i ++)
    {
        oneCol[0][i] = data[i+1][0];
        oneCol[1][i] = data[i+1][1];
    }

    printf("Done splitting\n");
    printf("%d %d\n",
           SquareErr(oneCol[0], oneCol[1], data[0][1]),
           MedianErr(oneCol[0], oneCol[1], data[0][1]));
    return 1;
}

// convert a line to int from the beginning till the first non-numeric value

int fromCharToInt(char* numeric)
{
    //char c = numeric[0];
    int res = 0;
    /*
    int i = 0;


    while (c >= '0' && c <= '9')
        c = numeric[++i];
    i--;
    int p = 0;
    */
    sscanf(numeric, "%d", &res);
    return res;
}

char** splitString(char *str, char sep, int sections, int buff_size)
{
    char** res;
    int curr_sec = 0;
    int cursor = 0;
    res = new char*[sections];
    res[0] = new char[buff_size];

    for (int i = 0; i < buff_size; i++)
    {
        if (str[i] == NULL)
            break;
        if (str[i] != sep){
            res[curr_sec][cursor++] = str[i];
        }
        else {
            res[++curr_sec] = new char[buff_size];
            cursor = 0;
        }
    }
    return res;
}


#include <stdlib.h>
#include <stdio.h>

#define rows 3000000
#define cols 100

int main()
{
    FILE *f = fopen("Data.csv", "w");
    for (int i = 0; i < rows; i++)
    {
        for(int t = 0; t < cols; t++)
        {
            fprintf(f,"%d", rand()%999);
            if ( t != cols - 1)
                fprintf(f, ";");
        }
        fprintf(f,"\n");
    }


    fclose(f);
}

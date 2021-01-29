#include <stdlib.h>

int SimpleHash(char** input, int size)
{
    int res = 0;
    for(int i = 0; i < size; i++){
        printf("Char %c have code %d\n",input[i], input[i]);
        res += input[i];
    }
    return res;
}

void FindCoins(int *coins, int target, int *counter, int size)
{
    int tar = target;
    for(int i = 0 ; i < size; ++i)
        if (coins[i] <= tar){
            counter[i]++;
            tar -= coins[i];
            i--;
        }
}
int main()
{
    char **word[6] = {'H','e','l','l','o','!'};
    printf("Total hash is: %d\n",SimpleHash(word, 6));

    int coins[5] = {50,10,5,2,1};
    int counter[5] = {0};
    FindCoins(&coins, 98, &counter, 5);
    printf("\nGreedy coin count:\n");
    for (int i = 0; i < 5; i++)
        printf("%2d - %2d\n",coins[i], counter[i]);
}

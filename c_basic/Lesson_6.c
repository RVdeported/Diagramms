#include <stdlib.h>

#define SIZE_S 1000
#define SIZE 10
#define true 1 == 1
#define false 1 != 1
#define T char

//--------------------Queue-------------------------------//

int head;
int tail;
int items;

typedef int boolean;
typedef struct{
    int pr;
    int dat;
} Node;

Node* arr[SIZE];

void init() {
    for(int i = 0; i < SIZE; i++)
        arr[i] = NULL;
    head = 0;
    tail = 0;
    items = 0;
}

boolean add(int pr, int dat)
{
    if (items >= SIZE)
    {
        printf("Deck is full\n");
        return false;
    }

    Node *n = (Node *)malloc(sizeof(Node));
    n -> pr = pr;
    n -> dat = dat;
    arr[head] = n;
    items++;
    head = (head + 1) % SIZE;
    return true;
}

Node* remove(){
    if (items < 1)
    {
        printf("No items to remove\n");
        return NULL;
    }
    int max = -255;
    int ind = tail;
    for (int i = 0; i < items; i++) // determing max priority value and closest max element in queue
    {
        int temp_ind = (tail + i) % SIZE;
        if (arr[temp_ind] -> pr > max)
        {
            max = arr[temp_ind] -> pr;
            ind = temp_ind;
        }
    }
    Node* tmp = arr[ind]; //storing output
    arr[ind] = NULL;
    if (head - 1 < 0)
        head = SIZE - 1;
    else
        head--;
    for (int i = ind; i < head; ++i) //shifting arr towards removed element
        arr[i] = arr[(i+1)%SIZE];
    arr[head] = NULL; // removing the last element
    items--;
    return tmp;
}

void printDeck()
{
    for (int i = 0; i < SIZE; i++)
        if (arr[i] != NULL)
            printf("[%d %d] ",arr[i] -> pr, arr[i] -> dat);
        else
            printf("[* *] ");
    printf("\n");
}

void showNode (Node* node)
{
    printf("[%d %d]\n",node -> pr, node -> dat);
}
//--------------------------------Binary Stack-----------------------//

T Stack[SIZE_S];
int cursor = -1;

boolean push(T data){
    if (cursor >= SIZE_S)
    {
        printf("Stack full\n");
        return false;
    }
    Stack[++cursor] = data;
    return true;
}

T pop(){
    if (cursor == -1)
    {
        printf("No data in stack");
        return -1;
    }
    return Stack[cursor--];
}

void binary_to_dec(int num)
{
    while (num > 0)
    {
        push(num % 2);
        num >>= 1;
    }
    while(cursor > -1)
        printf("%d",pop());
    printf("\n");
}
//-------------------------------------------------//
int main(){
    // forming key parametrs for queue demonstration
    int key_size = 10;
    int data_size = 100;
    int remove_times = 5;
    while (remove_times < 1)
        remove_times = rand() % SIZE;
    //------------------------------//
    printf("Queue formation:/n");
    for(int i = 0; i < SIZE; i++)
    {
        add(rand()%key_size, rand()%data_size);
        printDeck();
    }
    printf("\nTotal Queue:\n");
    printDeck();
    printf("\nRemoving items:\n");
    for (int i = 0; i < remove_times; i ++)
    {
        printf("extracted ");
        showNode(remove());
        printDeck();
    }
    printf("\nTotal remaining deck\n");
    printDeck();
    printf("\nCounting binary to 20:\n");
    for(int i = 1; i <= 20; i++)
    {
        printf("%2d: ",i);
        binary_to_dec(i);
    }

}

#include <stdlib.h>

#define graphs_big   14
#define graphs_small 6
#define char_A 65
#define T char
#define true 1==1
#define false 1!=1

typedef int bool;

//---------------Stack utilities-------------//
typedef struct {
    int data;
    struct Node *prev;
} Node;

typedef struct {
    struct Node *head;
    int size;
} Stack;

bool init(Stack *stack);
bool clear_and_init(Stack *stack);
bool add (Stack *stack, int data);
T pop(Stack *stack);

//-------------------------------------------//

// matrix for task 1
int **g_matrix_small[graphs_small][graphs_small] = {
    //A  B  C  D  E  F
    { 0, 1, 1, 1, 0, 0},
    { 0, 0, 0, 0, 1, 0},
    { 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0}
};

// matrix for task 2
int **g_matrix_big[graphs_big][graphs_big] = {
    //A  B  C  D  E  F  G  H  I  J  K  L  M  N
    { 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
    { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    { 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    { 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    { 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
    { 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1},
    { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};
int visited[graphs_big] = {0};
int count_rec[graphs_big] = {0};
int count_adj[graphs_big] = {0};


void deepSearch_rec(char start, Stack *stack, int **matrix, int graphs)
{
    add(stack, start);
    int st = start - char_A;
    visited[st] = 1;
    for (int i = 0 ; i < graphs; i++)
        if (*(matrix  + st * graphs + i) == 1 && st != i)//
        {
            count_rec[i]++;
            if (visited[i] == 0)
                deepSearch_rec(i + char_A, stack, matrix, graphs);
        }
}

void adjSearch(int **matrix[][graphs_big], int graphs)
{
    for (int i = 0; i < graphs; i++)
        for (int t = 0; t < graphs; t++)
            if (matrix[i][t] == 1 && i != t)
                count_adj[t]++;
}


//---------utilities---------------//
void clear_arrs();
void sorted_show();

int main()
{
    printf("Task 1 - conducting deep search via Stack container:\n");
    clear_arrs();
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    init(stack);
    deepSearch_rec('A', stack, g_matrix_small, graphs_small);
    while (stack->size > 0)
        printf("%c ", pop(stack));
    printf("\n");
    clear_arrs();

    printf("\nTask 2 - conducting search via recSearch and adj search:\n");
    clear_and_init(stack);
    deepSearch_rec('A', stack, g_matrix_big, graphs_big);
    adjSearch(g_matrix_big, graphs_big);
    sorted_show();
    printf("Note: E, I and F nodes are expected to be 0 by recSearch as those are not connected to start 'A' node\n");
}

void clear_arrs()
{
    for (int i = 0; i < graphs_big; i++)
    {
        visited[i] = 0;
        count_rec[i] = 0;
        count_adj[i] = 0;
    }
}
void sorted_show()
{
    printf("Node | recSearch | adjSearch\n");
    printf("----------------------------\n");
    for(int i = graphs_big; i >= 0; i--)
        for (int t = 0; t < graphs_big; t++)
            if (count_adj[t] == i)
                printf("    %c|%11d|%10d\n", t+ char_A, count_rec[t],count_adj[t]);
    printf("----------------------------\n");
}

bool init(Stack *stack)
{
    stack->size = 0;
    stack->head = NULL;
    return true;
}

bool clear_and_init(Stack *stack)
{
    while(stack->size > 0)
        pop(stack);
    init(stack);
}

bool add (Stack *stack, int data)
{
    Node *add = (Node*)malloc(sizeof(Node));
    if (add == NULL)
    {
        printf("Stack overflow");
        return false;
    }
    add->prev = NULL;
    add->data = data;
    if (stack->size == 0)
        stack->head = add;
    else
    {
        add->prev = stack->head;
        stack->head = add;
    }
    stack->size++;
}

T pop(Stack *stack)
{
    if (stack->size <= 0)
    {
        printf("The stack is empty");
        return NULL;
    }
    Node *to_return = stack->head;
    T res = to_return->data;
    stack->head = to_return->prev;
    free(to_return);
    stack->size--;
    return res;
}

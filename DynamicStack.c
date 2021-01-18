#include <stdlib.h>

#define true 1==1
#define false 1!=1
#define T int

typedef int bool;

typedef struct {
    int data;
    struct Node *prev;
} Node;

typedef struct {
    struct Node *head;
    int size;
} Stack;

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





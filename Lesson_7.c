#include <stdlib.h>
#include <ctype.h>

#define true 1==1
#define false 1!=1

#define par_len 6

#define T int

//--------------------------------Part 1------------------------------------//
typedef int bool;

const char corresponding_par[par_len] = {'[',']','(',')','{','}'};

bool check_line(char* line, int len){
    int booked[len];
    for(int i = 0; i < len; i++)
        booked[i] = 0;
    for(int i = len - 1; i >= 0; i--) // scroll through array backwards...
        for(int t = 0; t < par_len; t += 2) //...to find last open unchecked start-bracket
            if (line[i] == corresponding_par[t] &&
                booked[i] != 1)
                for (int r = i; r < len; r++) //...and scroll back to the end of the arr to find if there is unchecked closing bracket
                {
                    if (line[r] == corresponding_par[t + 1] &&
                        booked[r] != 1)
                    {
                        booked[i] = 1;
                        booked[r] = 1;
                        break;
                    }
                    if (r == len - 1) // if no closed brackets detected -> false
                    {
                        printf("Error!\n");
                        printCharArr(line, len);
                        printPointer(i);
                        return false;
                    }
                }

    /*
     * Code above checks all open brackets to have corresponding closing brackets
     * Code below check if there any closing brakcets left unbooked.
     */
    for(int i = 0; i < len; i++)
        if (booked[i] != 1)
            for(int t = 1; t < par_len; t += 2)
                if (line[i] == corresponding_par[t])
                {
                    printf("Error!\n");
                    printCharArr(line, len);
                    printPointer(i);
                    return false;
                }
    return true;
}

// scan input and return lengh
int record_line(char* line)
{
    int len = 0;
    for (int i = 0;i < 100;i++)
    {
        scanf("%c", &line[i]);
        if (line[i] == '\n')
        {
            len = i;
            break;
        }
        //printf("recording %c\n", line[i]);
    }
    return len;
}

void printCharArr(char* line, int len)
{
    for(int i = 0; i < len; i++)
        printf("%c",line[i]);
    putchar('\n');
}

void printPointer(int spaces)
{
    for(int i = 0;i < spaces; i++)
        printf(" ");
    printf("^\n");
    for(int i = 0;i < spaces; i++)
        printf(" ");
    printf("|\n");

}
//--------------------------------Part 2------------------------------------//

//----creating the list structure-------//
typedef struct{
    struct Node *prev;
    T data;
} Node;


typedef struct{
    int size;
    struct Node *head;
} List;

void init(List *list)
{
    list->size = 0;
    list->head = NULL;
}
bool push(int data, List *list)
{
    Node *tmp = (Node*)malloc(sizeof(Node));
    if (tmp == NULL)
    {
        printf("Stack overflow\n");
        //free(tmp);
        return false;
    }
    tmp->prev = NULL;
    tmp->data = data;
    Node *current = list->head;
    list->head = tmp;

    //printf("Recording %d\n",tmp->data);
    tmp->prev = current;
    //printf("Out is %d %d\n",list->size,tmp->data);
    //free(tmp);
    list->size++;
    return true;
}

void printList(List *list)
{
    int size = list->size;
    Node *curNode = list->head;
    printf("[");
    while (size > 0){
        printf("%d ",curNode ->data);
        curNode = curNode->prev;
        size--;
    }
    printf("]\n");
}

T pop(List *list)
{
    if (list->size <= 0)
    {
        printf("List is empty");
        return -1;
    }
    Node *to_free = list->head;
    int dat = to_free->data;
    if (list->size==1)
        list->head = NULL;
    else
        list->head = to_free->prev;
    free(to_free);
    list->size--;
    return dat;
}
//--------------------------------Part 2------------------------------------//

bool CopyList(List *from, List *to)
{
    int size = from->size;
    Node *currFr = from->head;
    Node *currTo = to->head;
    int tmp[size];
    for(int i = 0; i < size ; i++)
    {
        tmp[i] = currFr->data;
        if (i < size-1)
            currFr = currFr->prev;
    }
    for(int i = 0; i < size; i++)
    {
        push(tmp[size - i - 1],to);
    }
    return true;
}

//--------------------------------Part 3------------------------------------//

bool isSorted(List* list)
{
    Node *curNode = list->head;
    T Max = curNode->data;
    int size = list->size;

    while(size != 1)
    {
        curNode = curNode->prev;
        if (curNode->data > Max)
            return false;
        Max = curNode->data;
        size--;
    }
    return true;
}



int main(){
    int max_size = 1000;
    static char message[1000];
    printf("Testing brackets solution.\n");
    while (1 == 1)
    {
        printf("Enter the message or '@' to exit:\n");
        if (message[0] == '@')
            break;
        int len = record_line(&message);
        printf("check %d\n", check_line(&message, len));
    }

    List *list_1 = (List*)malloc(sizeof(List));
    init(list_1);
    List *list_2 = (List*)malloc(sizeof(List));
    init(list_2);
    printf("\nFilling list_1:\n");
    for (int i = 0; i < 10; i++)
        push(i, list_1);
    printList(list_1);
    printf("Copying list_1 into list_2:\n");
    CopyList(list_1, list_2);
    printf("list_1: ");
    printList(list_1);
    printf("list_2: ");
    printList(list_2);

    printf("\nFilling list with sorted numbers:\n");
    List *list_3 = (List*)malloc(sizeof(List));
    init(list_3);
    for (int i = 0; i < 10; i++)
        push(i, list_3);
    printList(list_3);
    printf("The list is sorted: %d\n",isSorted(list_3));
    list_3 = (List*)malloc(sizeof(List));
    init(list_3);
    for (int i = 0; i < 10; i++)
        push(rand()%30, list_3);
    printList(list_3);
    printf("The list is sorted: %d\n",isSorted(list_3));
}

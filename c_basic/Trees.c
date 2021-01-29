#include <stdlib.h>
#include <stdio.h>

#define true 1==1
#define false 1!=1


//--------------------------Tree base settings-----------------------------//
typedef int bool;

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
} TreeNode;

FILE *file;

TreeNode* insert_tree(TreeNode *t, int data)
{
    TreeNode *newTree;
    newTree = (TreeNode*)malloc(sizeof(TreeNode));
    TreeNode *parent = t;
    TreeNode *current = t;
    newTree->key = data;
    newTree->left = NULL;
    newTree->right = NULL;
    if(t == NULL)
        t = newTree;
    else
        while (1==1)
        {
            parent = current;
            if (current->key > data)
            {
                current = current->right;
                if (current == NULL)
                {
                    parent->right = newTree;
                    break;
                }
            }
            else
            {
                current = current->left;
                if (current == NULL)
                {
                    parent->left = newTree;
                    break;
                }
            }
        }
    return t;
}



TreeNode* GetSuccsessorTree (TreeNode *t)
{
    TreeNode *parent = t;
    TreeNode *current = t -> right;
    TreeNode *s = t;

    while (current != NULL)
    {
        parent = current;
        s = current;
        current = current -> left;
    }
    if (s != t -> right)
    {
        parent -> left = s -> right;
        s -> right = t ->right;
    }
    //print_Tree(s);
    //printf("\n");
    return s;
}

bool delete_tree(TreeNode *tree,int num)
{
    if (tree == NULL)
    {
        printf("Tree is empty\n");
        return false;
    }
    TreeNode *parent = tree;
    TreeNode *current = tree;
    bool isLeft = true;
    while (current -> key != num)
    {
        parent = current;
        if (num > current -> key)
        {
            current = current->left;
            isLeft = true;
        }
        else
        {
            current = current->right;
            isLeft = false;
        }

        if (current == NULL)
        {
            printf("No such node is found: %d\n",num);
            return false;
        }
    }

    if (current->left == NULL && current->right == NULL)
    {
        if (isLeft)
            parent->left = NULL;
        else
            parent->right = NULL;
    }
    else if (current -> left == NULL || current -> right == NULL)
    {
        if (current -> left == NULL )
            if (isLeft)
                parent->left = current -> right;
            else parent->right = current -> right;
        else
            if (isLeft)
                parent->left = current -> left;
            else parent->right = current -> left;
    }
    else
    {
        TreeNode *succsessor = GetSuccsessorTree(current);
        succsessor -> left = current -> left;
        if (isLeft)
            parent->left = succsessor;
        else parent->right = succsessor;

    }
    return true;
}

TreeNode* balancedTree(int n)
{
    TreeNode *newTree;
    if (n==0)
        return NULL;
    int x;
    int L = n / 2;
    int R = n - L - 1;
    newTree = (TreeNode*)malloc(sizeof(TreeNode));
    fscanf(file,"%d",&x);
    newTree->key = x;
    newTree->left=balancedTree(L);
    newTree->right=balancedTree(R);
    return newTree;
}

//----------------------------------isBalanced func-----------------------------//
bool isBalanced(TreeNode *tree) //the func recursively compares node count on both branches.
{
    if (tree == NULL)
        return true;
    int Lcount = NodeCounter(tree->left);
    int Rcount = NodeCounter(tree->right);
    if (isBalanced(tree->left) && isBalanced(tree->right))
        if (abs(Lcount - Rcount) <= 1) // in case of odd element size, there can be allowed difference by 1
            return true;
    return false;
}

int NodeCounter(TreeNode *tree)
{
    if (tree == NULL)
        return 0;
    int counter = NodeCounter(tree->left);
    counter += NodeCounter(tree->right);
    return counter + 1;
}

//-----------------------------------Recursive find func-----------------------//

TreeNode* findItem(TreeNode *t, int key)
{
    if (t==NULL)
        return NULL;
    if (key == t-> key)
        return t;
    else if (key > t->key)
        return findItem(t->left, key);
    else
        return findItem(t->right, key);
}


 //--------------------Utilities-----------------------//
void print_Tree(TreeNode *t) // there is separate func just to print '\n'
{
    _print_Tree(t);
    printf("\n");
}

bool _print_Tree(TreeNode *t)
{
    if(t == NULL)
        return false;
    printf("%d",t->key);
    if (t->right || t->left)
    {
        printf("(");
        if (t->right)
            _print_Tree(t->right);
        else
            printf("NULL");
        printf(",");
        if (t->left)
            _print_Tree(t->left);
        else
            printf("NULL");
        printf(")");
    }
    return true;
}

TreeNode* FillTree(TreeNode *t, int size, int max_num)
{
    t = insert_tree(t, rand()%max_num);
    for (int c = 0; c < size; c++)
        insert_tree(t, rand()%max_num);
    return t;
}

void findAndShow(TreeNode *t, int key)
{
    TreeNode *m = findItem(t, key);
    if (m == NULL)
        printf("Not found");
    else
    {
        printf("Found item:\n");
        print_Tree(m);
    }
}

int main(int argc, char const *argv[])
{
    printf("Task 1: Creation of 10000 trees 10-el long and finding balanced:\n");
    TreeNode *t = NULL;
    int balanced_counter = 0;
    int Trees = 10000;
    int SIZE = 10;
    int max_num = 1000;
    for(int i = 0; i < Trees; i++)
    {
        t = NULL;
        t = FillTree(t, SIZE, 1000);
        if (isBalanced(t)==1)
        {
            balanced_counter++;
            printf("\nBalanced tree found:\n");
            print_Tree(t);
        }
    }
    printf("\nTotal balanced trees: %d\n", balanced_counter);
    printf("Total success trees ratio: 0,%d%%\n",balanced_counter *1000 / Trees );
    printf("--------------------------------------------------\n");
    printf("\nTask 2: Find something in Tree. Test tree is below:\n");
    int key_to_find = (t->right)->key;
    print_Tree(t);
    printf("Aim - find the key: %d\n",key_to_find);
    findAndShow(t, key_to_find);
    int key_you_wont_find = max_num + 1;
    printf("\nTrying to find key that is Not in the tree:\n");
    findAndShow(t, key_you_wont_find);
}

#include <stdlib.h>

#define true 1==1
#define false 1!=1

typedef int bool;

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
} TreeNode;

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
    {
        t = newTree;
    }
    else
    {
        while (current->key != data)
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
    }
    return t;
}

bool print_Tree(TreeNode *t)
{
    if(t == NULL)
        return false;
    printf("%d",t->key);
    if (t->right || t->left)
    {
        printf("(");
        if (t->right)
            print_Tree(t->right);
        else
            printf("NULL");
        printf(",");
        if (t->left)
            print_Tree(t->left);
        else
            printf("NULL");
        printf(")");
    }
    return true;
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



int main()
{
    TreeNode *t = NULL;
    t = insert_tree(t,10);
    insert_tree(t,8);
    insert_tree(t,19);
    insert_tree(t,5);
    insert_tree(t,16);
    insert_tree(t,21);
    insert_tree(t,9);
    insert_tree(t,15);
    insert_tree(t,20);
    print_Tree(t);
    printf("\n");
    delete_tree(t,19);
    print_Tree(t);
}

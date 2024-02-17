#include <stdio.h>
#include <stdlib.h>
#include "binSearchTree.h"

void linkedListInit(LinkedList *list)
{
}

// todo : listAppendRear(Q+), listPopFront(Q-), listTerminate
// nodeAppendFront(sPush), nodePopFront(sPop)

// this is meaningless, but if you have data element except key value, it will be useful
TreeNode *binTreeSearch(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    if (root->key == key)
        return root; // need to revise it -> return matching data
    if (key < root->key)
        return binTreeSearch(root->lChild, key);
    return binTreeSearch(root->rChild, key);
}

TreeNode *_treeInsertSearch(TreeNode *root, int key)
{
    if (root == NULL)
        return NULL;
    TreeNode *now = root;
    TreeNode *pre = NULL;

    while (now != NULL)
    {
        if (now->key == key)
            return NULL; // inserting same value is not allowed
        if (now->key < key)
        {
            pre = now;
            now = now->rChild;
        }
        else
        {
            pre = now;
            now = now->lChild;
        }
    }

    return pre;
}

TreeNode *insertBinTree(TreeNode *root, int key)
{
    TreeNode *newNode;
    if (root == NULL)
    {
        newNode = malloc(sizeof(TreeNode));
        newNode->key = key;
        newNode->lChild = NULL;
        newNode->rChild = NULL;
        return newNode;
    }
    TreeNode *parentNode = _treeInsertSearch(root, key);
    if (parentNode)
    {
        newNode = malloc(sizeof(TreeNode));
        newNode->key = key;
        newNode->lChild = newNode->rChild = NULL;
        if (key < parentNode->key)
            parentNode->lChild = newNode;
        else
            parentNode->rChild = newNode;
    }
    return root;
}

void inorderPrintRecur(TreeNode *root)
{
    if (root)
    {
        inorderPrintRecur(root->lChild);
        printf("%3d ", root->key);
        inorderPrintRecur(root->rChild);
    }
}
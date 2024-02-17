#include <stdio.h>
#include <stdlib.h>
#include "binSearchTree.h"

void linkedListInit(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

void listAppendFront(LinkedList *list, TreeNode data)
{
    LinkedNode *newNode = malloc(sizeof(LinkedNode));
    if (list->head == NULL)
    {
        list->tail = newNode;
    }
    newNode->data = data;
    newNode->next = list->head;
    list->head = newNode;
}

void listAppendRear(LinkedList *list, TreeNode data)
{
    LinkedNode *newNode = malloc(sizeof(LinkedNode));
    newNode->data = data;
    newNode->next = NULL;
    if (list->tail != NULL)
        list->tail->next = newNode;
    list->tail = newNode;
    if (list->head == NULL)
        list->head = newNode;
    else if (list->head->next == NULL)
        list->head->next = newNode;
}

TreeNode *listPopFront(LinkedList *list)
{
    if (list->head == NULL)
        return NULL;
    LinkedNode *temp = list->head;
    TreeNode *data = malloc(sizeof(TreeNode));
    *data = temp->data;
    list->head = temp->next;
    if (list->head == NULL)
        list->tail = NULL;
    free(temp);
    return data;
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

void inorderPrintIter(TreeNode *root)
{
    TreeNode *ptr = root;
    LinkedList *stack = malloc(sizeof(LinkedList));
    linkedListInit(stack);
    while (1)
    {
        // at start, stack all node until we reach leftmost node
        for (; ptr != NULL; ptr = ptr->lChild)
            listAppendFront(stack, *ptr);
        ptr = listPopFront(stack); // reached NULL node, so we pop once
        if (ptr == NULL)           // if stack is empty, break loop
            break;
        printf("%3d ", ptr->key);
        // if we are on terminal node, we doesn't append anymore, pop from stack (go to parent node)
        // else, we are in parent node of some left child. we try to reach rChild & stack lChild if exits
        ptr = ptr->rChild;
    }
    free(stack);
}
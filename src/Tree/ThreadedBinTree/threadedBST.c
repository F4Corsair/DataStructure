#include <stdio.h>
#include <stdlib.h>
#include "threadedBST.h"

/* in linked representation of binary tree, there are more null links than actual pointers
 * we replace the null links by pointers to other nodes by following rules
 * 1. if ptr->leftChild == NULL -> replace it with a pointer to the node
 * that would be visited before ptr in an inorder traversal
 * 2. if ptr->rightChild == NULL -> replace it wit a pointer to the node
 * that would be visited after ptr in an inorder traversal
 */

TreeNode *initThreadedBST()
{
    TreeNode *root = malloc(sizeof(TreeNode));
    root->lThreaded = 1; // new node start from left side, so we sign left as threaded
    root->rThreaded = 0; // left threaded info is useless
    root->lChild = root;
    root->rChild = root;
    return root;
}

TreeNode *findInorderSuccessor(TreeNode *node)
{
    // threaded node(leaf node) is linked to inorder successor
    TreeNode *temp;
    temp = node->rChild;
    if (!node->rThreaded)
    {
        while (!temp->lThreaded)
        {
            temp = temp->lChild;
        }
    }
    return temp;
}

void inodrderTraversePrint(TreeNode *root)
{
    TreeNode *temp = root->lChild;
    for (; !temp->lThreaded; temp = temp->lChild)
        ; // move to leftmost node in tree
    printf("%3d ", temp->key);
    while (1)
    {
        temp = findInorderSuccessor(temp);
        if (temp == root)
            break;
        printf("%3d ", temp->key);
    }
}

void _insertTbstRight(TreeNode *parent, TreeNode *newNode)
{
    // insert newNode as leftChild of parent node
    // parent's leftChild subtree will be changed into newNode's leftChild
    TreeNode *temp;
    newNode->rChild = parent->rChild;
    newNode->rThreaded = parent->rThreaded;
    newNode->lChild = parent;
    newNode->lThreaded = 1;
    parent->rChild = newNode;
    parent->rThreaded = 0;
    if (!newNode->rThreaded)
    {
        // it means parent node has subtree as child
        temp = findInorderSuccessor(newNode);
        // change inordersuccessor's(thread node) lchild connection
        temp->lChild = newNode;
    }
}

void _insertTbstLeft(TreeNode *parent, TreeNode *newNode)
{
    // insert newNode as rightChild of parent node
    // parent's rightChild subtree will be changed into newNode's rightChild
    TreeNode *temp;
    newNode->lChild = parent->lChild;
    newNode->lThreaded = parent->lThreaded;
    newNode->rChild = parent;
    newNode->rThreaded = 1;
    parent->lChild = newNode;
    parent->lThreaded = 0;
    if (!newNode->lThreaded)
    {
        // find node that would be visited before newNode in an inorder traversal
        temp = newNode->lChild;
        if (!temp->rThreaded)
            while (!temp->rThreaded)
                temp = temp->rChild;
        temp->rChild = newNode;
    }
}

TreeNode *_treeInsertSearch(TreeNode *root, int key)
{
    TreeNode *now = root->lChild;

    while (1)
    {
        if (now->key == key)
            return NULL; // inserting same value is not allowed
        if (now->key < key)
        {
            if (now->rThreaded)
                return now;
            now = now->rChild;
        }
        else
        {
            if (now->lThreaded)
                return now;
            now = now->lChild;
        }
    }
}

void insertThreadedBST(TreeNode *root, int key)
{
    TreeNode *newNode;
    if (root->lThreaded)
    {
        // initial node will be root's leftChild regardless of its key value
        newNode = malloc(sizeof(TreeNode));
        newNode->key = key;
        _insertTbstLeft(root, newNode);
        return;
    }
    TreeNode *parentNode = _treeInsertSearch(root, key);
    if (parentNode) // same key value in tree is not allowed & skip memory allocation
    {
        newNode = malloc(sizeof(TreeNode));
        newNode->key = key;
        if (parentNode->key > key)
            _insertTbstLeft(parentNode, newNode);
        else
            _insertTbstRight(parentNode, newNode);
    }
}

void terminateThreadedBST(TreeNode *root)
{
    TreeNode *temp = root->lChild;
    TreeNode *next;
    for (; !temp->lThreaded; temp = temp->lChild)
        ;
    while (1)
    {
        next = findInorderSuccessor(temp);
        free(temp);
        temp = next;
        if (temp == root)
            break;
    }
    free(root);
}
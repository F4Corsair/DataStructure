#ifndef __threadedBinarySearchTree
#define __threadedBinarySearchTree

typedef struct _TreeNode
{
    int key;
    int lThreaded, rThreaded;
    struct _TreeNode *lChild, *rChild;
} TreeNode;

TreeNode *initThreadedBST();

TreeNode *findInorderSuccessor(TreeNode *node);

void inodrderTraversePrint(TreeNode *root);

void _insertTbstRight(TreeNode *parent, TreeNode *newNode);

void _insertTbstLeft(TreeNode *parent, TreeNode *newNode);

TreeNode *_treeInsertSearch(TreeNode *root, int key);

void insertThreadedBST(TreeNode *root, int key);

void terminateThreadedBST(TreeNode *root);

#endif
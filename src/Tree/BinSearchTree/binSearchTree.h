#ifndef __BinSearchTree
#define __BinSearchTree

typedef struct _TreeNode
{
    int key;
    struct _TreeNode *rChild, *lChild;
} TreeNode;

typedef struct _LinkNode
{
    int num;
    struct _LinkNode *next;
} LinkedNode;

typedef struct
{
    LinkedNode *head;
    LinkedNode *tail;
} LinkedList;

TreeNode *binTreeSearch(TreeNode *root, int key);

TreeNode *_treeInsertSearch(TreeNode *root, int key);

TreeNode *insertBinTree(TreeNode *root, int key);

void inorderPrintRecur(TreeNode *root);

#endif
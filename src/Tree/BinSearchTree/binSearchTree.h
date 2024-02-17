#ifndef __BinSearchTree
#define __BinSearchTree

typedef struct _TreeNode
{
    int key;
    struct _TreeNode *rChild, *lChild;
} TreeNode;

typedef struct _LinkNode
{
    TreeNode data;
    struct _LinkNode *next;
} LinkedNode;

typedef struct
{
    LinkedNode *head;
    LinkedNode *tail;
} LinkedList;

void linkedListInit(LinkedList *list);

void listAppendFront(LinkedList *list, TreeNode data);

void listAppendRear(LinkedList *list, TreeNode data);

TreeNode *listPopFront(LinkedList *list);

TreeNode *binTreeSearch(TreeNode *root, int key);

TreeNode *_treeInsertSearch(TreeNode *root, int key);

TreeNode *insertBinTree(TreeNode *root, int key);

void inorderPrintRecur(TreeNode *root);

void inorderPrintIter(TreeNode *root);

#endif
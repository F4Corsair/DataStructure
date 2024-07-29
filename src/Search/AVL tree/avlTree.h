#ifndef __AVL_TREE
#define __AVL_TREE

typedef struct _treeNode{
    int key;
    int bf; // balance factor = lChild height - rChild height
    struct _treeNode *rChild, *lChild;
} TreeNode;

void avlInsert(TreeNode **parent, int key, int *unbalanced);
void leftRotation(TreeNode **parent, int *unbalanced);
void rightRotation(TreeNode **parent, int *unbalanced);

#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
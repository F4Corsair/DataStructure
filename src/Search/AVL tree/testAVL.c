#include <stdio.h>
#include <stdlib.h>
#include "avlTree.h"

// AVL tree is Height Balanced Binary search tree - it keeps plausible compare time to search

int main(void) {
    TreeNode *root = NULL;
    int unbalanced = FALSE;

    avlInsert(&root, 10, &unbalanced);
    unbalanced = FALSE;
    avlInsert(&root, 40, &unbalanced);
    unbalanced = FALSE;
    avlInsert(&root, 20, &unbalanced);
    unbalanced = FALSE;
    avlInsert(&root, 30, &unbalanced);
    unbalanced = FALSE;
    avlInsert(&root, 5, &unbalanced);
}
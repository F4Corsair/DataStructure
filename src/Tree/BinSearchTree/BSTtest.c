#include <stdio.h>
#include <stdlib.h>
#include "binSearchTree.h"

int main(void)
{
    TreeNode *root = NULL;
    FILE *fp = fopen("in.txt", "r");
    int readNum;
    fscanf(fp, " %d", &readNum);
    while (!feof(fp))
    {
        root = insertBinTree(root, readNum);
        fscanf(fp, " %d", &readNum);
    }
    fclose(fp);

    puts("[Inorder Traverse]");
    printf("Recur : ");
    inorderPrintRecur(root);
    printf("\nIter : ");
    inorderPrintIter(root);

    puts("\n[Preorder Traverse]");
    printf("Recur : ");
    preorderPrintRecur(root);
    printf("\nIter : ");
    preorderPrintIter(root);

    puts("\n[Postorder Traverse]");
    printf("Recur : ");
    postorderPrintRecur(root);

    puts("\n[LevelOrder Traverse]");
    levelorderPrint(root);
    puts("");
}
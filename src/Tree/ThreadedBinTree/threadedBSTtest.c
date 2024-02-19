#include <stdio.h>
#include <stdlib.h>
#include "threadedBST.h"

int main(void)
{
    TreeNode *root = initThreadedBST();
    FILE *fp = fopen("in.txt", "r");
    int readNum;
    fscanf(fp, " %d", &readNum);
    while (!feof(fp))
    {
        insertThreadedBST(root, readNum);
        fscanf(fp, " %d", &readNum);
    }
    fclose(fp);

    inodrderTraversePrint(root);
    puts("");
    terminateThreadedBST(root);
}
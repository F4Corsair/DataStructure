#include <stdio.h>
#include <stdlib.h>

/*
 / Equivalent Class : find equivalent relationship between symbols(integers) & group them as classes
 / ex) x == y, then y == x. x == y & y == z, then x == z
*/

typedef struct _node
{
    int num;
    struct _node *next;
} Node;

Node *setNode(int num, Node *next)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = next;
    return newNode;
}

int main(void)
{
    FILE *fp = fopen("in1.txt", "r");
    int numListSize;
    // read size of number list. list is number which from 0 to numListSize - 1
    fscanf(fp, "%d", &numListSize);
    // printFlag : to check number was already printed(classed) or not
    int *printFlag = malloc(sizeof(int) * numListSize);
    // linked list that record equivalent numbers of each index
    Node **numList = malloc(sizeof(Node *) * numListSize);
    for (int i = 0; i < numListSize; i++)
    {
        printFlag[i] = 0;
        numList[i] = NULL;
    }

    int readA, readB;
    // read 2 numbers, which has equivalent connection between them
    fscanf(fp, " %d %d", &readA, &readB);
    while (!feof(fp))
    {
        // record connection to corresponding number
        // for example, x == y, list[x] = y ... / list[y] = x ...
        numList[readA] = setNode(readB, numList[readA]);
        numList[readB] = setNode(readA, numList[readB]);
        fscanf(fp, " %d %d", &readA, &readB);
    }
    fclose(fp);

    // classify equivalent by using numList
    int classIdx = 0, readNum;
    Node *curNode, *stack, *nextNode;
    for (int i = 0; i < numListSize; i++)
    {
        if (printFlag[i] == 0)
        {
            printf("Class[%d] : %-3d", classIdx++, i);
            printFlag[i] = 1;
            // start from first number in first numList
            curNode = numList[i];
            stack = NULL;
            while (1)
            {
                while (curNode) // search all node in one numList
                {
                    readNum = curNode->num;
                    if (printFlag[readNum] == 0)
                    {
                        printf("%-3d", readNum);
                        printFlag[readNum] = 1;
                        nextNode = curNode->next;
                        // push curNode to stack, that is, we will search all node that has equivalent relation
                        curNode->next = stack;
                        stack = curNode;
                        // move to next node in same numList
                        curNode = nextNode;
                    }
                    else
                        curNode = curNode->next;
                }
                if (!stack)
                    break; // loop until stack got empty
                // stack pop -> we will search equivalent node that we didn't searched(!printFlag) yet
                curNode = numList[stack->num];
                stack = stack->next;
            } // we searched all node that has equivalent connection to number i
            puts("");
        }
    }

    // free dynamic memory
    free(printFlag);
    for (int i = 0; i < numListSize; i++)
    {
        curNode = numList[i];
        while (curNode)
        {
            nextNode = curNode->next;
            free(curNode);
            curNode = nextNode;
        }
    }
    free(numList);
}
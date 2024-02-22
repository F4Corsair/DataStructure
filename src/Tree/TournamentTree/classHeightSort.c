#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tournamentTree.h"

int main(void)
{
    int classNum, studentPerClass, readHeight, idx;
    char readName[NAME_SIZE];
    FILE *fp = fopen("in.txt", "r");
    fscanf(fp, "%d %d", &classNum, &studentPerClass);

    StudentInfo **classInfoSequence = classSeqInit(classNum, studentPerClass); // saves students information as a list per each class
    int winTreeSize = classNum * 2 - 1;
    TournamentTreeNode *winTree = malloc(sizeof(TournamentTreeNode) * winTreeSize);

    // read class height data from file, record studentInfo & set leaf node of winner tree
    for (int i = 0; i < classNum; i++)
    {
        int treeIdx = (winTreeSize / 2) + i;
        for (int j = 0; j < studentPerClass; j++)
        {
            fscanf(fp, " %s %d", readName, &readHeight);
            classInfoSequence[i][j].class = i + 1;
            classInfoSequence[i][j].height = readHeight;
            strcpy(classInfoSequence[i][j].name, readName);
            // first index of info list == each leaf node of winner tree
            if (j == 0)
                winTree[treeIdx].key = readHeight; // set key value(height)
        }
        winTree[treeIdx].index = i + 1; // set index value (class)
    }
    fclose(fp);

    // winner tree initial setting
    winnerTreeInit(winTree, winTreeSize);

    // pop minimum value & update tree until all sequences been searched
    StudentInfo *sorted = winnerTreeSort(winTree, classInfoSequence, classNum, studentPerClass);

    // print
    puts("[Winner Tree]");
    sortedInfoPrint(sorted, classNum, studentPerClass);

    // reuse winTree data, try loser tree this time
    free(sorted);
    puts("\n[Loser Tree]");
    // we have to reverse each class's classInfoSequence to retrieve fully-sorted value
    for (int i = 0; i < classNum; i++)
    {
        for (int j = 0; j < studentPerClass / 2; j++)
        {
            int temp;
            char tempName[NAME_SIZE];
            temp = classInfoSequence[i][studentPerClass - 1 - j].height;
            strcpy(tempName, classInfoSequence[i][studentPerClass - 1 - j].name);
            classInfoSequence[i][studentPerClass - 1 - j].height = classInfoSequence[i][j].height;
            strcpy(classInfoSequence[i][studentPerClass - 1 - j].name, classInfoSequence[i][j].name);
            classInfoSequence[i][j].height = temp;
            strcpy(classInfoSequence[i][j].name, tempName);
        }
    }
    // reset leaf node of winTree before re-use it
    for (int i = 0; i < classNum; i++)
    {
        int treeIdx = (winTreeSize / 2) + i;
        winTree[treeIdx].key = classInfoSequence[i][0].height;
        winTree[treeIdx].index = i + 1;
    }
    loserTreeInit(winTree, winTreeSize);
    sorted = loserTreeSort(winTree, classInfoSequence, classNum, studentPerClass);
    sortedInfoPrint(sorted, classNum, studentPerClass);

    // free allocated data
    free(winTree);
    classSeqTerminate(classInfoSequence, classNum);
    free(sorted);
}
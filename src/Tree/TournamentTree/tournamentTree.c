#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tournamentTree.h"

/* sort multiple class student with height using Winner Tree
 * from multiple class(FIFO List), get min/max elements consequently with using tree
 * if prepared data, each class list sorted with key values(height), result from winner tree
 * is also sorted with key values (if each class are not sorted, winner tree still try to get extreme value from peeked data)
 * except its initial tree setting time, time complexity of adding new element in winner tree is O(logn)
 * notice : winner tree gets lower key value first, loser tree gets higher key value first
 * both also called as tournament tree or selection tree
 * it is one of Divide and Conquer method like merge sort
 */

StudentInfo **classSeqInit(int classNum, int studentPerClass)
{
    StudentInfo **sequences = malloc(sizeof(StudentInfo *) * classNum);
    for (int i = 0; i < classNum; i++)
        sequences[i] = malloc(sizeof(StudentInfo) * studentPerClass);
    return sequences;
}

void sortedInfoPrint(StudentInfo *sorted, int classNum, int studentPerClass)
{
    for (int i = 0; i < classNum * studentPerClass; i++)
        printf("[%2d] Class %d %*s : %3d cm\n", i + 1, sorted[i].class, NAME_SIZE, sorted[i].name, sorted[i].height);
}

void classSeqTerminate(StudentInfo **sequences, int classNum)
{
    for (int i = 0; i < classNum; i++)
        free(sequences[i]);
    free(sequences);
}

void winnerTreeInit(TournamentTreeNode *winTree, int treeSize)
{
    // start from parent level of leaf nodes (assume that leaf node were already set)
    int startIdx = treeSize / 4;
    int endIdx = treeSize / 2 - 1;
    int left, right;

    while (endIdx >= 0)
    {
        for (int i = startIdx; i <= endIdx; i++)
        {
            // set left & right as child index of i
            left = i * 2 + 1;
            right = left + 1;
            // retrieve smaller value from childs
            if (winTree[left].key < winTree[right].key)
            {
                winTree[i].key = winTree[left].key;
                winTree[i].index = winTree[left].index;
            }
            else
            {
                winTree[i].key = winTree[right].key;
                winTree[i].index = winTree[right].index;
            }
        }
        endIdx = startIdx - 1;
        startIdx /= 2;
    }
}

StudentInfo *winnerTreeSort(TournamentTreeNode *winTree, StudentInfo **classInfoSequence, int classNum, int studentPerClass)
{
    StudentInfo *sorted = malloc(sizeof(StudentInfo) * classNum * studentPerClass);
    int sortedIdx = 0;
    int *seqHead = malloc(sizeof(int) * classNum);
    for (int i = 0; i < classNum; i++)
        seqHead[i] = 0;

    // pop minimum value from initialized winner tree
    int seqToUpdate = sorted[sortedIdx].class = winTree[0].index;
    seqToUpdate = seqToUpdate - 1; // class index starts from 1, but sequence index starts from 0
    sorted[sortedIdx].height = winTree[0].key;
    strcpy(sorted[sortedIdx].name, classInfoSequence[seqToUpdate][seqHead[seqToUpdate]].name);
    seqHead[seqToUpdate]++;
    sortedIdx++;
    // pop minimum value & update tree until all sequences been searched
    while (sortedIdx < classNum * studentPerClass)
    {
        winnerTreeUpdate(winTree, classInfoSequence[seqToUpdate], seqToUpdate, seqHead, classNum, studentPerClass);
        // pop minimum value from winner tree
        seqToUpdate = sorted[sortedIdx].class = winTree[0].index;
        seqToUpdate = seqToUpdate - 1;
        sorted[sortedIdx].height = winTree[0].key;
        strcpy(sorted[sortedIdx].name, classInfoSequence[seqToUpdate][seqHead[seqToUpdate]].name);
        seqHead[seqToUpdate]++;
        sortedIdx++;
    }

    free(seqHead);
    return sorted;
}

void winnerTreeUpdate(TournamentTreeNode *winTree, StudentInfo *infoList, int updateIdx, int *seqHead, int classNum, int studentPerClass)
{
    if (seqHead[updateIdx] >= studentPerClass)
        winTree[classNum - 1 + updateIdx].key = -1; // sequence search complete. set corresponding leaf node as -1 to sign it
    else
        winTree[classNum - 1 + updateIdx].key = infoList[seqHead[updateIdx]].height;

    // be careful with parent, child index. since it starts from 0, index calculating seems ridiculous
    int parent = (classNum + updateIdx) / 2 - 1;
    int lchild, rchild;
    while (parent >= 0)
    {
        lchild = (parent + 1) * 2 - 1;
        rchild = lchild + 1;
        if (winTree[lchild].key == -1)
        {
            // if completed sequence's data found, ignore it
            winTree[parent].key = winTree[rchild].key;
            winTree[parent].index = winTree[rchild].index;
        }
        else if (winTree[rchild].key == -1)
        {
            winTree[parent].key = winTree[lchild].key;
            winTree[parent].index = winTree[lchild].index;
        }
        else if (winTree[lchild].key < winTree[rchild].key)
        {
            winTree[parent].key = winTree[lchild].key;
            winTree[parent].index = winTree[lchild].index;
        }
        else
        {
            winTree[parent].key = winTree[rchild].key;
            winTree[parent].index = winTree[rchild].index;
        }
        parent = (parent + 1) / 2 - 1;
    }
}

void loserTreeInit(TournamentTreeNode *loseTree, int treeSize)
{
    // start from parent level of leaf nodes (assume that leaf node were already set)
    int startIdx = treeSize / 4;
    int endIdx = treeSize / 2 - 1;
    int left, right;

    while (endIdx >= 0)
    {
        for (int i = startIdx; i <= endIdx; i++)
        {
            // set left & right as child index of i
            left = i * 2 + 1;
            right = left + 1;
            // retrieve bigger value from childs
            if (loseTree[left].key > loseTree[right].key)
            {
                loseTree[i].key = loseTree[left].key;
                loseTree[i].index = loseTree[left].index;
            }
            else
            {
                loseTree[i].key = loseTree[right].key;
                loseTree[i].index = loseTree[right].index;
            }
        }
        endIdx = startIdx - 1;
        startIdx /= 2;
    }
}

StudentInfo *loserTreeSort(TournamentTreeNode *loseTree, StudentInfo **classInfoSequence, int classNum, int studentPerClass)
{
    StudentInfo *sorted = malloc(sizeof(StudentInfo) * classNum * studentPerClass);
    int sortedIdx = 0;
    int *seqHead = malloc(sizeof(int) * classNum);
    for (int i = 0; i < classNum; i++)
        seqHead[i] = 0;

    // pop maximum value from initialized loser tree
    int seqToUpdate = sorted[sortedIdx].class = loseTree[0].index;
    seqToUpdate = seqToUpdate - 1; // class index starts from 1, but sequence index starts from 0
    sorted[sortedIdx].height = loseTree[0].key;
    strcpy(sorted[sortedIdx].name, classInfoSequence[seqToUpdate][seqHead[seqToUpdate]].name);
    seqHead[seqToUpdate]++;
    sortedIdx++;
    // pop maximum value & update tree until all sequences been searched
    while (sortedIdx < classNum * studentPerClass)
    {
        loserTreeUpdate(loseTree, classInfoSequence[seqToUpdate], seqToUpdate, seqHead, classNum, studentPerClass);
        // pop minimum value from loser tree
        seqToUpdate = sorted[sortedIdx].class = loseTree[0].index;
        seqToUpdate = seqToUpdate - 1;
        sorted[sortedIdx].height = loseTree[0].key;
        strcpy(sorted[sortedIdx].name, classInfoSequence[seqToUpdate][seqHead[seqToUpdate]].name);
        seqHead[seqToUpdate]++;
        sortedIdx++;
    }

    free(seqHead);
    return sorted;
}

void loserTreeUpdate(TournamentTreeNode *loseTree, StudentInfo *infoList, int updateIdx, int *seqHead, int classNum, int studentPerClass)
{
    if (seqHead[updateIdx] >= studentPerClass)
        loseTree[classNum - 1 + updateIdx].key = -1; // sequence search complete. set corresponding leaf node as -1 to sign it
    else
        loseTree[classNum - 1 + updateIdx].key = infoList[seqHead[updateIdx]].height;

    // be careful with parent, child index. since it starts from 0, index calculating seems ridiculous
    int parent = (classNum + updateIdx) / 2 - 1;
    int lchild, rchild;
    while (parent >= 0)
    {
        lchild = (parent + 1) * 2 - 1;
        rchild = lchild + 1;
        if (loseTree[lchild].key == -1)
        {
            // if completed sequence's data found, ignore it
            loseTree[parent].key = loseTree[rchild].key;
            loseTree[parent].index = loseTree[rchild].index;
        }
        else if (loseTree[rchild].key == -1)
        {
            loseTree[parent].key = loseTree[lchild].key;
            loseTree[parent].index = loseTree[lchild].index;
        }
        else if (loseTree[lchild].key > loseTree[rchild].key)
        {
            loseTree[parent].key = loseTree[lchild].key;
            loseTree[parent].index = loseTree[lchild].index;
        }
        else
        {
            loseTree[parent].key = loseTree[rchild].key;
            loseTree[parent].index = loseTree[rchild].index;
        }
        parent = (parent + 1) / 2 - 1;
    }
}
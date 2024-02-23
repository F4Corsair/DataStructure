#include <stdio.h>
#include <stdlib.h>
#include "disjointSets.h"

Sets *setInitialize(int size)
{
    Sets *ret = malloc(sizeof(Sets));
    ret->data = malloc(sizeof(int) * size);
    // set initial value : -1 means it is root node (every node is root in initial state)
    for (int i = 0; i < size; i++)
        ret->data[i] = -1;
    ret->size = size;
    return ret;
}

void setTerminate(Sets *set)
{
    free(set->data);
    free(set);
}

void setUnion(Sets *sets, int i, int j)
{
    if (sets->data[i] >= 0)
    {
        // find root and change i to root index
        i = collapseFindRoot(sets, i);
    }
    if (sets->data[j] >= 0)
    {
        // find root and change j to root index
        j = collapseFindRoot(sets, j);
    }
    int parentVal = sets->data[i] + sets->data[j];
    if (sets->data[i] > sets->data[j])
    {
        // smaller set goes under bigger set root
        sets->data[i] = j;
        sets->data[j] = parentVal;
    }
    else
    {
        sets->data[j] = i;
        sets->data[i] = parentVal;
    }
}

int findRoot(Sets *sets, int i)
{
    for (; sets->data[i] >= 0; i = sets->data[i])
        ;
    return i;
}

int collapseFindRoot(Sets *sets, int i)
{
    int root;
    for (root = i; sets->data[root] >= 0; root = sets->data[root])
        ;
    int next, now;
    for (now = i; now != root; now = next)
    {
        next = sets->data[now];
        sets->data[now] = root;
    }
    return root;
}
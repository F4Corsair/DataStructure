#ifndef __disjointSet_EquivalentClass
#define __disjointSet_EquivalentClass

typedef struct
{
    int *data;
    int size;
} Sets;

Sets *setInitialize(int size);

void setTerminate(Sets *set);

void setUnion(Sets *sets, int i, int j);

int findRoot(Sets *sets, int i);

int collapseFindRoot(Sets *sets, int i);

#endif
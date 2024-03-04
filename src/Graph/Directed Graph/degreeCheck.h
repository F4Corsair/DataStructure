#ifndef __degreeCheck
#define __degreeCheck

typedef struct _Node
{
    int toward;
    struct _Node *next;
} Node;

typedef struct
{
    int size;
    Node **list;
} AdjLists;

typedef struct
{
    int size;
    int **matrix;
} AdjMatrix;

AdjLists *adjListsInit(int size);

void adjListTerminate(AdjLists *adj);

void adjListAppend(AdjLists *adj, int from, int toward);

void printList(AdjLists *adj);

int adjListIndegree(AdjLists *adj, int index);

int adjListOutdegree(AdjLists *adj, int index);

AdjMatrix *adjMatrixInit(int size);

void adjMatrixTerminate(AdjMatrix *adj);

void adjMatrixAppend(AdjMatrix *adj, int from, int toward);

void adjMatrixPrint(AdjMatrix *adj);

int adjMatrixIndegree(AdjMatrix *adj, int index);

int adjMatrixOutdegree(AdjMatrix *adj, int index);

#endif
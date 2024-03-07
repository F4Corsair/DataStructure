#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int cost;
    int from;
    int toward;
    struct _Node *next;
} Node;

typedef struct
{
    int vertexNum;
    Node *head;
} AdjList;

typedef struct
{
    int size;
    int *list;
} DisjointSet;

DisjointSet *disjointSetInit(int size)
{
    DisjointSet *set = malloc(sizeof(DisjointSet));
    set->list = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
        set->list[i] = -1;
    set->size = size;
    return set;
}

int findRoot(DisjointSet *set, int idx)
{
    int now = set->list[idx];
    if (now < 0)
        return idx;
    int parent = set->list[now];
    while (parent >= 0)
    {
        now = parent;
        parent = set->list[now];
    }
    return now;
}

int collapseFindRoot(DisjointSet *set, int idx)
{
    int root;
    for (root = idx; set->list[root] >= 0; root = set->list[root])
        ;
    int now, parent;
    for (now = idx; now != root; now = parent)
    {
        parent = set->list[now];
        set->list[now] = root;
    }
    return root;
}

void disjointSetUnion(DisjointSet *set, int i, int j)
{
    if (set->list[i] >= 0)
        i = collapseFindRoot(set, i);
    if (set->list[j] >= 0)
        j = collapseFindRoot(set, j);
    int parVal = set->list[i] + set->list[j];
    if (set->list[i] > set->list[j])
    {
        set->list[i] = j;
        set->list[j] = parVal;
    }
    else
    {
        set->list[i] = parVal;
        set->list[j] = i;
    }
}

void *disjointSetTerminate(DisjointSet *set)
{
    free(set->list);
    free(set);
}

AdjList *adjListInit(int vertexNum)
{
    AdjList *adj = malloc(sizeof(AdjList));
    adj->head = NULL;
    adj->vertexNum = vertexNum;
    return adj;
}

void adjListTerminate(AdjList *adj)
{
    Node *now = adj->head;
    Node *next;
    while (now != NULL)
    {
        next = now->next;
        free(now);
        now = next;
    }
    free(adj);
}

void adjListAppend(AdjList *adj, int from, int toward, int cost)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->cost = cost;
    newNode->from = from;
    newNode->toward = toward;

    // adjList is sorted in ascending order about cost
    Node *now = adj->head;
    if (now == NULL || now->cost > cost)
    {
        newNode->next = now;
        adj->head = newNode;
        return;
    }

    Node *next = now->next;
    while (next != NULL && next->cost < cost)
    {
        now = next;
        next = next->next;
    }
    newNode->next = next;
    now->next = newNode;
}

void printList(AdjList *adj)
{
    Node *now = adj->head;
    while (now != NULL)
    {
        printf("(%d -> %d) [%d] \t", now->from, now->toward, now->cost);
        now = now->next;
    }
    puts("");
}

int main(void)
{
    int vertexNum, toNode, costNode;
    char readChar;
    // read graph connections
    FILE *fp = fopen("../Graph/in1.txt", "r");
    fscanf(fp, "%d", &vertexNum);
    AdjList *adjList = adjListInit(vertexNum);
    int cnt = 0;
    for (int fromNode = 0; fromNode < vertexNum; fromNode++)
    {
        readChar = ' ';
        while (readChar != '\n')
        {
            fscanf(fp, "%d %d", &toNode, &costNode);
            adjListAppend(adjList, fromNode, toNode, costNode);
            fscanf(fp, "%c", &readChar);
        }
    }
    fclose(fp);

    printList(adjList);

    // Kruskal algorithm
    DisjointSet *set = disjointSetInit(vertexNum);
    int edgeNum = 0;

    Node *now = adjList->head;
    while (edgeNum < vertexNum - 1) // # of edge of MST = # of vertex - 1
    {
        while (now != NULL && findRoot(set, now->from) == findRoot(set, now->toward))
        { // cycle check -> if new edge make cycle, discard & test next edge
            // if new edge's from node & toward node same root == new edge make cycle
            now = now->next;
        }
        if (now == NULL)
        {
            printf("Failed to find route\n");
            break;
        }
        edgeNum++; // found avaiable & cheapest edge to add
        printf("%d - %d\n", now->from, now->toward);
        // let them have same root
        disjointSetUnion(set, now->from, now->toward);
        now = now->next;
    }

    // free head data
    disjointSetTerminate(set);
    adjListTerminate(adjList);
}
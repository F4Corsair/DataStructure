#include <stdio.h>
#include <stdlib.h>

// be caution with input data format. it applies directed expression

typedef struct _Node
{
    int cost;
    int toward;
    struct _Node *next;
} Node;

typedef struct
{
    int size;
    Node **list;
} AdjLists;

AdjLists *adjListInit(int vertexNum)
{
    AdjLists *adj = malloc(sizeof(AdjLists));
    adj->list = malloc(sizeof(Node *) * vertexNum);
    for (int i = 0; i < vertexNum; i++)
        adj->list[i] = NULL;
    adj->size = vertexNum;
    return adj;
}

void adjListTerminate(AdjLists *adj)
{
    Node *now;
    Node *next;
    for (int i = 0; i < adj->size; i++)
    {
        next = adj->list[i];
        while (next != NULL)
        {
            now = next;
            next = now->next;
            free(now);
        }
    }
    free(adj);
}

void adjListAppend(AdjLists *adj, int from, int toward, int cost)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->cost = cost;
    newNode->toward = toward;

    Node *now = adj->list[from];
    if (now == NULL || now->cost > cost)
    {
        newNode->next = now;
        adj->list[from] = newNode;
        return;
    }

    // let linked list sorted in asceding order
    Node *next = now->next;
    while (next != NULL && next->cost < cost)
    {
        now = next;
        next = next->next;
    }
    newNode->next = next;
    now->next = newNode;
}

void printList(AdjLists *adj)
{
    for (int i = 0; i < adj->size; i++)
    {
        Node *now = adj->list[i];
        printf("Vertex[%d] : ", i);
        while (now != NULL)
        {
            printf("%d ", now->toward);
            now = now->next;
        }
        puts("");
    }
}

int main(void)
{
    int vertexNum, toNode, costNode;
    char readChar;
    // read graph connections
    FILE *fp = fopen("../Graph/in1.txt", "r");
    fscanf(fp, "%d", &vertexNum);
    AdjLists *adjList = adjListInit(vertexNum);
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

    // Prim Algorithm
    int *visited = malloc(sizeof(int) * vertexNum);
    for (int i = 0; i < vertexNum; i++)
        visited[i] = 0;
    int edgeNum = 0, availPath, startVertex, minCost;

    // headAdjList is list to point available & cheapest vertex connection
    Node **headAdjList = malloc(sizeof(Node *) * adjList->size);
    for (int i = 0; i < adjList->size; i++)
        headAdjList[i] = adjList->list[i];

    printf("Input start vertex: ");
    scanf(" %d", &startVertex);
    visited[startVertex] = 1;

    while (edgeNum < vertexNum)
    {
        availPath = 0;

        // search all possible path from visited vertex -> unefficient
        // make head pointer list of AdjList at first
        // seek path from visited vertex
        // if path is unavailable(visited->visited), move head to next
        // from seeked cost, find min value and let it add new path
        // => print edge & record visited & update startvertex

        // 1. seek headAdjList 2. if visited[head], head = head->next;
        // 3. if unvisited, update minCost value & iter about all headList (also, availPath++)
        // 4. if loop done, let it add new path

        if (!availPath)
            break; // failed to find route
        else
        {
            // record visited node (lowest cost node) & print
            // set startnode as lowest cost node and loop
            edgeNum++;
        }
    }

    // free heap data
    free(headAdjList);
    adjListTerminate(adjList);
}
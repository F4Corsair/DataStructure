#include <stdio.h>
#include <stdlib.h>
#include "degreeCheck.h"

int main(void)
{
    int vertexSize;
    puts("[Adjacency Linked Lists]");
    FILE *fp = fopen("directedGraphInput.txt", "r");
    fscanf(fp, "%d", &vertexSize);
    AdjLists *adjList = adjListsInit(vertexSize);

    // read directed edge connections
    int fromNode, toNode;
    fscanf(fp, " %d %d", &fromNode, &toNode);
    while (!feof(fp))
    {
        adjListAppend(adjList, fromNode, toNode);
        fscanf(fp, " %d %d", &fromNode, &toNode);
    }
    fclose(fp);

    printList(adjList);

    // degree check about directed graph - linked lists representation
    puts("\n[Indegree]");
    for (int i = 0; i < adjList->size; i++)
        printf("Vertex[%d] : %-3d ", i, adjListIndegree(adjList, i));
    puts("\n[Outdegree]");
    for (int i = 0; i < adjList->size; i++)
        printf("Vertex[%d] : %-3d ", i, adjListOutdegree(adjList, i));
    adjListTerminate(adjList);

    puts("\n\n[Adjacency Matrix]");
    fp = fopen("directedGraphInput.txt", "r");
    fscanf(fp, "%d", &vertexSize);
    AdjMatrix *adjMatrix = adjMatrixInit(vertexSize);
    while (!feof(fp))
    {
        adjMatrixAppend(adjMatrix, fromNode, toNode);
        fscanf(fp, " %d %d", &fromNode, &toNode);
    }
    fclose(fp);

    adjMatrixPrint(adjMatrix);

    // degree check about directed graph - matrix representation
    puts("\n[Indegree]");
    for (int i = 0; i < adjMatrix->size; i++)
        printf("Vertex[%d] : %-3d ", i, adjMatrixIndegree(adjMatrix, i));
    puts("\n[Outdegree]");
    for (int i = 0; i < adjMatrix->size; i++)
        printf("Vertex[%d] : %-3d ", i, adjMatrixOutdegree(adjMatrix, i));
    puts("");
    adjMatrixTerminate(adjMatrix);
}
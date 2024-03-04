#include <stdio.h>
#include <stdlib.h>
#include "degreeCheck.h"

// directed graph. 2 way representation -> adjacency matrix and adjacency linked lists
// find each vertices indegree and outdegree of each representation

AdjLists *adjListsInit(int size)
{
    AdjLists *adj = malloc(sizeof(AdjLists));
    adj->list = malloc(sizeof(Node *) * size);
    for (int i = 0; i < size; i++)
        adj->list[i] = NULL;
    adj->size = size;
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

void adjListAppend(AdjLists *adj, int from, int toward)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->next = NULL;
    newNode->toward = toward;
    if (adj->list[from] == NULL)
    {
        adj->list[from] = newNode;
        return;
    }

    Node *now = adj->list[from];
    while (now->next != NULL)
    {
        now = now->next;
    }
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

int adjListIndegree(AdjLists *adj, int index)
{
    int cnt = 0;
    for (int i = 0; i < adj->size; i++)
    {
        Node *temp = adj->list[i];
        while (temp != NULL)
        {
            if (temp->toward == index)
                cnt++;
            temp = temp->next;
        }
    }
    return cnt;
}

int adjListOutdegree(AdjLists *adj, int index)
{
    int cnt = 0;
    Node *temp = adj->list[index];
    while (temp != NULL)
    {
        cnt++;
        temp = temp->next;
    }
    return cnt;
}

AdjMatrix *adjMatrixInit(int size)
{
    AdjMatrix *adj = malloc(sizeof(AdjMatrix));
    adj->matrix = malloc(sizeof(int *) * size);
    for (int i = 0; i < size; i++)
    {
        adj->matrix[i] = malloc(sizeof(int) * size);
        for (int j = 0; j < size; j++)
            adj->matrix[i][j] = 0;
    }
    adj->size = size;
    return adj;
}

void adjMatrixTerminate(AdjMatrix *adj)
{
    for (int i = 0; i < adj->size; i++)
    {
        free(adj->matrix[i]);
    }
    free(adj->matrix);
    free(adj);
}

void adjMatrixAppend(AdjMatrix *adj, int from, int toward)
{
    adj->matrix[from][toward] = 1;
}

void adjMatrixPrint(AdjMatrix *adj)
{
    for (int i = 0; i < adj->size; i++)
    {
        for (int j = 0; j < adj->size; j++)
            printf("%2d", adj->matrix[i][j]);
        puts("");
    }
}

int adjMatrixIndegree(AdjMatrix *adj, int index)
{
    int cnt = 0;
    for (int i = 0; i < adj->size; i++)
        if (adj->matrix[i][index] == 1)
            cnt++;

    return cnt;
}

int adjMatrixOutdegree(AdjMatrix *adj, int index)
{
    int cnt = 0;
    for (int i = 0; i < adj->size; i++)
        if (adj->matrix[index][i] == 1)
            cnt++;

    return cnt;
}

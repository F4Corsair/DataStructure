#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void linkedListInit(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
}

void listAppendFront(LinkedList *list, const int num)
{
    Node *newNode = malloc(sizeof(Node));
    if (list->head == NULL)
        list->tail = newNode;
    newNode->num = num;
    newNode->next = list->head;
    list->head = newNode;
}

Node *nodeAppendFront(Node *head, const int num)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = head;
    return newNode;
}

void listAppendRear(LinkedList *list, const int num)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = NULL;
    // consider when handling empty list
    if (list->tail != NULL)
        list->tail->next = newNode;
    list->tail = newNode;
    if (list->head == NULL)
        list->head = newNode;
}

void *nodeAppendRear(Node *head, const int num)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = NULL;

    Node *now = head;
    while (now->next)
    {
        now = now->next;
    }
    now->next = newNode;
}

// you can make addition linked list that saved deleted nodes, instead of freeing deleted nodes
// it will save cost to make new nodes when you have some saved nodes
int listPopFront(LinkedList *list)
{
    Node *temp = list->head;
    int num = temp->num;
    list->head = temp->next;
    if (list->head == NULL)
        list->tail = NULL;
    free(temp);
    return num;
}

Node *nodePopFront(Node *head, int *num)
{
    Node *temp = head->next;
    *num = head->num;
    free(head);
    return temp;
}

void listPrint(LinkedList *list)
{
    Node *now = list->head;
    Node *next = now->next;
    while (now)
    {
        printf("%d ", now->num);
        now = next;
        if (next)
            next = next->next;
    }
    puts("");
}

void nodePrint(Node *head)
{
    Node *now = head;
    Node *next = head->next;
    while (now)
    {
        printf("%d ", now->num);
        now = next;
        if (next)
            next = next->next;
    }
    puts("");
}

void listTerminate(LinkedList *list)
{
    Node *now = list->head;
    list->head = NULL;
    Node *next = now->next;
    while (now)
    {
        free(now);
        now = next;
        if (next)
            next = next->next;
    }
    list->tail = NULL;
}

void nodeTerminate(Node *head)
{
    Node *now = head;
    head = NULL;
    Node *next = now->next;
    while (now)
    {
        free(now);
        now = next;
        if (next)
            next = next->next;
    }
}
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
    else if (list->head->next == NULL) // set chain between haed - tail
        list->head->next = newNode;
}

// consider append first element, we have to return head pointer!
Node *nodeAppendRear(Node *head, const int num)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->num = num;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        return head;
    }

    Node *now = head;
    while (now->next)
    {
        now = now->next;
    }
    now->next = newNode;
    return head;
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

void listPrintInLine(LinkedList *list)
{
    listPrint(list);
    listTerminate(list);
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

void nodePrintInLine(Node *head)
{
    nodePrint(head);
    nodeTerminate(head);
}

LinkedList *concatList(LinkedList *listA, LinkedList *listB)
{
    LinkedList *newList = malloc(sizeof(LinkedList));
    linkedListInit(newList);
    Node *ptrA = listA->head;
    Node *ptrB = listB->head;
    while (ptrA)
    {
        listAppendRear(newList, ptrA->num);
        ptrA = ptrA->next;
    }
    while (ptrB)
    {
        listAppendRear(newList, ptrB->num);
        ptrB = ptrB->next;
    }

    return newList;
}

Node *concatNodeList(Node *headA, Node *headB)
{
    Node *newNode = NULL;
    // you must set newNode initail value as NULL (read nodeAppendRear())
    Node *ptrA = headA;
    Node *ptrB = headB;
    while (ptrA)
    {
        newNode = nodeAppendRear(newNode, ptrA->num);
        ptrA = ptrA->next;
    }
    while (ptrB)
    {
        newNode = nodeAppendRear(newNode, ptrB->num);
        ptrB = ptrB->next;
    }
    return newNode;
}

LinkedList *invertList(LinkedList *list)
{
    LinkedList *newList = malloc(sizeof(LinkedList));
    linkedListInit(newList);
    newList->tail = list->head;

    Node *first = list->head;
    Node *second = NULL;
    Node *third;

    while (first != NULL)
    {
        // push back former list
        third = second;
        second = malloc(sizeof(Node));
        // we copy first to prevent cutting original list connection
        second->num = first->num;
        // set first as next node of second (first == second)
        first = first->next;
        // set link
        second->next = third;
    }

    newList->head = second;

    return newList;
}

Node *invertNodeList(Node *head)
{
    Node *first = head;
    Node *second = NULL;
    Node *third;

    while (first != NULL)
    {
        // push back former list
        third = second;
        second = malloc(sizeof(Node));
        second->num = first->num;
        // set first as next node of second (first == second)
        first = first->next;
        // set link
        second->next = third;
    }
    return second;
}

void listTerminate(LinkedList *list)
{
    Node *now = list->head;
    Node *next = NULL;
    if(now != NULL)
        next = now->next;
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
    Node *next;
    if(now != NULL)
        next = now->next;
    while (now)
    {
        free(now);
        now = next;
        if (next)
            next = next->next;
    }
}
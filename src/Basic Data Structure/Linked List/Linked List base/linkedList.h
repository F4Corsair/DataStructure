#ifndef __LinkedListBase
#define __LinkedListBase

typedef struct _node
{
    int num;
    struct _node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
} LinkedList;

void linkedListInit(LinkedList *list);

void listAppendFront(LinkedList *list, const int num);

Node *nodeAppendFront(Node *node, const int num);

void listAppendRear(LinkedList *list, const int num);

Node *nodeAppendRear(Node *head, const int num);

int listPopFront(LinkedList *list);

Node *nodePopFront(Node *head, int *num);

void listPrint(LinkedList *list);

void listPrintInLine(LinkedList *list);

void nodePrint(Node *head);

void nodePrintInLine(Node *head);

LinkedList *concatList(LinkedList *listA, LinkedList *listB);

Node *concatNodeList(Node *headA, Node *headB);

LinkedList *invertList(LinkedList *list);

Node *invertNodeList(Node *head);

void listTerminate(LinkedList *list);

void nodeTerminate(Node *head);

#endif
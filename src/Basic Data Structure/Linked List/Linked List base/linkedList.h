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

void *nodeAppendRear(Node *head, const int num);

int listPopFront(LinkedList *list);

Node *nodePopFront(Node *head, int *num);

void listPrint(LinkedList *list);

void nodePrint(Node *head);

void listTerminate(LinkedList *list);

void nodeTerminate(Node *head);

#endif
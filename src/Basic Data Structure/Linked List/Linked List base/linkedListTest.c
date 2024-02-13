#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int main(void)
{
    // use LinkedList struct
    LinkedList list;
    linkedListInit(&list);
    listAppendFront(&list, 10);
    listAppendFront(&list, 20);
    listAppendRear(&list, 30);
    printf("Pop : %d\n", listPopFront(&list));
    listAppendFront(&list, 40);
    listAppendRear(&list, 50);
    listPrint(&list);
    puts("Invert");
    listPrintInLine(invertList(&list));
    puts("Concatenation");
    listPrintInLine(concatList(&list, &list));
    listTerminate(&list);

    // use head node pointer directly
    Node *head = nodeAppendFront(NULL, 10);
    head = nodeAppendFront(head, 20);
    head = nodeAppendRear(head, 30);
    int num;
    head = nodePopFront(head, &num);
    printf("Pop : %d\n", num);
    head = nodeAppendFront(head, 40);
    head = nodeAppendRear(head, 50);
    nodePrint(head);
    puts("Invert");
    nodePrintInLine(invertNodeList(head));
    puts("Concatenation");
    nodePrintInLine(concatNodeList(head, head));
    nodeTerminate(head);
}
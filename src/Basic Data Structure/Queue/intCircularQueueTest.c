#include <stdio.h>
#include <stdlib.h>
#include "intCircularQueue.h"

int main(void)
{
    IntQueue que;

    if (qInitialize(&que, 64) == -1)
    {
        puts("Failed to create Queue\n");
        return 1;
    }
    while (1)
    {
        int menu, x;
        printf("Current Data Count : %d / %d\n", qSize(&que), qCapacity(&que));
        printf("(1)Enqueue (2)Dequeue (3)Peek (4)Print (0)Terminate : ");
        scanf("%d", &menu);
        if (menu == 0)
            break;
        switch (menu)
        {
        case 1:
            printf("Data : ");
            scanf("%d", &x);
            if (enqueue(&que, x) == -1)
                puts("Failed to Enqueue");
            break;
        case 2:
            if (dequeue(&que, &x) == -1)
                puts("Failed to Enqueue");
            else
                printf("Dequeued Data : %d\n", x);
            break;
        case 3:
            if (qPeek(&que, &x) == -1)
                puts("Failed to Peek");
            else
                printf("Peek Data : %d\n", x);
            break;
        case 4:
            qPrint(&que);
            break;
        }
    }
    qTerminate(&que);
}
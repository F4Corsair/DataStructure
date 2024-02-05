#include <stdio.h>
#include <stdlib.h>
#include "intStack.h"

int main(void)
{
    IntStack s;
    if (stackInitialize(&s, 64) == -1)
    {
        puts("Failed to create Stack\n");
        return 1;
    }

    while (1)
    {
        int menu, x;
        printf("The number of current data : %d / %d\n", stackSize(&s), stackCapacity(&s));
        printf("(1)Push (2)Pop (3)Peek (4)Print (0)Exit : ");
        scanf("%d", &menu);

        if (menu == 0)
            break;
        switch (menu)
        {
        case 1:
            printf("Data : ");
            scanf("%d", &x);
            if (stackPush(&s, x) == -1)
                puts("\aErr : Failed to Push\n");
            break;
        case 2:
            if (stackPop(&s, &x) == -1)
                puts("\aErr : Failed to Pop\n");
            else
                printf("Pop data is %d\n", x);
            break;
        case 3:
            if (stackPeek(&s, &x) == -1)
                puts("\aErr : Failed to Peek");
            else
                printf("Peek data is %d\n", x);
            break;

        case 4:
            stackPrint(&s);
            break;
        }
    }
    stackTerminate(&s);
}
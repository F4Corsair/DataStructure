#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LIST_SIZE 20
#define MIN_BOUND 10
#define MAX_BOUND 30
/* counting sort counts each key value appreas & determine the position of each key value in sequence
 * this algorithm requires minimum & maximum boundary of key value. and this boundary range determines its running time
 * time complexity : O(nlogn) & stable(about same key value elements, it sorts them in reverse order -> but we traverse in reverse oreder let its stability)
 * this is non-comparative sorting algortihm
 */

void fsortAscend(int *list, int listSize, int min, int max)
{
    int *startPos = malloc(sizeof(int) * (max - min + 1));
    int *sorted = malloc(sizeof(int) * listSize);

    for (int i = 0; i <= max - min; i++)
        startPos[i] = 0; // initialize
    for (int i = 0; i < listSize; i++)
        startPos[list[i] - min]++; // count number of appearances about each key value
    for (int i = 1; i <= max - min; i++)
        startPos[i] += startPos[i - 1]; // calculate each start position of each key
    // notice : actually we calculate starting position of (key + 1) -> same as key's end position
    for (int i = listSize - 1; i >= 0; i--)          // to save its stability, traverse in reverse order
        sorted[--startPos[list[i] - min]] = list[i]; // determine position
    // we reference starting position of (key + 1) and use minused value
    // so we can say we actually refer "end position" of each key value
    for (int i = 0; i < listSize; i++)
        list[i] = sorted[i]; // copy sorted list to original list

    free(sorted);
    free(startPos);
}

void fsortDescend(int *list, int listSize, int min, int max)
{
    int *startPos = malloc(sizeof(int) * (max - min + 1));
    int *sorted = malloc(sizeof(int) * listSize);

    for (int i = 0; i <= max - min; i++)
        startPos[i] = 0;
    for (int i = 0; i < listSize; i++)
        startPos[list[i] - min]++;
    for (int i = 1; i <= max - min; i++)
        startPos[i] += startPos[i - 1];
    for (int i = 0; i < listSize; i++)
    { // to save its stability, list traverse direction is inversed
        int val = startPos[list[i] - min]--;
        sorted[listSize - val] = list[i];
    }
    for (int i = 0; i < listSize; i++)
        list[i] = sorted[i];

    free(sorted);
    free(startPos);
}

void printList(int *list, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%3d ", list[i]);
    }
    puts("");
}

int main(void)
{
    srand(time(NULL));
    int numList[LIST_SIZE];
    int size = LIST_SIZE;

    // we will sort random integer data within boundary range
    for (int i = 0; i < size; i++)
        numList[i] = rand() % (MAX_BOUND - MIN_BOUND + 1) + MIN_BOUND;

    puts("[Original List]");
    printList(numList, size);

    puts("[Sorted_Ascend]");
    fsortAscend(numList, size, MIN_BOUND, MAX_BOUND);
    printList(numList, size);

    puts("[Sorted_Descend]");
    fsortDescend(numList, size, MIN_BOUND, MAX_BOUND);
    printList(numList, size);
}
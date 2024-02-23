#include <stdio.h>
#include <stdlib.h>
#include "disjointSets.h"

int main(void)
{
    FILE *fp = fopen("in.txt", "r");
    int numSize;
    fscanf(fp, "%d", &numSize);
    Sets *sets = setInitialize(numSize);

    int readA, readB;
    // read 2 numbers, which has equivalent connection between them
    fscanf(fp, " %d %d", &readA, &readB);
    while (!feof(fp))
    {
        setUnion(sets, readA, readB);
        fscanf(fp, " %d %d", &readA, &readB);
    }
    fclose(fp);

    // print equivalence connections
    int cnt = 0;
    int *visited = malloc(sizeof(int) * numSize);
    for (int i = 0; i < numSize; i++)
        visited[i] = 0;
    for (int i = 0; i < numSize; i++)
    {
        if (!visited[i])
        {
            visited[i] = 1;
            printf("Set %d : %d ", cnt++, i);
            int root = findRoot(sets, i);
            for (int j = i + 1; j < numSize; j++)
            {
                int temp = findRoot(sets, j);
                if (temp == root)
                {
                    printf("%d ", j);
                    visited[j] = 1;
                }
            }
            puts("");
        }
    }

    // free heap data
    setTerminate(sets);
}
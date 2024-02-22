#include <stdio.h>
#include <stdlib.h>
#include "disjointSets.h"

int main(void)
{
    FILE *fp = fopen("in.txt", "r");
    int numSize;
    fscanf(fp, "%d", &numSize);
    fclose(fp);
}
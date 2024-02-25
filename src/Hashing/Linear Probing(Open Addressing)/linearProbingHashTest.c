#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linearProbingHash.h"
// if using division(modulo) as hash funcitnon, u'd better set bucket size as prime number
#define BUCKET_SIZE 19
#define SLOT_SIZE 2

int main(void)
{
    char ***hashTable = strHashTableInit(BUCKET_SIZE, SLOT_SIZE);

    // read elements from file
    char readName[STR_SIZE];
    FILE *fp = fopen("in.txt", "r");
    fscanf(fp, "%s", readName);
    while (!feof(fp))
    {
        strHashTableAdd(hashTable, readName, BUCKET_SIZE, SLOT_SIZE);
        fscanf(fp, "%s", readName);
    }
    fclose(fp);

    puts("");
    strHashTablePrint(hashTable, BUCKET_SIZE, SLOT_SIZE);

    // search table : determine existence of element
    puts("\n=Check Existence=");
    char *searchList[10] = {"RUBY", "RUCY", "HOLLY", "OLIVIA", "BROWNY", "MICHEL", "LILY", NULL};
    for (int i = 0; searchList[i] != NULL; i++)
    {
        int existence = strHashIsExist(hashTable, searchList[i], BUCKET_SIZE, SLOT_SIZE);
        printf("%s %s\n", searchList[i], existence ? "exists" : "does not exist");
    }

    // free heap
    strHashTableTerminate(hashTable, BUCKET_SIZE, SLOT_SIZE);
}
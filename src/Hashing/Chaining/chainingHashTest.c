#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chainingHash.h"
// if using division(modulo) as hash funcitnon, u'd better set bucket size as prime number
#define BUCKET_SIZE 19

int main(void)
{
    HashNode **hashTable = strHashTableInit(BUCKET_SIZE);

    // read elements from file
    char readName[STR_SIZE];
    FILE *fp = fopen("in.txt", "r");
    fscanf(fp, "%s", readName);
    while (!feof(fp))
    {
        strHashTableAdd(hashTable, readName, BUCKET_SIZE);
        fscanf(fp, "%s", readName);
    }
    fclose(fp);

    puts("");
    strHashTablePrint(hashTable, BUCKET_SIZE);

    // search table : determine existence of element
    puts("\n=Check Existence=");
    char *searchList[10] = {"RUBY", "RUCY", "HOLLY", "OLIVIA", "BROWNY", "MICHEL", "LILY", NULL};
    for (int i = 0; searchList[i] != NULL; i++)
    {
        int existence = strHashIsExist(hashTable, searchList[i], BUCKET_SIZE);
        printf("%s %s\n", searchList[i], existence ? "exists" : "does not exist");
    }

    // free heap memory
    strHashTableTerminate(hashTable, BUCKET_SIZE);
}
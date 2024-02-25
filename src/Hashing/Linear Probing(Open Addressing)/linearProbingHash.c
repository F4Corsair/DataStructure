#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linearProbingHash.h"

int strFindHashKey(char *str, int div, int printLog)
{
    int sum = 0;
    for (int i = 0; i < strlen(str); i++)
        sum += str[i]; // convert keys to integer & summate
    if (printLog)
        printf("%s [%d]\n", str, sum % div);
    return sum % div;
    // Hash Function : Division
    // example of another hash function : mid-square, folding, digit analysis
}

char ***strHashTableInit(int bucketSize, int slotSize)
{
    char ***table = malloc(sizeof(char **) * bucketSize);
    for (int i = 0; i < bucketSize; i++)
    {
        table[i] = malloc(sizeof(char *) * slotSize);
        for (int j = 0; j < slotSize; j++)
            table[i][j] = NULL;
    }
    return table;
}

void strHashTableTerminate(char ***table, int bucketSize, int slotSize)
{
    for (int i = 0; i < bucketSize; i++)
    {
        for (int j = 0; j < slotSize; j++)
        {
            if (table[i][j] == NULL)
                break;
            else
                free(table[i][j]);
        }
        free(table[i]);
    }
    free(table);
}

void strHashTableAdd(char ***table, char *str, int bucketSize, int slotSize)
{
    int hashKey = strFindHashKey(str, bucketSize, 1);
    int curBucket = hashKey;
    while (table[curBucket][slotSize - 1] != NULL)
    {
        // in linear probing, if overflow occured on some bucket,
        // use next bucket to add new item
        curBucket = (curBucket + 1) % bucketSize;
        if (curBucket == hashKey)
        {
            // you can also expand hash table instead of this
            fprintf(stderr, "hash table is full\n");
            return;
        }
    }
    int curSlot = 0;
    while (table[curBucket][curSlot] != NULL)
        curSlot++;
    // if you read string data from scnaf, some compiler save it on stack frame, not heap
    // to prevent that stack frame free & data erase, we will alloc heap & copy it
    char *newStr = malloc(sizeof(char) * STR_SIZE);
    strcpy(newStr, str);
    table[curBucket][curSlot] = newStr;
}

void strHashTablePrint(char ***table, int bucketSize, int slotSize)
{
    for (int i = 0; i < bucketSize; i++)
    {
        printf("Bucket[%d] : ", i);
        for (int j = 0; j < slotSize; j++)
        {
            if (table[i][j] == NULL)
                break;
            else
                printf("%*s", STR_SIZE, table[i][j]);
        }
        puts("");
    }
}

int strHashIsExist(char ***table, char *str, int bucketSize, int slotSize)
{
    int hashKey = strFindHashKey(str, bucketSize, 0);
    int curBucket = hashKey;
    char *temp;
    while (table[curBucket][slotSize - 1] != NULL)
    {
        // find matching element
        for (int i = 0; i < slotSize; i++)
        {
            temp = table[curBucket][i];
            if (strcmp(str, temp) == 0)
                return 1;
        }
        // if not found && slot full -> search next bucket
        curBucket = (curBucket + 1) % bucketSize;
        if (curBucket == hashKey)
            return 0;
    }
    // slot is not full
    // find matching element
    for (int i = 0; i < slotSize; i++)
    {
        temp = table[curBucket][i];
        if (temp == NULL)
            return 0;
        if (strcmp(str, temp) == 0)
            return 1;
    }
}
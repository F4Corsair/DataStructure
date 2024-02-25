#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chainingHash.h"

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

HashNode **strHashTableInit(int bucketSize)
{
    HashNode **table = malloc(sizeof(HashNode *) * bucketSize);
    for (int i = 0; i < bucketSize; i++)
        table[i] = NULL;
    return table;
}

void strHashTableTerminate(HashNode **table, int bucketSize)
{
    HashNode *now;
    HashNode *next;
    for (int i = 0; i < bucketSize; i++)
    {
        now = table[i];
        while (now != NULL)
        {
            next = now->next;
            free(now);
            now = next;
        }
    }
    free(table);
}

void strHashTableAdd(HashNode **table, char *str, int bucketSize)
{
    int hashKey = strFindHashKey(str, bucketSize, 1);
    HashNode *newNode = malloc(sizeof(HashNode));
    newNode->next = NULL;
    strcpy(newNode->str, str);
    if (table[hashKey] == NULL)
    {
        table[hashKey] = newNode;
        return;
    }
    HashNode *ptr = table[hashKey];
    while (ptr->next != NULL)
        ptr = ptr->next;
    ptr->next = newNode;
}

void strHashTablePrint(HashNode **table, int bucketSize)
{
    for (int i = 0; i < bucketSize; i++)
    {
        printf("Bucket[%d] : ", i);
        HashNode *ptr = table[i];
        while (ptr != NULL)
        {
            printf("%*s", STR_SIZE, ptr->str);
            ptr = ptr->next;
        }
        puts("");
    }
}

int strHashIsExist(HashNode **table, char *str, int bucketSize)
{
    int hashKey = strFindHashKey(str, bucketSize, 0);
    HashNode *ptr = table[hashKey];
    while (ptr != NULL)
    {
        if (strcmp(ptr->str, str) == 0)
            return 1;
        ptr = ptr->next;
    }
    return 0;
}
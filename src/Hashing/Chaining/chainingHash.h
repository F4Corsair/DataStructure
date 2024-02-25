#ifndef __chainingHash
#define __chainingHash

#define STR_SIZE 10

typedef struct _HashNode
{
    char str[STR_SIZE];
    struct _HashNode *next;
} HashNode;

int strFindHashKey(char *str, int div, int printLog);

HashNode **strHashTableInit(int bucketSize);

void strHashTableTerminate(HashNode **table, int bucketSize);

void strHashTableAdd(HashNode **table, char *str, int bucketSize);

void strHashTablePrint(HashNode **table, int bucketSize);

int strHashIsExist(HashNode **table, char *str, int bucketSize);

#endif
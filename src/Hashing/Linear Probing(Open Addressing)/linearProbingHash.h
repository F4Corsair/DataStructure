#ifndef __linearProbingHash
#define __linearProbingHash

#define STR_SIZE 10

int strFindHashKey(char *str, int div, int printLog);

char ***strHashTableInit(int bucketSize, int slotSize);

void strHashTableTerminate(char ***table, int bucketSize, int slotSize);

void strHashTableAdd(char ***table, char *str, int bucketSize, int slotSize);

void strHashTablePrint(char ***table, int bucketSize, int slotSize);

void strHashTablePrint(char ***table, int bucketSize, int slotSize);

int strHashIsExist(char ***table, char *str, int bucketSize, int slotSize);

#endif
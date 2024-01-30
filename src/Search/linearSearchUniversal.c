#include <stdio.h>

void *seqsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char *x = (char *)base;
    for (int i = 0; i < (int)(nmemb); i++)
    {
        if (!compar(&x[i * size], key))
            return &x[i * size];
    }
    return NULL;
}

int int_cmp(const int *a, const int *b)
{
    return *a < *b ? -1 : (*a > *b ? 1 : 0);
}

int main(void)
{
    int searchNum;
    int numbers[] = {1, 9, 2, 9, 4, 6, 7, 9};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < size; i++)
        printf("%-3d", numbers[i]);
    printf("\nNumber to Search : ");
    scanf("%d", &searchNum);
    int *p = seqsearch(&searchNum, numbers, size, sizeof(int), (int (*)(const void *, const void *))int_cmp);
    if (p == NULL)
        printf("Failed to Search\n");
    else
        printf("Index of %d in number list : %d\n", searchNum, (int)(p - numbers));
}
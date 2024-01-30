#include <stdio.h>

void *binsearch(const void *key, const void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    char *x = (char *)base;
    int head = 0;
    int rear = nmemb - 1;
    int mid, flag;
    while (head <= rear)
    {
        mid = (head + rear) / 2;
        flag = compar(&x[mid * size], key);
        if (!flag)
            return &x[mid * size];
        else if (flag > 0)
            rear = mid - 1;
        else
            head = mid + 1;
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
    int numbers[] = {15, 18, 18, 23, 39, 57, 68, 72}; // numbers must be sorted in ascending order
    int size = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < size; i++)
        printf("%-3d", numbers[i]);
    printf("\nNumber to Search : ");
    scanf("%d", &searchNum);
    int *p = binsearch(&searchNum, numbers, size, sizeof(int), (int (*)(const void *, const void *))int_cmp);
    if (p == NULL)
        printf("Failed to Search\n");
    else
        printf("Index of %d in number list : %d\n", searchNum, (int)(p - numbers));
}
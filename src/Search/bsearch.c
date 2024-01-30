#include <stdio.h>
#include <stdlib.h>

int int_cmp(const int *a, const int *b)
{
    return *a > *b ? 1 : (*a < *b ? -1 : 0);
} // bsearch requires compare function with this format

int main(void)
{
    int numbers[] = {15, 18, 18, 23, 39, 57, 68, 72}; // numbers must be sorted in ascending order
    int searchNum;

    printf("Number to Search : ");
    scanf("%d", &searchNum);

    int *idx = bsearch(&searchNum, numbers, sizeof(numbers) / sizeof(int), sizeof(int), (int (*)(const void *, const void *))int_cmp);

    if (idx == NULL)
        puts("Failed to search");
    else
        printf("Index of %d in number list : %d\n", searchNum, (int)(idx - numbers));
}

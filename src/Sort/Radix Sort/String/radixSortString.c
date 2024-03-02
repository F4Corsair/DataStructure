#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26

/* sort about radix(base), starting from LSD or MSD will determine its sorting order
 * if you sort about 10 base(radix), each digit in same position will be key of each element
 * radix sort commonly applied to sort intger or english words in lexicographic order(26 radix) -> you must consider its length
 * in application, we can sort poker card about shape first & sort about face number when they have same shape
 * LSD(Least Significant Digit) radix sort : keys in same length sorted lexicographically -> stable
 * MSD(Most Significant Digit) radix sort : suit for string sort or fixed length integer -> unstable
 * time complexity : O(nw) such that n : # of keys, w : key length
 * this is non-comparative sorting algortihm
 */

// input data
char *data[] = {"people", "day", "man", "thing", "time", "mother", "school", "friend", "year", "work", "home", "house", "way", "back", "country", "moon", "month", "parents", "street", "summer"};

int getSymbolNumber(char *str, int idx)
{
    if (strlen(str) <= idx)
        return 0;
    return str[idx] - 'a';
}

int radixSort(char **strList, int *linkList, int digit, int radix, int listSize)
{
    int first = 1;
    int last, key;
    for (int i = 1; i < listSize; i++)
        linkList[i] = i + 1;
    linkList[listSize] = 0;
    // 0 signals end of list link

    // use linked list to implement radix sort -> save link list's front, rear link
    int *front = malloc(sizeof(int) * radix);
    int *rear = malloc(sizeof(int) * radix);
    // sort in lexicographical order -> starting from MSD
    for (int curDigit = digit - 1; curDigit >= 0; curDigit--)
    {
        for (int j = 0; j < radix; j++)
            front[j] = 0; // initialize
        for (int cur = first; cur != 0; cur = linkList[cur])
        {
            key = getSymbolNumber(data[cur - 1], curDigit);
            // connect element's index to link list
            if (front[key] == 0)
                front[key] = cur;
            else
                linkList[rear[key]] = cur; // write where to jump next
            rear[key] = cur;
        }
        for (key = 0; front[key] == 0; key++)
            ; // set key as first order element's key
        first = front[key];
        last = rear[key];
        for (key++; key < radix; key++)
        {
            if (front[key])
            {
                linkList[last] = front[key]; // end of key's link = next key's first
                last = rear[key];
            }
        }
        linkList[last] = 0;
    }

    free(front);
    free(rear);
    return first;
}

void printList(char **list, int size)
{
    for (int i = 0; i < size; i++)
        printf("%9s", list[i]);
    puts("");
}

int main(void)
{
    int listSize = sizeof(data) / sizeof(char *);
    puts("[Original List]");
    printList(data, listSize);

    // get max length of data list
    int maxStrLength = strlen(data[0]);
    for (int i = 1; i < listSize; i++)
    {
        int temp = strlen(data[i]);
        if (temp > maxStrLength)
            maxStrLength = temp;
    }

    puts("[After Radix Sort]");
    int *linkList = malloc(sizeof(int) * (listSize + 1)); // link list != linked List. it shows what index to search next in data list
    int firstIdx = radixSort(data, linkList, maxStrLength, ALPHABET_SIZE, listSize);
    int idx = firstIdx;
    // print sorted list
    while (idx != 0)
    {
        printf("%9s", data[idx - 1]);
        idx = linkList[idx];
    }
    puts("");

    free(linkList);
}
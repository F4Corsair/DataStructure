#include <stdio.h>
#include <stdlib.h>
#include "sparseMatrix.h"

Term *readNormalMatrix(char *fileName)
{
    int readRow, readCol;
    FILE *fp = fopen(fileName, "r");
    fscanf(fp, "%d %d", &readRow, &readCol);
    Term *term = malloc(sizeof(Term) * (readRow * readCol + 1));
    term[0].row = readRow;
    term[0].col = readCol;

    int readNum, idx = 0;
    for (int i = 0; i < readRow; i++)
    {
        for (int j = 0; j < readCol; j++)
        {
            fscanf(fp, " %d", &readNum);
            if (readNum != 0)
            {
                term[++idx].row = i;
                term[idx].col = j;
                term[idx].val = readNum;
            }
        }
    }
    term[0].val = idx;
    fclose(fp);
    return term;
}

Term *readSparseMatrix(char *fileName)
{
    int readRow, readCol, readVal;
    FILE *fp = fopen(fileName, "r");
    fscanf(fp, "%d %d %d", &readRow, &readCol, &readVal);
    Term *term = malloc(sizeof(Term) * (readVal + 1));
    term[0].row = readRow;
    term[0].col = readCol;
    term[0].val = readVal;
    for (int i = 1; i <= term[0].val; i++)
    {
        fscanf(fp, " %d %d %d", &readRow, &readCol, &readVal);
        term[i].row = readRow;
        term[i].col = readCol;
        term[i].val = readVal;
    }
    fclose(fp);
    return term;
}

void freeSparseMatrix(Term *term)
{
    free(term);
}

void printSparseMatrix(Term *term)
{
    printf("Row : %d\nCol : %d\n# of Elements : %d\n", term[0].row, term[0].col, term[0].val);
    for (int i = 1; i <= term[0].val; i++)
    {
        printf("matrix[%d][%d] : %d\n", term[i].row, term[i].col, term[i].val);
    }
}

void printOriginalMatrix(Term *term)
{
    int idx = 1;
    int row = term[0].row, col = term[0].col;
    printf("Row : %d\nCol : %d\n# of Elements : %d\n", row, col, term[0].val);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (term[idx].row == i && term[idx].col == j)
                printf("%5d", term[idx++].val);
            else
                printf("%5d", 0);
        }
        puts("");
    }
    puts("");
}

Term *transpose(Term *a)
{
    int eleSize = a[0].val;
    Term *b = malloc(sizeof(Term) * (eleSize + 1));
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].val = eleSize;
    // it will keep the values sorted in ascending order even when transposed
    if (eleSize > 0)
    {
        int idx = 1;
        for (int i = 0; i < a[0].col; i++)
            for (int j = 1; j <= eleSize; j++)
                if (a[j].col == i) // from origianl matrix, search (ori.col == trans.row)
                {
                    b[idx].row = a[j].col;
                    b[idx].col = a[j].row;
                    b[idx].val = a[j].val;
                    idx++;
                }
    }

    return b;
} // time complexity : O(colSize * elementSize)

Term *fastTranspose(Term *a)
{
    int eleSize = a[0].val;
    int colSize = a[0].col;
    int *rowTerms = malloc(sizeof(int) * colSize);
    int *startingPos = malloc(sizeof(int) * colSize);
    Term *b = malloc(sizeof(Term) * (eleSize + 1));
    b[0].row = colSize;
    b[0].col = a[0].row;
    b[0].val = eleSize;
    // keep values sorted in ascending order
    if (eleSize > 0)
    {
        for (int i = 0; i < colSize; i++)
            rowTerms[i] = 0;
        for (int i = 1; i <= eleSize; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1; // idx 0 stores matrix data. so, we start from idx 1
        for (int i = 1; i < colSize; i++)
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        for (int i = 1; i <= eleSize; i++)
        {
            int idx = startingPos[a[i].col]++;
            b[idx].row = a[i].col;
            b[idx].col = a[i].row;
            b[idx].val = a[i].val;
        }
    }

    puts("");
    free(rowTerms);
    free(startingPos);
    return b;
} // time complexity : O(colSize+eleSize)
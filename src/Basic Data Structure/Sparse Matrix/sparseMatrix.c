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

void *_fastTranspose(const Term *a, Term *b)
{
    int eleSize = a[0].val;
    int colSize = a[0].col;
    int *rowTerms = malloc(sizeof(int) * colSize);
    int *startingPos = malloc(sizeof(int) * colSize);
    b[0].row = colSize;
    b[0].col = a[0].row;
    b[0].val = eleSize;
    if (eleSize > 0)
    {
        for (int i = 0; i < colSize; i++)
            rowTerms[i] = 0;
        for (int i = 1; i <= eleSize; i++)
            rowTerms[a[i].col]++;
        startingPos[0] = 1;
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
}

void copyMatrix(const Term *src, Term *dest)
{
    for (int i = 0; i <= src[0].val; i++)
    {
        dest[i].row = src[i].row;
        dest[i].col = src[i].col;
        dest[i].val = src[i].val;
    }
}

void _storeSum(Term *a, int *ptr, int row, int col, int *sum)
{
    if (*sum != 0)
    {
        a[++*ptr].row = row;
        a[*ptr].col = col;
        a[*ptr].val = *sum;
        *sum = 0;
    }
}

int _compare_int(int a, int b)
{
    return a > b ? 1 : (a < b ? -1 : 0);
}

Term *multiplicateMatrix(const Term *_a, const Term *_b)
{
    if (_a[0].col != _b[0].row)
    {
        fprintf(stderr, "Matrix Multiplication : Incompatilbe matricies\n");
        exit(1);
    }
    Term *a = malloc(sizeof(Term) * (_a[0].val + 1));
    copyMatrix(_a, a);
    Term *b = malloc(sizeof(Term) * (_b[0].val + 1));
    _fastTranspose(_b, b);
    Term *result = malloc(sizeof(Term) * (_a[0].row * _b[0].col + 1));
    result[0].row = a[0].row;
    result[0].col = b[0].col;

    int sum = 0, eleNum = 0;
    int row = a[1].row;
    int rowBegin = 1;
    for (int i = 1; i <= a[0].val;)
    {
        int col = b[1].row;
        for (int j = 1; j <= b[0].val + 1;)
        {
            if (a[i].row != row)
            {
                _storeSum(result, &eleNum, row, col, &sum);
                i = rowBegin;
                for (; b[j].row == col; j++)
                    ;           // search done about same b column. so skip it
                col = b[j].row; // set next col to search
            }
            else if (b[j].row != col)
            {
                _storeSum(result, &eleNum, row, col, &sum);
                i = rowBegin;
                // we don't need to skip b col, because there's nothing to skip (since its condition)
                col = b[j].row; // done summation about one column. set column to next one
            }
            else
                switch (_compare_int(a[i].col, b[j].col))
                { // if a col != b row, skip it
                case -1:
                    i++;
                    break;
                case 0:
                    sum += (a[i++].val * b[j++].val); // stack sum only if a col == b row
                    break;
                case 1:
                    j++;
                }
        }

        for (; a[i].row == row; i++)
            ; // search done about same a row. so skip it
        rowBegin = i;
        row = a[i].row; // row value must be changed
    }
    result[0].val = eleNum;

    Term *out = malloc(sizeof(Term) * (eleNum + 1));
    copyMatrix(result, out);
    free(a);
    free(b);
    free(result);
    return out;
}
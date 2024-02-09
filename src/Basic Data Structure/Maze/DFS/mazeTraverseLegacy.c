#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STK_SIZE 100
#define STK_APPEND_SIZE 50

typedef struct
{
    int vert;
    int horiz;
} Offset;

Offset move[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; // N -> NE ... -> NW (clockwise)

typedef struct
{
    int row;
    int col;
    int dir;
} Element;

typedef struct
{
    int capacity;
    int idx;
    Element *e;
} Stack;

int stackInitialize(Stack *stk, const int size)
{
    stk->idx = 0;
    if (!(stk->e = malloc(sizeof(Element) * size)))
    {
        puts("Malloc Err!");
        return 1;
    }
    stk->capacity = size;
    return 0;
}

int stackSizeUp(Stack *stk)
{
    stk->e = realloc(stk->e, sizeof(Element) * (stk->capacity + STK_APPEND_SIZE));
    if (!stk->e)
    {
        puts("Realloc Err!");
        return 1;
    }
    stk->capacity += STK_APPEND_SIZE;
    return 0;
}

int stackIsFull(Stack *stk)
{
    return stk->capacity <= stk->idx;
}

int stackIsEmpty(Stack *stk)
{
    return stk->idx <= 0;
}

int stackPush(Stack *stk, const Element e)
{
    if (stackIsFull(stk))
        if (stackSizeUp(stk))
            return 1;
    stk->e[stk->idx].row = e.row;
    stk->e[stk->idx].col = e.col;
    stk->e[stk->idx].dir = e.dir;
    stk->idx++;
    return 0;
}

int stackPop(Stack *stk, Element *e)
{
    if (stackIsEmpty(stk))
        return 1;
    stk->idx--;
    e->row = stk->e[stk->idx].row;
    e->col = stk->e[stk->idx].col;
    e->dir = stk->e[stk->idx].dir;
    return 0;
}

void stackTerminate(Stack *stk)
{
    if (!stk->e)
        return;
    free(stk->e);
    stk->idx = stk->capacity = 0;
}

void mazePrint(int **map, const int rowSize, const int colSize, const int stRow, const int stCol, const int edRow, const int edCol)
{
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (i == stRow && j == stCol)
                printf("%s ", "S");
            else if (i == edRow && j == edCol)
                printf("%s ", "F");
            else
                printf("%d ", map[i + 1][j + 1]);
        }
        puts("");
    }
}

void mazePathMake(Stack *stk, int **map, const int rowSize, const int colSize, const int stRow, const int stCol, const int edRow, const int edCol)
{
    int row, col;
    for (int i = 0; i < stk->idx; i++)
    {
        row = stk->e[i].row;
        col = stk->e[i].col;
        map[row][col] = 2;
    }
}
void mazePathPrint(int **map, const int rowSize, const int colSize, const int stRow, const int stCol, const int edRow, const int edCol)
{
    // add path print function!!!
    for (int i = 0; i < rowSize; i++)
    {
        for (int j = 0; j < colSize; j++)
        {
            if (i == stRow && j == stCol)
                printf("%s ", "S");
            else if (i == edRow && j == edCol)
                printf("%s ", "F");
            else if (map[i + 1][j + 1])
                printf("%s ", map[i + 1][j + 1] == 2 ? "X" : "1");
            else
                printf("0 ");
        }
        puts("");
    }
}

int main(void)
{
    int mazeRow, mazeCol;
    int startRow, startCol, endRow, endCol;
    FILE *fp = fopen("maze2.txt", "r");
    fscanf(fp, "%d %d", &mazeRow, &mazeCol);
    int **mazeMap = malloc(sizeof(int *) * (mazeRow + 2));
    int **mazeMark = malloc(sizeof(int *) * (mazeRow + 2));
    for (int i = 0; i < mazeRow + 2; i++)
    {
        mazeMap[i] = malloc(sizeof(int) * (mazeCol + 2));
        mazeMark[i] = malloc(sizeof(int) * (mazeCol + 2));
        for (int j = 0; j < mazeCol + 2; j++)
        {
            mazeMark[i][j] = 0;
            if (i == 0 || i == mazeRow + 1 || j == 0 || j == mazeCol + 1)
                mazeMap[i][j] = 1;
            else
                fscanf(fp, " %d", &mazeMap[i][j]);
        }
    }
    fscanf(fp, "%d %d %d %d", &startRow, &startCol, &endRow, &endCol);
    fclose(fp);
    /*Refactr start, end point for easy calculation*/
    puts("[MAZE]");
    mazePrint(mazeMap, mazeRow, mazeCol, startRow, startCol, endRow, endCol);

    int flag = 0;
    Element position;
    int nextRow, nextCol;
    Stack stk;
    if (stackInitialize(&stk, MAX_STK_SIZE))
        return 1;
    position.row = startRow + 1;
    position.col = startCol + 1;
    position.dir = 0;
    stackPush(&stk, position);
    while (!flag && !stackIsEmpty(&stk))
    {
        stackPop(&stk, &position);
        // printf("%d %d %d\n", position.row, position.col, position.dir);

        while (!flag && position.dir < 8)
        {
            nextRow = position.row + move[position.dir].vert;
            nextCol = position.col + move[position.dir].horiz;
            if (nextRow == endRow + 1 && nextCol == endCol + 1)
            {
                position.dir++;
                stackPush(&stk, position);
                flag = 1;
            }
            else if (!mazeMap[nextRow][nextCol] && !mazeMark[nextRow][nextCol])
            {
                mazeMark[nextRow][nextCol] = 1;
                position.dir++;
                stackPush(&stk, position);
                position.row = nextRow;
                position.col = nextCol;
                position.dir = 0;
            }
            else
                position.dir++;
        }
    }
    // print
    if (!flag)
        printf("\nNo Path\n");
    else
    {
        puts("[PATH]");
        mazePathMake(&stk, mazeMap, mazeRow, mazeCol, startRow, startCol, endRow, endCol);
        mazePathPrint(mazeMap, mazeRow, mazeCol, startRow, startCol, endRow, endCol);
    }
    stackTerminate(&stk);
    // free mazeMap, mazeMark
    for (int i = 0; i < mazeRow + 2; i++)
    {
        free(mazeMap[i]);
        free(mazeMark[i]);
    }
    free(mazeMap);
    free(mazeMark);
}
#include <stdio.h>
#include <stdlib.h>
#include "mazeTraverseDFS.h"
#define MAZE_STACK_INIT_SIZE 20

Offset step[8] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}}; // N -> NE ... -> NW (clockwise)

Maze *mazeFileRead(char *fileName)
{
    Maze *maze = malloc(sizeof(Maze));
    FILE *fp = fopen(fileName, "r");
    fscanf(fp, "%d %d", &maze->row, &maze->col);

    // memory allocation - consider its boundary(+2)
    maze->map = malloc(sizeof(int *) * (maze->row + 2));
    maze->mark = malloc(sizeof(int *) * (maze->row + 2));

    // read map & memory allocation
    for (int i = 0; i < maze->row + 2; i++)
    {
        maze->map[i] = malloc(sizeof(int) * (maze->col + 2));
        maze->mark[i] = malloc(sizeof(int) * (maze->col + 2));
        for (int j = 0; j < maze->col + 2; j++)
        {
            maze->mark[i][j] = 0;
            if (i == 0 || i == maze->row + 1 || j == 0 || j == maze->col + 1)
                maze->map[i][j] = 1; // set boundary as 1(wall)
            else
                fscanf(fp, " %d", &maze->map[i][j]);
        }
    }
    fscanf(fp, " %d %d %d %d", &maze->startRow, &maze->startCol, &maze->endRow, &maze->endCol);
    fclose(fp);

    return maze;
}

void mazeClose(Maze *maze)
{
    for (int i = 0; i < maze->row + 2; i++)
    {
        free(maze->map[i]);
        free(maze->mark[i]);
    }
    free(maze->map);
    free(maze->mark);
    free(maze);
}

void mazePrint(Maze *maze)
{
    for (int i = 0; i < maze->row; i++)
    {
        for (int j = 0; j < maze->col; j++)
        {
            if (i == maze->startRow && j == maze->startCol)
                printf("%s ", "S");
            else if (i == maze->endRow && j == maze->endCol)
                printf("%s ", "F");
            else
                printf("%d ", maze->map[i + 1][j + 1]);
        }
        puts("");
    }
}

int traceStackInit(TraceStack *ts, const int stackSize)
{
    ts->top = 0;
    if ((ts->stack = malloc(sizeof(Trace) * stackSize)) == NULL)
    {
        puts("Memory Allocation Error");
        return 1;
    }
    ts->capacity = stackSize;
    return 0;
}

int traceStackPush(TraceStack *ts, Trace trace)
{
    if (ts->top >= ts->capacity)
    {
        if ((ts->stack = realloc(ts->stack, sizeof(Trace) * ts->capacity * 2)) == NULL)
        {
            puts("Memory Re-Allocation Error");
            return 1;
        }
    }
    ts->stack[ts->top].row = trace.row;
    ts->stack[ts->top].col = trace.col;
    ts->stack[ts->top].direction = trace.direction;
    ts->top++;
    return 0;
}

int traceStackPop(TraceStack *ts, Trace *trace)
{
    if (ts->top <= 0)
        return 1;
    ts->top--;
    trace->row = ts->stack[ts->top].row;
    trace->col = ts->stack[ts->top].col;
    trace->direction = ts->stack[ts->top].direction;
    return 0;
}

void traceStackTerminate(TraceStack *ts)
{
    if (ts->stack == NULL)
        return;
    free(ts->stack);
    ts->top = ts->capacity = 0;
}

void mazePathMake(TraceStack *ts, int **map)
{
    for (int i = 0; i < ts->top; i++)
    {
        map[ts->stack[i].row][ts->stack[i].col] = 2;
    }
}

// print path (which get from mazePathMake()) as "X" character
void mazePathPrint(Maze *maze)
{
    for (int i = 0; i < maze->row; i++)
    {
        for (int j = 0; j < maze->col; j++)
        {
            if (i == maze->startRow && j == maze->startCol)
                printf("%s ", "S");
            else if (i == maze->endRow && j == maze->endCol)
                printf("%s ", "F");
            else if (maze->map[i + 1][j + 1])
                printf("%s ", maze->map[i + 1][j + 1] == 2 ? "X" : "1");
            else
                printf("0 ");
        }
        puts("");
    }
}

int mazeTraverse(TraceStack *ts, Maze *maze)
{
    int flag = 0;
    Trace curPosition;
    int nextRow, nextCol;
    if (traceStackInit(ts, MAZE_STACK_INIT_SIZE))
        return 0;
    // push initial position data
    curPosition.row = maze->startRow + 1;
    curPosition.col = maze->startCol + 1;
    curPosition.direction = 0;
    traceStackPush(ts, curPosition);

    while (flag == 0 && ts->top > 0)
    {
        traceStackPop(ts, &curPosition);
        while (flag == 0 && curPosition.direction < 8)
        {
            // set next position
            nextRow = curPosition.row + step[curPosition.direction].vertical;
            nextCol = curPosition.col + step[curPosition.direction].horizontal;
            // seek next position
            if (nextRow == maze->endRow + 1 && nextCol == maze->endCol + 1)
            {
                // endpoint reach
                traceStackPush(ts, curPosition);
                flag = 1;
                // break all loop
            }
            else if (!maze->map[nextRow][nextCol] && !maze->mark[nextRow][nextCol])
            {
                // if un-visited route found, push curPosition(log direction and route)
                maze->mark[nextRow][nextCol] = 1; // mark visited position to prevent re-visit same route
                curPosition.direction++;
                traceStackPush(ts, curPosition);
                // after push, step to next position
                curPosition.row = nextRow;
                curPosition.col = nextCol;
                curPosition.direction = 0;
            }
            else // next position is invalid. try next direction
                curPosition.direction++;
        }
    }

    return flag;
}
#include <stdio.h>
#include <stdlib.h>
#include "mazeTraverseBFS.h"
#define MAZE_Q_INIT_SIZE 20
#define TOMB_STACK_INIT_SIZE 20

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

int traceQueueInit(TraceQueue *tq, const int qSize)
{
    tq->front = tq->rear = tq->size = 0;
    if ((tq->queue = malloc(sizeof(Trace) * qSize)) == NULL)
    {
        puts("Memory Allocation Error");
        return 1;
    }
    tq->capacity = qSize;
    return 0;
}

int traceEnQueue(TraceQueue *tq, Trace trace)
{
    if (tq->size >= tq->capacity)
    {
        Trace *temp = malloc(sizeof(Trace) * tq->capacity);
        if (temp == NULL)
        {
            puts("Memory Allocation Error");
            return 1;
        }

        int idx;
        for (int i = 0; i < tq->size; i++)
        {
            idx = (tq->front + i) % tq->capacity;
            temp[i].row = tq->queue[idx].row;
            temp[i].col = tq->queue[idx].col;
            temp[i].direction = tq->queue[idx].direction;
            temp[i].parentRow = tq->queue[idx].parentRow;
            temp[i].parentCol = tq->queue[idx].parentCol;
        }
        if ((tq->queue = realloc(tq->queue, sizeof(Trace) * tq->capacity * 2)) == NULL)
        {
            puts("Memory Re-Allocation Error");
            return 1;
        }
        for (int i = 0; i < tq->size; i++)
        {
            tq->queue[i].row = temp[i].row;
            tq->queue[i].col = temp[i].col;
            tq->queue[i].direction = temp[i].direction;
            tq->queue[i].parentRow = temp[i].parentRow;
            tq->queue[i].parentCol = temp[i].parentCol;
        }
        tq->front = 0;
        tq->rear = tq->size;
        tq->capacity = tq->capacity * 2;
        free(temp);
    }
    tq->queue[tq->rear].row = trace.row;
    tq->queue[tq->rear].col = trace.col;
    tq->queue[tq->rear].direction = trace.direction;
    tq->queue[tq->rear].parentRow = trace.parentRow;
    tq->queue[tq->rear].parentCol = trace.parentCol;
    tq->rear = (tq->rear + 1) % tq->capacity;
    tq->size++;
    return 0;
}

int traceDeQueue(TraceQueue *tq, Trace *trace)
{
    if (tq->size <= 0)
        return 1;
    trace->row = tq->queue[tq->front].row;
    trace->col = tq->queue[tq->front].col;
    trace->direction = tq->queue[tq->front].direction;
    trace->parentRow = tq->queue[tq->front].parentRow;
    trace->parentCol = tq->queue[tq->front].parentCol;
    tq->front = (tq->front + 1) % tq->capacity;
    tq->size--;
    return 0;
}

void traceQueueTerminate(TraceQueue *tq)
{
    if (tq->queue == NULL)
        return;
    free(tq->queue);
    tq->front = tq->rear = tq->capacity = tq->size = 0;
}

int tombStackInit(TombStack *ts, const int size)
{
    ts->top = 0;
    if ((ts->stack = malloc(sizeof(Trace) * size)) == NULL)
    {
        puts("Memory Allocation Error");
        return 1;
    }
    ts->capacity = size;
    return 0;
}

int tombStackPush(TombStack *ts, Trace trace)
{
    if (ts->top >= ts->capacity)
    {
        ts->stack = realloc(ts->stack, sizeof(Trace) * ts->capacity * 2);
        if (ts->stack == NULL)
        {
            puts("Memory Re-Allocation Error");
            return 1;
        }
        ts->capacity = ts->capacity * 2;
    }
    ts->stack[ts->top].row = trace.row;
    ts->stack[ts->top].col = trace.col;
    ts->stack[ts->top].parentRow = trace.parentRow;
    ts->stack[ts->top].parentCol = trace.parentCol;
    ts->stack[ts->top].direction = trace.direction;
    ts->top++;
    return 0;
}

int tombStackPop(TombStack *ts, Trace *trace)
{
    if (ts->top <= 0)
        return 1;
    ts->top--;
    trace->row = ts->stack[ts->top].row;
    trace->col = ts->stack[ts->top].col;
    trace->parentRow = ts->stack[ts->top].parentRow;
    trace->parentCol = ts->stack[ts->top].parentCol;
    trace->direction = ts->stack[ts->top].direction;
    return 0;
}

void tombStackTerminate(TombStack *ts)
{
    if (ts->stack == NULL)
        return;
    free(ts->stack);
    ts->capacity = ts->top = 0;
}

// we will backtrack with using tomb stack
void mazePathMake(TombStack *ts, int **map)
{
    Trace trace;
    tombStackPop(ts, &trace);
    map[trace.row][trace.col] = 2;
    int parentRow = trace.parentRow;
    int parentCol = trace.parentCol;
    while (ts->top > 0)
    {
        tombStackPop(ts, &trace);
        if (trace.row == parentRow && trace.col == parentCol)
        {
            map[trace.row][trace.col] = 2;
            parentRow = trace.parentRow;
            parentCol = trace.parentCol;
        }
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

int mazeTraverse(TraceQueue *tq, TombStack *ts, Maze *maze)
{
    int flag = 0;
    Trace curPosition;
    Trace nextPosition;
    if (traceQueueInit(tq, MAZE_Q_INIT_SIZE) || tombStackInit(ts, TOMB_STACK_INIT_SIZE))
        return 0;
    // enqueue initial position data
    curPosition.row = maze->startRow + 1;
    curPosition.col = maze->startCol + 1;
    curPosition.direction = 0;
    curPosition.parentRow = 0;
    curPosition.parentCol = 0;
    traceEnQueue(tq, curPosition);

    while (flag == 0 && tq->size > 0)
    {
        traceDeQueue(tq, &curPosition);
        while (maze->mark[curPosition.row][curPosition.col])
        {
            // prevent dequeue visited position
            // this is CORE point of BFS!
            traceDeQueue(tq, &curPosition);
        }
        maze->mark[curPosition.row][curPosition.col] = 1; // mark visited position to prevent re-visit same route
        nextPosition.parentRow = curPosition.row;
        nextPosition.parentCol = curPosition.col;
        nextPosition.direction = 0;
        while (flag == 0 && curPosition.direction < 8)
        {
            // set next position
            nextPosition.row = curPosition.row + step[curPosition.direction].vertical;
            nextPosition.col = curPosition.col + step[curPosition.direction].horizontal;
            // seek next position
            if (nextPosition.row == maze->endRow + 1 && nextPosition.col == maze->endCol + 1)
            {
                // endpoint reach
                tombStackPush(ts, curPosition);
                tombStackPush(ts, nextPosition);
                flag = 1;
                // break all loop
            }
            else if (!maze->map[nextPosition.row][nextPosition.col] && !maze->mark[nextPosition.row][nextPosition.col])
            {
                // if un-visited route found, enqueue next Position
                traceEnQueue(tq, nextPosition);
                curPosition.direction++;
            }
            else // next position is invalid. try next direction
                curPosition.direction++;
        }
        // tomb : archive of fully visited position
        tombStackPush(ts, curPosition);
    }

    return flag;
}
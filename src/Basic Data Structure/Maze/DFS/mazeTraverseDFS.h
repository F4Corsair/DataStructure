#ifndef __mazeTraverseDFS
#define __mazeTraverseDFS

typedef struct
{
    int vertical;
    int horizontal;
} Offset;

extern Offset step[8];

typedef struct
{
    int row;
    int col;
    int direction;
} Trace;

typedef struct
{
    int capacity;
    int top;
    Trace *stack;
} TraceStack;

typedef struct
{
    int row;
    int col;
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    int **map;
    int **mark;
} Maze;

Maze *mazeFileRead(char *fileName);

void mazeClose(Maze *maze);

void mazePrint(Maze *maze);

int traceStackPush(TraceStack *ts, Trace trace);

int traceStackPop(TraceStack *ts, Trace *trace);

void traceStackTerminate(TraceStack *ts);

void mazePathMake(TraceStack *ts, int **map);

void mazePathPrint(Maze *maze);

int mazeTraverse(TraceStack *ts, Maze *maze);

#endif
#ifndef __mazeTraverseBFS
#define __mazeTraverseBFS

typedef struct
{
    int vertical;
    int horizontal;
} Offset;

extern Offset step[8];

typedef struct
{
    int parentRow;
    int parentCol;
    int row;
    int col;
    int direction;
} Trace;

typedef struct
{
    int capacity;
    int size;
    int front;
    int rear;
    Trace *queue;
} TraceQueue;

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

typedef struct
{
    int capacity;
    int top;
    Trace *stack;
} TombStack;

Maze *mazeFileRead(char *fileName);

void mazeClose(Maze *maze);

void mazePrint(Maze *maze);

int traceQueueInit(TraceQueue *tq, const int qSize);

int traceEnQueue(TraceQueue *tq, Trace trace);

int traceDeQueue(TraceQueue *tq, Trace *trace);

void traceQueueTerminate(TraceQueue *tq);

int tombStackInit(TombStack *ts, const int size);

int tombStackPush(TombStack *ts, Trace trace);

int tombStackPop(TombStack *ts, Trace *trace);

void tombStackTerminate(TombStack *ts);

void mazePathMake(TombStack *ts, int **map);

void mazePathPrint(Maze *maze);

int mazeTraverse(TraceQueue *tq, TombStack *ts, Maze *maze);

#endif
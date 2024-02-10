#include <stdio.h>
#include <stdlib.h>
#include "mazeTraverseBFS.h"

int main(void)
{
    Maze *maze = mazeFileRead("../Map/maze4.txt");
    puts("[Maze]");
    mazePrint(maze);

    TraceQueue tq;
    TombStack ts;
    int flag = mazeTraverse(&tq, &ts, maze);
    if (flag == 0)
        puts("\nNo Path");
    else
    {
        puts("\n[Path]");
        mazePathMake(&ts, maze->map);
        mazePathPrint(maze);
    }
    traceQueueTerminate(&tq);
    tombStackTerminate(&ts);
    mazeClose(maze);
}
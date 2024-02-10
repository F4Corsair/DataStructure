#include <stdio.h>
#include <stdlib.h>
#include "mazeTraverseDFS.h"

int main(void)
{
    Maze *maze = mazeFileRead("../Map/maze2.txt");
    puts("[Maze]");
    mazePrint(maze);

    TraceStack ts;
    int flag = mazeTraverse(&ts, maze);
    if (flag == 0)
        puts("\nNo Path");
    else
    {
        puts("\n[Path]");
        mazePathMake(&ts, maze->map);
        mazePathPrint(maze);
    }
    traceStackTerminate(&ts);
    mazeClose(maze);
}
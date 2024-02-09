#include <stdio.h>
#include <stdlib.h>
#include "mazeTraverseDFS.h"

int main(void)
{
    Maze *maze = mazeFileRead("../Map/maze4.txt");
    puts("[Maze]");
    mazePrint(maze);

    mazeClose(maze);
}
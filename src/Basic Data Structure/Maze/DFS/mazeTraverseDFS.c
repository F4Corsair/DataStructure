#include <stdio.h>
#include <stdlib.h>
#include "mazeTraverseDFS.h"

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
            if (i == 0 || i == maze->row + 1 || j == 0 || j == maze->col)
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
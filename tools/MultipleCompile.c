#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define MAX_FILE_CNT 30
#define STRING_BUFFER 100

int main(void)
{
    int fileCnt = 0;
    char input[STRING_BUFFER];
    char outFileName[STRING_BUFFER];
    char batName[STRING_BUFFER + 20] = "compile_";
    char **FileName = malloc(sizeof(char *) * MAX_FILE_CNT);
    FileName[0] = malloc(sizeof(char) * MAX_FILE_CNT * STRING_BUFFER);
    for (int i = 1; i < MAX_FILE_CNT; i++)
    {
        FileName[i] = FileName[i - 1] + sizeof(char) * STRING_BUFFER;
    }
    puts("=MultipleCompile.bat Generator=");
    puts(">input file names[input nothing to end]");
    while (fileCnt < MAX_FILE_CNT)
    {
        fgets(input, sizeof(input), stdin);
        if (input[0] == '\n')
        {
            if (fileCnt == 0)
            {
                puts("You must input 1 fileName at least");
                continue;
            }
            else
            {
                break;
            }
        }
        input[strlen(input) - 1] = '\0';
        // printf("Echo : %s\n", input);
        strcpy(FileName[fileCnt], input);
        fileCnt++;
    }

    puts(">input output file's name[default : firstFileName.exe]");
    fgets(input, sizeof(input), stdin);
    if (strlen(input) == 1 && input[0] == '\n')
    {
        strcpy(outFileName, FileName[0]);
    }
    else
    {
        input[strlen(input) - 1] = '\0';
        strcpy(outFileName, input);
    }
    // make .bat file
    strcat(batName, outFileName);
    strcat(batName, ".bat");
    FILE *fp = fopen(batName, "w");
    fprintf(fp, "gcc ");
    for (int i = 0; i < fileCnt; i++)
    {
        fprintf(fp, ".\\%s.c ", FileName[i]);
    }
    fprintf(fp, "-c\ngcc ");
    for (int i = 0; i < fileCnt; i++)
    {
        fprintf(fp, ".\\%s.o ", FileName[i]);
    }
    fprintf(fp, "-o %s\n%s.exe", outFileName, outFileName);
    // free memory
    fclose(fp);
    free(FileName[0]);
    free(FileName);
}
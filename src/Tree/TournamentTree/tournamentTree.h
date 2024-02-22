#ifndef __tournamentTree
#define __tournamentTree
#define NAME_SIZE 6

typedef struct
{
    int class;
    int height;
    char name[10];
} StudentInfo;

typedef struct
{
    int key;   // height
    int index; // class
} TournamentTreeNode;

StudentInfo **classSeqInit(int classNum, int studentPerClass);

void sortedInfoPrint(StudentInfo *sorted, int classNum, int studentPerClass);

void classSeqTerminate(StudentInfo **sequences, int classNum);

void winnerTreeInit(TournamentTreeNode *winTree, int treeSize);

StudentInfo *winnerTreeSort(TournamentTreeNode *winTree, StudentInfo **classSequence, int classNum, int studentPerClass);

void winnerTreeUpdate(TournamentTreeNode *winTree, StudentInfo *infoList, int updateIdx, int *seqHead, int classNum, int studentPerClass);

void loserTreeInit(TournamentTreeNode *loseTree, int treeSize);

StudentInfo *loserTreeSort(TournamentTreeNode *loseTree, StudentInfo **classInfoSequence, int classNum, int studentPerClass);

void loserTreeUpdate(TournamentTreeNode *loseTree, StudentInfo *infoList, int updateIdx, int *seqHead, int classNum, int studentPerClass);

#endif
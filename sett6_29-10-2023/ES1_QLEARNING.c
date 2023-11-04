#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#else
#define CLEAR_CONSOLE system("clear")
#endif

#define VECTORCOUNT(vect) ((int)(sizeof(vect) / sizeof(vect[0])))
#define NRROWS 10
#define NRCOLS 10

#define CBLU    "\x1b[34m"
#define CRED    "\x1b[31m"
#define CGRN    "\x1b[32m"
#define CYLW    "\x1b[33m"
#define CRESET  "\x1b[0m"

typedef enum eDirections 
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NRDIRECTIONS // Little workaround in order to have the number of elements inside enum 
} eDirections;

typedef enum eStates 
{
    EMPTY,
    BOMB,
    CHARGE,
    START,
    END,
    NRSTATES
} eStates;

typedef struct MazeInfo 
{
    int nrBombs;
    int nrCharges;
} MazeInfo;

void set_qtable(float qtable[NRSTATES][NRDIRECTIONS], float value) 
{
    for (int row = 0; row < VECTORCOUNT(*qtable) + 1; row++) 
    {
        for (int col = 0; col < VECTORCOUNT(qtable[0]); col++) 
        {
            qtable[row][col] = value;
        }
    }
}

void print_qtable(float qtable[NRSTATES][NRDIRECTIONS])
{
    char *colHeaders[NRDIRECTIONS] = { "LEFT", "UP", "DOWN", "RIGHT" };
    char *rowHeaders[NRSTATES] = { "START", "EMPTY","CHARGE", "BOMB", "END" };

    printf("%10s", "");
    for (int col = 0; col < VECTORCOUNT(qtable[0]); col++)
        printf("%-11s", colHeaders[col]);

    puts("");
    for (int row = 0; row < VECTORCOUNT(*qtable) + 1; row++) 
    {
        printf("%-10s", rowHeaders[row]);
        for (int col = 0; col < VECTORCOUNT(qtable[0]); col++) 
        {
            printf("%-10.4f ", qtable[row][col]);
            // printf("%5s", "");
        }

        puts("");
    }
}

void init_maze(int nrRows, int nrCols, int maze[nrRows][nrCols], MazeInfo *info) 
{
    srand(time(NULL));
    
    for (int row = 0; row < nrRows; row++) 
    {
        for (int col = 0; col < nrCols; col++) 
        {
            maze[row][col] = EMPTY;
        }
    }

    for (int i = 0; i < info->nrBombs; i++) 
    {
        int rndCol = -1, rndRow = -1;
        do 
        {
            rndRow = rand() % nrRows;
            rndCol = rand() % nrCols;
        } while(maze[rndRow][rndCol] != EMPTY || maze[rndRow][rndCol] == BOMB);

        maze[rndRow][rndCol] = BOMB;
    }

    for (int i = 0; i < info->nrCharges; i++) 
    {
        int rndCol = -1, rndRow = -1;
        do 
        {
            rndRow = rand() % nrRows;
            rndCol = rand() % nrCols;
        } while(maze[rndRow][rndCol] != EMPTY || maze[rndRow][rndCol] == CHARGE);

        maze[rndRow][rndCol] = CHARGE;
    }

    maze[0][0] = START;
    maze[nrRows - 1][nrCols - 1] = END;
}

void print_maze(int nrRows, int nrCols, int maze[nrRows][nrCols])
{
    for (int row = 0; row < nrRows; row++) 
    {
        for (int col = 0; col < nrCols; col++) 
        {
            char consoleColor[9] = CRESET;
            switch (maze[row][col]) 
            {
                case START:
                strcpy(consoleColor, CBLU);
                break;

                case BOMB:
                strcpy(consoleColor, CRED);
                break;

                case CHARGE:
                strcpy(consoleColor, CYLW);
                break;

                case END:
                strcpy(consoleColor, CGRN);
                break;
            }


            fprintf(stdout, "%s%d%s ", consoleColor, maze[row][col], CRESET);
        }

        puts("");
    }
}

int main()
{
    float q_table[NRSTATES][NRDIRECTIONS];
    set_qtable(q_table, 0);
    print_qtable(q_table);

    int maze[NRROWS][NRCOLS];
    MazeInfo mazeStats;
    mazeStats.nrBombs = 5;
    mazeStats.nrCharges = 6;
    init_maze(NRROWS, NRCOLS, maze, &mazeStats);
    print_maze(NRROWS, NRCOLS, maze);

    return 0;
}
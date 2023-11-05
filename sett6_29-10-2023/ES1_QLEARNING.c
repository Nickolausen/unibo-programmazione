#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

#ifdef _WIN32
#include <windows.h>
#define CLEAR_CONSOLE system("cls")
#define SLEEP(ms) Sleep(ms * 1000)
#else
#include <unistd.h>
#define CLEAR_CONSOLE system("clear")
#define SLEEP(s) sleep(s)
#endif

#define VECTORCOUNT(vect) ((int)(sizeof(vect) / sizeof(vect[0])))

#define NRROWS 10
#define NRCOLS 10
#define Q_LENGTH NRROWS * NRCOLS

#define MAX_TRAINING_EXPERIMENT 1000
#define MAX_TRAINING_STEP -1
#define LEARNING_RATE .1f
#define DISCOUNT_RATE .99f

#define FSBOLD      "\e[1m"
#define FSRESET     "\e[m"

#define CBLU        "\x1b[34m"
#define CRED        "\x1b[31m"
#define CGRN        "\x1b[32m"
#define CYLW        "\x1b[33m"
#define CRESET      "\x1b[0m"

typedef enum eActions 
{
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NRACTIONS // Little workaround in order to have the number of elements inside enum 
} eAction;

typedef enum eStateTypes 
{
    EMPTY,
    BOMB,
    CHARGE,
    START,
    END,
    NRSTATES
} eStateTypes;

typedef struct MazeInfo 
{
    int nrBombs;
    int nrCharges;
    int bombMalus;
    int chargeBonus;
    int emptyTilePoints;
    int endScore;
} MazeInfo;

typedef struct Coordinates 
{
    int row;
    int col;
} Coordinates;

void set_qtable(float qtable[Q_LENGTH][NRACTIONS], float value) 
{
    for (int state = 0; state < VECTORCOUNT(*qtable) + 1; state++) 
    {
        for (int action = 0; action < VECTORCOUNT(qtable[0]); action++) 
        {
            qtable[state][action] = value;
        }
    }
}

void print_qtable(float qtable[Q_LENGTH][NRACTIONS], int state)
{
    char *rowHeaders[NRACTIONS] = { "LEFT", "UP", "DOWN", "RIGHT" };
    printf("== Q-Table values for state [%d] ==\n", state);

    printf("%-10s%.5f\n", rowHeaders[LEFT], qtable[state][LEFT]);
    printf("%-10s%.5f\n", rowHeaders[UP], qtable[state][UP]);
    printf("%-10s%.5f\n", rowHeaders[DOWN], qtable[state][DOWN]);
    printf("%-10s%.5f\n", rowHeaders[RIGHT], qtable[state][RIGHT]);
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

void print_maze(int nrRows, int nrCols, int maze[nrRows][nrCols], Coordinates *robot_position)
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

            if (robot_position->row == row && robot_position->col == col)
                fprintf(stdout, FSBOLD"%c "FSRESET, 'X'); // Print X for ROBOT
            else
                fprintf(stdout, "%s%d%s ", consoleColor, maze[row][col], CRESET); // Print the maze content
        }

        puts("");
    }
}

bool is_within_boundaries(Coordinates *position, int nrRows, int nrCols)
{
    return (position->row >= 0 && position->row < nrRows) &&
        (position->col >= 0 && position->col < nrCols);
}

int main()
{
    CLEAR_CONSOLE;
    srand(time(NULL));

    float q_table[Q_LENGTH][NRACTIONS];
    set_qtable(q_table, 0);

    int countTrainingStep = 0, countTrainingExperiment = 0;

    int maze[NRROWS][NRCOLS];
    MazeInfo mazeStats = 
    {
        7, // NR° BOMBS
        6, // NR° CHARGES
        -100, // BOMB MALUS
        +1, // CHARGE BONUS
        -1, // EMPTY TILE MALUS
        +100 // END SCORE
    };

    Coordinates initial_position = { 0, 0 };
    Coordinates current_position;
    Coordinates next_position;

    init_maze(NRROWS, NRCOLS, maze, &mazeStats);
    print_maze(NRROWS, NRCOLS, maze, &initial_position);

    int moves[NRACTIONS][2] = {
        {-1, 0 }, // UP
        { 0, 1 }, // RIGHT
        { 1, 0 }, // DOWN
        { 0, -1 } // LEFT
    };

    int trainingCount = 0; 

    /* 
        The value of epsilon will decrease as the training goes on.
        The robot will choose to perform an action based on Q-Table values if he got trained enough, 
        or a random action in order to explore the maze depending on epsylon value after each training iteration.
    */
    float eps = 100;

    float maxReward = -FLT_MAX;
    eAction action;

    int current_state = 0;
    current_position.row = initial_position.row;
    current_position.col = initial_position.col;
    bool first;

    while (trainingCount < MAX_TRAINING_EXPERIMENT) // Robot's training
    {
        CLEAR_CONSOLE;
        SLEEP(1);

        printf("%d",trainingCount);
        countTrainingStep++;
        int probability = (rand() % 100) + 1;

        if ( probability <= (100 - eps) )
        {
            // Perform an action according to Q-Table values
            first = true;
            
            /*
                The robot tries to perform every action.
                If the i-th action stays within the boundaries of the maze AND
                it is either the first move in that action OR a reward in q-table is found to be 
                higher than the current maxReward, then we update maxReward with the value found and we save the
                corresponding action that led to such reward.
            */
            for (int actIdx = 0; actIdx < NRACTIONS; actIdx++)
            {
                next_position.row = current_position.row + moves[actIdx][0];
                next_position.col = current_position.col + moves[actIdx][1];

                if (is_within_boundaries(&next_position, NRROWS, NRCOLS) && 
                    (first || q_table[current_state][actIdx] > maxReward)) 
                {
                    maxReward = q_table[current_state][actIdx];
                    action = actIdx;
                    first = false;
                }
            }
        }
        else 
        {
            // Perform an action randomly
            bool actionCheck[NRACTIONS] = { false, false, false, false };
            bool found = false;

            while (!found) 
            {
                do 
                {
                    action = rand() % 4;
                } while (!actionCheck[action]);

                actionCheck[action] = true;

                next_position.row = current_position.row + moves[action][0];
                next_position.col = current_position.col + moves[action][1];

                if (is_within_boundaries(&next_position, NRROWS, NRCOLS))
                    found = true;
            }
        }

        // Updating current position with new moves, 
        // determined either by chance or by Q-Table values;
        current_position.row += moves[action][0];
        current_position.col += moves[action][1];

        // Determine reward points based on which tile type
        // the robot is standing over;
        int reward = 0;
        switch (maze[current_position.row][current_position.col]) 
        {
            case BOMB:
                reward = mazeStats.bombMalus;
            break;

            case EMPTY:
                reward = mazeStats.emptyTilePoints;
            break;

            case CHARGE:
                reward = mazeStats.chargeBonus;
            break;

            case END:
                reward = mazeStats.endScore;
            break;
        }

        /* 
            In order to apply the formula we have to estimate the maximum future reward determined by Q-Table values of
            nearby tiles.
        */
        // Finding new state
        int new_state = current_position.row * NRCOLS + current_position.col;

        float maxFutureReward = -FLT_MAX;
        first = true;

        for (int actIdx = 0; actIdx < NRACTIONS; actIdx++) 
        {
            next_position.row = current_position.row + moves[actIdx][0];
            next_position.col = current_position.col + moves[actIdx][1];

            if (is_within_boundaries(&next_position, NRROWS, NRCOLS) && 
                (first || q_table[current_state][actIdx] > maxFutureReward))
            {
                maxFutureReward = q_table[new_state][actIdx];
                first = false;
            }
        }

        // Applying formula to update Q-Table values for current_state
        q_table[current_state][action] = q_table[current_state][action] + LEARNING_RATE * (reward + (DISCOUNT_RATE * maxFutureReward) - q_table[current_state][action]);
        print_qtable(q_table, current_state);

        if (maze[current_position.row][current_position.col] == BOMB || 
            maze[current_position.row][current_position.col] == END ||
            (MAX_TRAINING_STEP > 0 && countTrainingExperiment > MAX_TRAINING_STEP))
        {
            countTrainingStep = 0;
            current_state = initial_position.row * NRCOLS + initial_position.col;
            current_position.row = initial_position.row;
            current_position.col = initial_position.col;
            countTrainingExperiment++;
            eps -= 100.0f / MAX_TRAINING_EXPERIMENT;
        }
        else
        {
            current_state = new_state;
        }

        print_maze(NRROWS, NRCOLS, maze, &current_position);
    }
    return 0;
}
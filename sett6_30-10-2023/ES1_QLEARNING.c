#include <float.h>
#include <limits.h>
#include <stdint.h>
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

#define MAX_TRAINING_ITERATIONS 1000
#define MAX_TRAINING_STEP -1

/*
    Value between 0 <= x <= 1; 
    - If set to 0, the agent learns nothing from its moves;
    - If set to 1, the agent values only most recent information;
*/
#define LEARNING_RATE .5f

/*
    Value between 0 <= x <= 1;
    - If set to 0, the agent completely ignore future rewards;
    - If set to 1, the agent looks for high rewards in the long term;
*/
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
    NRSTATES // Little workaround in order to have the number of elements inside enum
} eStateType;

typedef struct MazeComposition 
{
    int nrBombs;
    int nrCharges;
} MazeComposition;

typedef struct MazeScores 
{
    int bombMalus;
    int chargeBonus;
    int emptyTilePoints;
    int endScore;
} MazeScores;

typedef struct Coordinates 
{
    int row;
    int col;
} Coordinates;

void set_qtable(float qtable[Q_LENGTH][NRACTIONS], float value) 
{
    for (int state = 0; state < Q_LENGTH; state++) 
    {
        for (int action = 0; action < NRACTIONS; action++) 
        {
            qtable[state][action] = value;
        }
    }
}

void print_qtable_complete(float qtable[Q_LENGTH][NRACTIONS]) 
{
    char *rowHeaders[NRACTIONS] = { "LEFT", "UP", "DOWN", "RIGHT" };
    int nrChars = 25;
    printf("%*s\n", -(int)strlen("==== Entire Q-Table ===="), "==== Entire Q-Table ====");

    printf("%10s", "");
    for (int action = 0; action < NRACTIONS; action++)
    {
        printf("%-10s", rowHeaders[action]);
    }

    puts("");
    for (int state = 0; state < Q_LENGTH; state++) 
    {
        printf("State [%d]%10s", state, "");
        for (int action = 0; action < NRACTIONS; action++)
        {
            printf("%-10.5f", qtable[state][action]);
        }
        puts("");
    }
}

void print_qtable_state(float qtable[Q_LENGTH][NRACTIONS], int state)
{
    char *rowHeaders[NRACTIONS] = { "LEFT", "UP", "DOWN", "RIGHT" };
    printf("== Q-Table values for state [%d] ==\n", state);

    printf("%-10s%.5f\n", rowHeaders[LEFT], qtable[state][LEFT]);
    printf("%-10s%.5f\n", rowHeaders[UP], qtable[state][UP]);
    printf("%-10s%.5f\n", rowHeaders[DOWN], qtable[state][DOWN]);
    printf("%-10s%.5f\n", rowHeaders[RIGHT], qtable[state][RIGHT]);
}

void init_maze(int nrRows, int nrCols, int maze[nrRows][nrCols], MazeComposition *info) 
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

            if (robot_position->row == row && 
                robot_position->col == col)
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

int to_state(Coordinates *position, int max_cols)
{
    return position->row * max_cols + position->col;
}

void train_agent(int maze[NRROWS][NRCOLS], 
    MazeScores* scores,
    Coordinates* initial_position, 
    float q_table[Q_LENGTH][NRACTIONS],
    const int MAX_TRAINING) 
{
    Coordinates current_position = *initial_position;
    int initial_state = to_state(initial_position, NRCOLS);
    float eps = 100;
    int moves[NRACTIONS][2] =  
    {
        {-1,0}, // UP
        {0,1}, // RIGHT
        {1,0}, // DOWN
        {0,-1} // LEFT
    };
    
    int trainingStep = 0;
    while (trainingStep < MAX_TRAINING) 
    {
        CLEAR_CONSOLE;
        int rndDecision = rand() % 100 + 1;
        eAction action;
        Coordinates next_position;

        // Perform an action according to epsilon-greedy policy:
        /* 
            If the random decision <= "1 - eps", then use Q-Table;
            if the random decision is == to "eps", then explore. 
        */
        if (rndDecision <= (100 - eps)) 
        {
            // Perform an action EXPLOITING Q-table values

            Coordinates possible_next_position;
            float maxReward = -FLT_MIN;

            for (int idxAction = 0; idxAction < NRACTIONS; idxAction++) 
            {
                possible_next_position.row = current_position.row + moves[idxAction][0];
                possible_next_position.col = current_position.col + moves[idxAction][1];

                if (q_table[to_state(&possible_next_position, NRCOLS)][idxAction] >= maxReward) 
                {
                    maxReward = q_table[to_state(&possible_next_position, NRCOLS)][idxAction];
                    action = idxAction;
                    next_position.row = possible_next_position.row;
                    next_position.col = possible_next_position.col;
                }
            }
        }
        else 
        {
            // Perform an action EXPLORING the environment

            // /* For 
            //     [0]=UP, 
            //     [1]=RIGHT, 
            //     [2]=DOWN, 
            //     [3]=LEFT 
            // */
            // bool actionCheck[] = { false, false, false, false };
            
            Coordinates possible_next_position; 
            do 
            {
                action = rand() % NRACTIONS; 

                possible_next_position.row = current_position.row + moves[action][0];
                possible_next_position.col = possible_next_position.col + moves[action][1];

            } while (is_within_boundaries(&possible_next_position, NRROWS, NRCOLS));

            next_position.row = possible_next_position.row;
            next_position.col = possible_next_position.col;
        }

        // As we computed the next position (coming from exploration or exploitation of the Q-Table)
        // we update the agent's current position on the maze, and we check on what kind of tile he's standing over

        int reward = -1;
        current_position.row = next_position.row;
        current_position.col = next_position.col;

        switch (maze[current_position.row][current_position.col])
        {
            case EMPTY:
                reward = scores->emptyTilePoints;
            break;

            case BOMB:
                reward = scores->bombMalus;
            break;

            case CHARGE:
                reward = scores->chargeBonus;
            break;

            case END:
                reward = scores->endScore;
            break;
        }

        int current_state = to_state(&current_position, NRCOLS);

        // In order to use the formula, we need to estimate the max
        // future reward from the Q-Table
        float maxFutureReward = -FLT_MIN;
        for (int idxAction = 0; idxAction < NRACTIONS; idxAction++)
        {
            next_position.row = current_position.row + moves[idxAction][0];
            next_position.col = current_position.col + moves[idxAction][1];
            int futureState = to_state(&next_position, NRCOLS);
            
            if (q_table[futureState][idxAction] >= maxFutureReward) 
            {
                maxFutureReward = q_table[futureState][idxAction];
            }
        }

        // Updating Q-Table value
        q_table[current_state][action] = q_table[current_state][action] + LEARNING_RATE * 
            (reward + DISCOUNT_RATE * maxFutureReward - q_table[current_state][action]);

        if (maze[current_state][action] == BOMB || maze[current_state][action] == END) 
        {
            eps -= 100.0f / MAX_TRAINING;
            trainingStep++;
            current_position = *initial_position;
            current_state = initial_state;
        }
        // print_maze(NRROWS, NRCOLS, maze, &current_position);
        // SLEEP(1);
    }

    print_qtable_complete(q_table);
}

int main()
{
    CLEAR_CONSOLE;
    srand(time(NULL));

    float q_table[Q_LENGTH][NRACTIONS];
    set_qtable(q_table, 0);
    print_qtable_complete(q_table);
    int maze[NRROWS][NRCOLS];
    MazeComposition mazeComposition = 
    {
        7, // NR° BOMBS
        6, // NR° CHARGES
    };

    MazeScores scores = { 
        -100, // Bomb malus
        +10, // Charge bonus
        -1, // Empty tile malus
        100 // End score
    };
    Coordinates initial_position = {0 /*row*/, 0 /*col*/};

    init_maze(NRROWS, NRCOLS, maze, &mazeComposition);
    // print_maze(NRROWS, NRCOLS, maze, &initial_position);

    train_agent(maze, &scores, &initial_position, q_table, 1000);
    
    return 0;
}
#include <ctype.h>
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

#define NRROWS 10
#define NRCOLS 10
#define Q_LENGTH NRROWS * NRCOLS

/*
    Value between 0 <= x <= 1; 
    - If set to 0, the agent learns nothing from its moves;
    - If set to 1, the agent values only most recent information;
*/
#define LEARNING_RATE .1f

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

typedef struct MazeScores 
{
    int bombMalus;
    int chargeBonus;
    int emptyTilePoints;
    int endScore;
    int alreadyVisitedMalus;
} MazeScores;

typedef struct Coordinates 
{
    int row;
    int col;
} Coordinates;

typedef struct MazeComposition 
{
    int nrBombs;
    int nrCharges;
    Coordinates start_point;
    Coordinates end_point;
} MazeComposition;

static int moves[NRACTIONS][2] =  
{
    {-1,0}, // UP
    {0,1}, // RIGHT
    {1,0}, // DOWN
    {0,-1} // LEFT
};

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

void init_maze(int nrRows, int nrCols, int maze[nrRows][nrCols], 
    MazeComposition* info) 
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

    maze[info->start_point.row][info->start_point.col] = START;
    maze[info->end_point.row][info->end_point.col] = END;
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
                printf("%s%s%c%s%s ", consoleColor, FSBOLD, 'X', FSRESET, CRESET); // Print X for ROBOT
            else
                printf("%s%d%s ", consoleColor, maze[row][col], CRESET); // Print the maze content
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

bool game_over(eStateType cell) 
{
    return cell == BOMB || cell == END;
}

// Returns the celltype that triggered tmarohe gameover (it could be the endpoint or a bomb)
eStateType play_game(int maze[NRROWS][NRCOLS], 
    float qtable[Q_LENGTH][NRACTIONS], 
    Coordinates* initial_position) 
{
    // Main steps:
    // (1) LOOK Q-TABLE VALUES FROM CURRENT POSITION;
    // (2) MOVE ACCORDING TO BEST VALUE FOUND;
    // (3) CHECK ON WHAT KIND OF CELL THE ROBOT IS STANDING OVER;

    Coordinates current_position = { initial_position->row, initial_position->col };
    eStateType current_cell = maze[current_position.row][current_position.col];
    
    while ( !game_over(current_cell) ) // (3)
    {
        CLEAR_CONSOLE;
        print_maze(NRROWS, NRCOLS, maze, &current_position);
        puts("");
        print_qtable_state(qtable, to_state(&current_position, NRCOLS));
        SLEEP(1);

        Coordinates next_position;
        eAction action;

        // (1)
        float maxQValue = -FLT_MAX;
        bool firstPossiblePosition = true;
        for (int idxAction = 0; idxAction < NRACTIONS; idxAction++) 
        {
            next_position.row = current_position.row + moves[idxAction][0];
            next_position.col = current_position.col + moves[idxAction][1];

            if (!is_within_boundaries(&next_position, NRROWS, NRCOLS))
                continue;
            
            int next_state = to_state(&next_position, NRCOLS);
            
            if (firstPossiblePosition || qtable[next_state][idxAction] >= maxQValue) 
            {
                firstPossiblePosition = false;
                maxQValue = qtable[next_state][idxAction];
                action = idxAction;
            }
        }

        // (2)
        current_position.row += moves[action][0];
        current_position.col += moves[action][1];

        current_cell = maze[current_position.row][current_position.col];
    }

    CLEAR_CONSOLE;
    print_maze(NRROWS, NRCOLS, maze, &current_position);
    puts("");
    print_qtable_state(qtable, to_state(&current_position, NRCOLS));

    return current_cell;
}

time_t train_agent(int maze[NRROWS][NRCOLS], 
    MazeScores* scores,
    Coordinates* initial_position, 
    float q_table[Q_LENGTH][NRACTIONS],
    const int MAX_TRAINING) 
{
    time_t start_time = clock();

    Coordinates current_position = { initial_position->row, initial_position->col };
    int initial_state = to_state(initial_position, NRCOLS);
    float eps = 100;

    // Keep track of visited cells
    bool alreadyVisited[NRROWS][NRCOLS];
    for (int row = 0; row < NRROWS; row++) 
    {
        for (int col = 0; col < NRCOLS; col++) 
        {
            alreadyVisited[row][col] = false;
        }
    }
    
    print_maze(NRROWS, NRCOLS, maze, &current_position);
    int trainingStep = 0, nrIterations = 0;
    while (trainingStep < MAX_TRAINING) 
    {
        CLEAR_CONSOLE;
        int percentage = trainingStep * 100 / MAX_TRAINING;
        printf("# Training status: %d%% completed [%d/%d]:\n", percentage, trainingStep, MAX_TRAINING);
        printf("## Iteration: %d\n", nrIterations++);
        
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
            float maxQValue = -FLT_MIN;

            int possible_next_state;
            bool firstPossiblePosition = true;
            for (int idxAction = 0; idxAction < NRACTIONS; idxAction++) 
            {
                Coordinates possible_next_position;
                possible_next_position.row = current_position.row + moves[idxAction][0];
                possible_next_position.col = current_position.col + moves[idxAction][1];

                if (!is_within_boundaries(&possible_next_position, NRROWS, NRCOLS))
                    continue;
                
                possible_next_state = to_state(&possible_next_position, NRCOLS);
                
                if (firstPossiblePosition || q_table[possible_next_state][idxAction] >= maxQValue) 
                {
                    firstPossiblePosition = false;
                    maxQValue = q_table[possible_next_state][idxAction];
                    action = idxAction;
                }
            }
        }
        else 
        {
            // Perform an action EXPLORING the environment
            
            Coordinates possible_next_position;
            do 
            {
                action = rand() % NRACTIONS; 

                possible_next_position.row = current_position.row + moves[action][0];
                possible_next_position.col = current_position.col + moves[action][1];

            } while (!is_within_boundaries(&possible_next_position, NRROWS, NRCOLS));
        }

        // As we computed the next position (coming from either exploration of the maze or exploitation of the Q-Table)
        // we update the agent's current position on the maze, and we find out on what kind of tile he's standing over
        current_position.row += moves[action][0];
        current_position.col += moves[action][1];

        int reward;
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

        if (alreadyVisited[current_position.row][current_position.col])
            reward += scores->alreadyVisitedMalus;
        else
            alreadyVisited[current_position.row][current_position.col] = true;

        int current_state = to_state(&current_position, NRCOLS);

        // In order to use the formula, we need to estimate the max
        // future reward from the Q-Table
        float maxFutureQValue = -FLT_MIN;
        bool firstPossiblePosition = true;
        for (int idxAction = 0; idxAction < NRACTIONS; idxAction++)
        {
            next_position.row = current_position.row + moves[idxAction][0];
            next_position.col = current_position.col + moves[idxAction][1];

            if (!is_within_boundaries(&next_position, NRROWS, NRCOLS))
                continue;
            
            int futureState = to_state(&next_position, NRCOLS);
            
            if (firstPossiblePosition || q_table[futureState][idxAction] >= maxFutureQValue) 
            {
                firstPossiblePosition = false;
                maxFutureQValue = q_table[futureState][idxAction];
            }
        }

        // Updating Q-Table value with Bellman's equation
        q_table[current_state][action] = q_table[current_state][action] + LEARNING_RATE * 
            (reward + DISCOUNT_RATE * maxFutureQValue - q_table[current_state][action]);

        if (game_over(maze[current_position.row][current_position.col])) 
        {
            eps -= 100.0f / MAX_TRAINING;
            trainingStep++;
            current_position = *initial_position;
            current_state = initial_state;
        }
    }

    time_t end_time = clock();

    time_t elapsedTime = end_time - start_time;
    return elapsedTime;
}

int main()
{
    CLEAR_CONSOLE;
    srand(time(NULL));

    float q_table[Q_LENGTH][NRACTIONS];
    set_qtable(q_table, 0);
    int maze[NRROWS][NRCOLS];
    MazeComposition mazeComposition = 
    {
        7, // NR° BOMBS
        6, // NR° CHARGES
        {1,1}, // START POINT
        {7, 6} // END POINT
    };

    MazeScores scores = { 
        -100, // Bomb malus
        +10, // Charge bonus
        -1, // Empty tile malus
        100, // End score
        -10 // Already visited malus
    };

    Coordinates initial_position = {
        mazeComposition.start_point.row /*row*/, 
        mazeComposition.start_point.col /*col*/
    };

    CLEAR_CONSOLE;
    printf(CBLU"=== Q-Learning Algorithm in C ===\n");
    printf("Program written by:\n");
    printf("> Nicholas Magi\n");
    printf("> Riccardo Ventrucci\n");
    printf("> Tommaso Maestri\n");
    printf("> Leonardo Perretta\n\n"CRESET);
    
    bool keepMaze;
    do {
        init_maze(NRROWS, NRCOLS, maze, &mazeComposition);
        printf("=== Generated maze:\n");
        print_maze(NRROWS, NRCOLS, maze, &initial_position);

        printf("\n- Do you want to keep this maze? [Y/n]: ");
        fflush(stdin);
        keepMaze = toupper(getchar()) == 'Y';

        if (!keepMaze) 
        {
            fflush(stdout);
            CLEAR_CONSOLE;
        }
        
    } while(!keepMaze);

    puts("");

    int nrTrainingSteps;
    do 
    {
        printf("How many training iterations do you want? (At least 1)\n");
        printf("%sWARNING: Low training iterations increase the chance of getting stuck in a loop.%s\n", CYLW, CRESET);
        printf("Input: ");
        fflush(stdin);
        scanf("%d", &nrTrainingSteps);
        puts("");

        if (nrTrainingSteps <= 0)
            puts("Invalid input! AT LEAST 1 TRAINING ITERATION IS REQUIRED");
    } while (nrTrainingSteps <= 0);

    bool keepTraining;
    do 
    {
        time_t elapsedSeconds = train_agent(maze, &scores, &initial_position, q_table, nrTrainingSteps) / CLOCKS_PER_SEC;
        printf("Training finished. Elapsed time: %lds\n", elapsedSeconds);
        
        printf("\n- Do you want to start another training session? [Y/n]: ");
        fflush(stdin);
        keepTraining = toupper(getchar()) == 'Y';

    } while (keepTraining);
    
    CLEAR_CONSOLE;

    eStateType gameoverTrigger = play_game(maze, q_table, &initial_position);

    puts("");
    if (gameoverTrigger == BOMB)
        printf("%sGAME OVER - A bomb exploded! %s", CRED, CRESET);
    else
        printf("%sYou won!%s", CGRN, CRESET);
   
    return 0;
}
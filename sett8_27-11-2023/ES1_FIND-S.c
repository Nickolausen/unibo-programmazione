/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define FILE_ROWS 6
#define MAX_LEN 1000
#define MAX_STR_LEN 100

#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#ifdef _WIN32
#include <windows.h>
#define CLEAR_CONSOLE system("cls")
#define SLEEP(ms) Sleep(ms * 1000)
#else
#include <unistd.h>
#define CLEAR_CONSOLE system("clear")
#define SLEEP(s) sleep(s)
#endif

typedef enum {
    nessuno = 0,
    qualcuno = 1,
    pieno = 2,
    generalStatus = 3
} crowd_status;

typedef enum {
    $ = 0,
    $$ = 1,
    $$$ = 2,
    generalPrice = 3
} price_tag;

typedef enum {
    italiano = 0,
    francese = 1,
    fast_food = 2,
    thai = 3,
    generalType = 4
} restaurant_type;

typedef enum {
    under10 = 0,
    over10 = 1,
    over30 = 2,
    over60 = 3,
    generalWaiting = 4
} estimated_waiting; 

typedef enum {
    no = 0,
    yes = 1,
    general = 2
} qbit; /*😎*/

typedef struct {
    qbit hasAlternative;
    qbit hasBar;
    qbit onFriOrSat;
    qbit isHungry;
    crowd_status crowdStatus;
    price_tag expensiveness;
    qbit isRaining;
    qbit hasReservation;
    restaurant_type type;
    estimated_waiting waiting;
    qbit considered;
} Hypothesis;

typedef struct {
    Hypothesis* data;
    int size;
} HypothesisList;

typedef enum {
    fromFile,
    fromConsole,
    undefined
} InputMode;

/*
    Function to choose which way the data should be prompted to the code.
*/
InputMode getInputMode() 
{
    char chosenInput;

    do 
    {
        fflush(stdin);
        printf("Choose input mode:\n");
        printf("> From .csv file [F]\n");
        printf("> From console [C]\n\n");
        printf("Type here: ");
        scanf("%c", &chosenInput);
        puts("");

        switch (toupper(chosenInput)) 
        {
            case 'F':
                return fromFile;
            case 'C':
                return fromConsole;
            default:
            {
                CLEAR_CONSOLE;
                printf(ANSI_COLOR_RED "Expected 'F' or 'C', but received '%c'. Choose again.\n\n" ANSI_COLOR_RESET, chosenInput);
            }
        }
    } while (chosenInput != 'C' || chosenInput != 'F');
    
    return undefined;
}

HypothesisList retrieveData(InputMode mode) 
{
    HypothesisList output = {NULL, 0};
    Hypothesis* outputVect = (Hypothesis*)malloc(sizeof(Hypothesis) * MAX_LEN);
    int vectorIndex = 0;
    if (outputVect == NULL)
    {
        printf(ANSI_COLOR_RED "An error occurred while allocating %lu bytes of memory. Exiting..." ANSI_COLOR_RESET, sizeof(Hypothesis) * MAX_LEN);
        exit(1);
    }

    switch (mode)
    {
        case fromConsole:
        {
            CLEAR_CONSOLE;
            printf("- Retrieving data from %sCONSOLE%s -\n\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);

            bool keepGoing = true;
            do {
                output.size++;
                printf("## Iterazione: %d\n\n", vectorIndex + 1);

                fflush(stdin);
                printf("(1) C'è un alternativa a questo locale? [1=Yes/0=No] ");
                scanf("%d", &(outputVect[vectorIndex].hasAlternative));
                puts("");

                fflush(stdin);
                printf("(2) Questo locale ha un bar? [1=Yes/0=No] ");
                scanf("%d", &(outputVect[vectorIndex].hasBar));
                puts("");

                fflush(stdin);
                printf("(3) Vuoi andare o di venerdì o sabato? [1=Yes/0=Other days] ");
                scanf("%d", &(outputVect[vectorIndex].onFriOrSat));
                puts("");

                fflush(stdin);
                printf("(4) Sei affamato? [1=Yes/0=No] ");
                scanf("%d", &(outputVect[vectorIndex].isHungry));
                puts("");

                fflush(stdin);
                printf("(5) Il locale è molto affollato al momento? [0=nessuno/1=qualcuno/2=pieno] ");
                scanf("%d", &(outputVect[vectorIndex].crowdStatus));
                puts("");

                fflush(stdin);
                printf("(6) Il locale è molto costoso? [0=$/1=$$/2=$$$] ");
                scanf("%d", &(outputVect[vectorIndex].expensiveness));
                puts("");

                fflush(stdin);
                printf("(7) Fuori sta piovendo? [1=Yes/0=No] ");
                scanf("%d", &(outputVect[vectorIndex].isRaining));
                puts("");

                fflush(stdin);
                printf("(8) Hai effettuato la prenotazione? [1=Yes/0=No] ");
                scanf("%d", &(outputVect[vectorIndex].hasReservation));
                puts("");

                fflush(stdin);
                printf("(9) Di quale tipo di ristorante si tratta? [0=italiano/1=francese/2=fast-food/3=thai] ");
                scanf("%d", &(outputVect[vectorIndex].isRaining));
                puts("");

                fflush(stdin);
                printf("(10) Qual è l'attesa stimata per poter entrare? [0 = (t)<10min / 1 = 11min<(t)<30min / 2 = 31min<(t)<60min / 3 = (t)>61min] ");
                scanf("%d", &(outputVect[vectorIndex].isRaining));
                puts("");

                fflush(stdin);
                printf("(11) Qual è l'attesa stimata per poter entrare? [1=Yes/0=No] ");
                scanf("%d", &(outputVect[vectorIndex].considered));
                puts("\n");

                fflush(stdin);
                printf("Would you like to keep prompting other data? [Y=Yes/Any char=No] ");
                keepGoing = toupper(getc(stdin)) == 'Y';

                if (keepGoing)
                {
                    vectorIndex++;
                    CLEAR_CONSOLE;
                }
                
            } while (keepGoing);
            break;
        }

        case fromFile:
        {
            char fileName[] = "dataset-finds.csv";
            FILE *pFile;
            char answer;

            CLEAR_CONSOLE;
            do 
            {
                printf("- Retrieving data from %sFILE%s -\n\n", ANSI_COLOR_BLUE, ANSI_COLOR_RESET);
                fflush(stdin);
                printf("Do you want to use the default filename '%s'? [Y/N]: " , fileName);
                scanf("%c", &answer);
                puts("");

                switch (toupper(answer))
                {
                    case 'Y': break;
                    case 'N': 
                    {
                        char inputFileName[MAX_STR_LEN];
                        do {

                            fflush(stdin);
                            printf(ANSI_COLOR_YELLOW "Make sure your dataset is .csv and does not have an header row!\n" ANSI_COLOR_RESET);
                            printf("Type the file name: ");
                            scanf("%s", inputFileName);
                            puts("\n");

                            pFile = fopen(inputFileName, "r");
                            if (pFile == NULL) 
                            {
                                CLEAR_CONSOLE;
                                printf(ANSI_COLOR_RED "An error occurred: could not open '%s'. Try again.\n\n" ANSI_COLOR_RESET, inputFileName);
                            }

                        } while (pFile == NULL);

                        /*
                            Closing and disposing pointer to file, used only to check if 
                            the prompted file exists
                        */
                        fclose(pFile);

                        strcpy(fileName, inputFileName);
                    }
                    default:
                    {
                        CLEAR_CONSOLE;
                        printf(ANSI_COLOR_RED "Expected 'Y' or 'N', but received '%c'. Choose again.\n\n" ANSI_COLOR_RESET, answer);
                        break;
                    }
                }

            } while (toupper(answer) != 'Y' && toupper(answer) != 'N');

            pFile = fopen(fileName, "r");
            if (pFile == NULL)
            {
                printf(ANSI_COLOR_RED "An error occurred: could not open '%s'. Exiting...." ANSI_COLOR_RESET, fileName);
                exit(1);
            }

            int lineIndex = 0;
            while (!feof(pFile))
            {
                output.size++;
                    
                fscanf(pFile, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", 
                    &(outputVect[vectorIndex].hasAlternative), // Alternativa
                    &(outputVect[vectorIndex].hasBar), // Bar
                    &(outputVect[vectorIndex].onFriOrSat), // Giorno
                    &(outputVect[vectorIndex].isHungry), // Fame
                    &(outputVect[vectorIndex].waiting), // Affollato
                    &(outputVect[vectorIndex].expensiveness), // Prezzo
                    &(outputVect[vectorIndex].isRaining), // Pioggia
                    &(outputVect[vectorIndex].hasReservation), // Prenotazione
                    &(outputVect[vectorIndex].type), // Tipo
                    &(outputVect[vectorIndex].waiting), // Attesa stimata
                    &(outputVect[vectorIndex].considered)); // Da considerare

                vectorIndex++;
                lineIndex++;
            }

            fclose(pFile);
            break;
        }

        case undefined:
        {
            printf(ANSI_COLOR_RED "An unexpected error occurred. Restart the program and try again." ANSI_COLOR_RESET);
            exit(1);
        }
    }

    output.data = outputVect;

    return output;
}

void printComparison(Hypothesis* current, int index, Hypothesis* general) 
{
    char *crowd_status_possibilities[] = {"nessuno", "qualcuno", "pieno", "-"};
    char *price_tag_possibilities[] = {"$", "$$", "$$$", "-"};
    char *restaurant_type_possibilities[] = {"italiano", "francese", "fast-food", "thai", "-"};
    char *estimated_waiting_possibilities[] = {"<10", "10-29", "30-60", ">60", "-"};
    char *qbit_possibilities[] = {"no","sì", "-"};

    printf("Comparison between:\n\n");
    printf("> Hypothesis nr. %d\n", index + 1);
    printf("{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}\n\n", 
        qbit_possibilities[current[index].hasAlternative],
        qbit_possibilities[current[index].hasBar],
        qbit_possibilities[current[index].onFriOrSat],
        qbit_possibilities[current[index].isHungry],
        crowd_status_possibilities[current[index].crowdStatus],
        price_tag_possibilities[current[index].expensiveness],
        qbit_possibilities[current[index].isRaining],
        qbit_possibilities[current[index].hasReservation],
        restaurant_type_possibilities[current[index].type],
        estimated_waiting_possibilities[current[index].waiting]);

    printf("> General hypothesis:\n");
    printf("{%s,%s,%s,%s,%s,%s,%s,%s,%s,%s}\n\n", 
        qbit_possibilities[general->hasAlternative],
        qbit_possibilities[general->hasBar],
        qbit_possibilities[general->onFriOrSat],
        qbit_possibilities[general->isHungry],
        crowd_status_possibilities[general->crowdStatus],
        price_tag_possibilities[general->expensiveness],
        qbit_possibilities[general->isRaining],
        qbit_possibilities[general->hasReservation],
        restaurant_type_possibilities[general->type],
        estimated_waiting_possibilities[general->waiting]);

    SLEEP(1);
}

bool Aspettiamo(HypothesisList* hypos) 
{
    Hypothesis general_hypothesis;

    bool firstHypothesis = true;
    for (int i = 0; i < hypos->size; i++)
    {
        CLEAR_CONSOLE;
        
        if (hypos->data[i].considered && firstHypothesis) 
        {
            firstHypothesis = false;
            general_hypothesis.hasAlternative = hypos->data[i].hasAlternative;
            general_hypothesis.hasBar = hypos->data[i].hasBar;
            general_hypothesis.onFriOrSat = hypos->data[i].onFriOrSat;
            general_hypothesis.isHungry = hypos->data[i].isHungry;
            general_hypothesis.crowdStatus = hypos->data[i].crowdStatus;
            general_hypothesis.expensiveness = hypos->data[i].expensiveness;
            general_hypothesis.isRaining = hypos->data[i].isRaining;
            general_hypothesis.hasReservation = hypos->data[i].hasReservation;
            general_hypothesis.type = hypos->data[i].type;
            general_hypothesis.waiting = hypos->data[i].waiting;
        }
        else if (hypos->data[i].considered) 
        {
            if (general_hypothesis.hasAlternative != hypos->data[i].hasAlternative)
                general_hypothesis.hasAlternative = general;
            
            if (general_hypothesis.hasBar != hypos->data[i].hasBar)
                general_hypothesis.hasBar = general;

            if (general_hypothesis.onFriOrSat != hypos->data[i].onFriOrSat)
                general_hypothesis.onFriOrSat = general;
            
            if (general_hypothesis.isHungry != hypos->data[i].isHungry)
                general_hypothesis.isHungry = general;

            if (general_hypothesis.crowdStatus != hypos->data[i].crowdStatus)
                general_hypothesis.crowdStatus = generalStatus;

            if (general_hypothesis.expensiveness != hypos->data[i].expensiveness)
                general_hypothesis.expensiveness = generalPrice;

            if (general_hypothesis.isRaining != hypos->data[i].isRaining)
                general_hypothesis.isRaining = general;

            if (general_hypothesis.hasReservation != hypos->data[i].hasReservation)
                general_hypothesis.hasReservation = general;

            if (general_hypothesis.type != hypos->data[i].type)
                general_hypothesis.type = generalType;

            if (general_hypothesis.waiting != hypos->data[i].waiting)
                general_hypothesis.waiting = generalWaiting;
        }

        printComparison(hypos->data, i, &general_hypothesis);
    }
    
    return false;
}

int main() 
{
    CLEAR_CONSOLE;
    printf(ANSI_COLOR_BLUE "- Welcome to Find-S Algorithm -\n" ANSI_COLOR_RESET);
    
    InputMode mode = getInputMode();
    HypothesisList data = retrieveData(mode);
    bool aspetta = Aspettiamo(&data);
    
    return 0;
}
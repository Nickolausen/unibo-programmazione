#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms * 1000)
#define CLEAR_CONSOLE system("cls")
#else
#include <unistd.h>
#define SLEEP(s) sleep(s)
#define CLEAR_CONSOLE system("clear")
#endif
#define LINE_SPLITTER puts("\n----------")

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

/* con questo metodo controllo se nel processo di conversione da stringa a intero l'utente ha
   inserito un valore oltre i limiti del tipo intero, per poterlo richiedere
*/ 
int hasBeenTruncated(int value, char input[]) {

    char intMaxToString[30];
    itoa(INT_MAX, intMaxToString, 10);
    char intMinToString[30];
    itoa(INT_MIN, intMinToString, 10);

    if(value==INT_MAX) {
        if(strcmp(input, intMaxToString) == 0)
            return 0;
        return 1;
    }
    if(value==INT_MIN) {
        if(strcmp(input, intMinToString) == 0)
            return 0;
        return 1;
    }
    return 0;
}

int *generateVector(int vectLength)
{

    int minVal, maxVal;
    do
    {
        printf("\nInserisci il numero minimo generabile (>=%d, <%d): ", INT_MIN, INT_MAX);
        fflush(stdin);
        scanf("%d", &minVal);
    } while (minVal < INT_MIN || minVal >= INT_MAX);

    do
    {
        printf("\nInserisci il numero massimo generabile (>=%d, <=%d): ", minVal, INT_MAX);
        fflush(stdin);
        scanf("%d", &maxVal);
    } while (maxVal < minVal || maxVal > INT_MAX);

    int *vector = malloc(vectLength * sizeof(int));

    for (int i = 0; i < vectLength; i++)
    {
        vector[i] = rand() % (maxVal - minVal + 1) + minVal;
    }

    return vector;
}

int main()
{

    srand(time(NULL));

    // numero di caratteri sufficiente a contenere in una stringa qualsiai numero intero
    const int MAX_INPUT_LENGTH = 50;

    int *vect1, *vect2;
    int vect1Length, vect2Length;
    char fillingType;

    printf("Vettore 1");
    do
    {
        printf("\nVuoi inserire i valori o generarli random (i/g): ");
        fflush(stdin);
        fillingType = getchar();
    } while (fillingType != 'i' && fillingType != 'g');

    if (fillingType == 'g')
    {
        do
        {
            printf("\nQuanti valori devono essere generati? (min: 1, max: %d) ", INT_MAX);
            fflush(stdin);
            scanf("%d", &vect1Length);
        } while (vect1Length < 1 || vect1Length > INT_MAX);

        vect1 = generateVector(vect1Length);
    }
    else
    {
        vect1 = malloc(0);
        int i = 0;
        char input[MAX_INPUT_LENGTH];
        int exit = 0;
        do
        {
            printf("\nInserisci un numero (# per terminare): ");
            fflush(stdin);
            scanf("%s", input);
            if (strcmp(input, "#") == 0)
            {
                exit = 1;
            }
            else
            {
                long tmp;
                int convertedVal;
                char *pointerEnd;

                tmp = strtol(input, &pointerEnd, 10);


                if (pointerEnd != input)
                {
                    if (!hasBeenTruncated(tmp, input))
                    {
                        convertedVal = (int)tmp;
                        vect1 = realloc(vect1, (i + 1) * sizeof(int));
                        vect1[i] = convertedVal;
                        i++;
                    }
                    else
                    {
                        printf("Numero oltre i limiti (min: %d, max: %d)", INT_MIN, INT_MAX);
                    }
                }
                else
                {
                    printf("Input non valido.");
                }
            }
        } while (!exit);
        vect1Length = i;
    }

    LINE_SPLITTER;

    printf("\nVettore 2");
    do
    {
        printf("\nVuoi inserire i valori o generarli random (i/g): ");
        fflush(stdin);
        fillingType = getchar();
    } while (fillingType != 'i' && fillingType != 'g');

    if (fillingType == 'g')
    {
        do
        {
            printf("\nQuanti valori devono essere generati? (min: 1, max: %d) ", INT_MAX);
            fflush(stdin);
            scanf("%d", &vect2Length);
        } while (vect2Length < 1 || vect2Length > INT_MAX);

        vect2 = generateVector(vect2Length);
    }
    else
    {
        vect2 = malloc(0);
        int i = 0;
        char input[MAX_INPUT_LENGTH];
        int exit = 0;
        do
        {
            printf("\nInserisci un numero (# per terminare): ");
            fflush(stdin);
            scanf("%s", input);
            if (strcmp(input, "#") == 0)
            {
                exit = 1;
            }
            else
            {
                long tmp;
                int convertedVal;
                char *pointerEnd;

                tmp = strtol(input, &pointerEnd, 10);

                if (pointerEnd != input)
                {
                    if (!hasBeenTruncated(tmp, input))
                    {
                        convertedVal = (int)tmp;
                        vect2 = realloc(vect2, (i + 1) * sizeof(int));
                        vect2[i] = convertedVal;
                        i++;
                    }
                    else
                    {
                        printf("Numero oltre i limiti (min: %d, max: %d)", INT_MIN, INT_MAX);
                    }
                }
                else
                {
                    printf("Input non valido.");
                }
            }

        } while (!exit);
        vect2Length = i;
    }

    LINE_SPLITTER;

    for (int i = 0; i < vect1Length; i++)
    {
        printf("%d ", vect1[i]);
    }

    printf("\n");

    for (int i = 0; i < vect2Length; i++)
    {
        printf("%d ", vect2[i]);
    }

    return 0;
}
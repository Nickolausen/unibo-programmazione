#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms * 1000)
    #define CLEAR_CONSOLE system("cls")
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
    #define CLEAR_CONSOLE system("clear")
#endif

#define ARR_COUNT(a) (int)(sizeof(a) / sizeof(a[0]))
#define RND_CHAR (rand() % (126 - 32)) + 32

#define CARATTERI_PER_VOLTA 3
#define INTERVALLO_DI_TEMPO 0.1
#define MAX_INPUT_LENGTH 1000

#define GRN "\e[0;32m"
#define BLU "\e[0;34m"
#define CRESET "\e[0m"

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

int main()
{
    CLEAR_CONSOLE;
    char stringaIniziale[MAX_INPUT_LENGTH];
    printf("=== Inserisci un testo da criptare [MAX %d CARATTERI] ===\n", MAX_INPUT_LENGTH);
    fgets(stringaIniziale, sizeof(stringaIniziale), stdin);

    char stringaCriptata[strlen(stringaIniziale) + 1];
    bool caratteriSostituiti[strlen(stringaIniziale) + 1];
    srand(time(NULL));

    // Imposto carattere di terminazione alla stringa criptata
    // Riempio la stringa criptata di char random e imposto i valori di caratteriSostituiti a 0
    int i;
    for (i = 0; i < (int)strlen(stringaIniziale) - 1; i++)
    {
        stringaCriptata[i] = RND_CHAR;
        caratteriSostituiti[i] = false;
    }

    stringaCriptata[i] = '\0';

    int nrCharDaSostituire = (int)strlen(stringaIniziale) - 1;
    int idx = 0, indiceDaSostituire = -1;
    // ripeto finché ci sono valori da sostituire
    CLEAR_CONSOLE;
    while (nrCharDaSostituire > 0)
    {
        idx = 0;
        // sostiuisco n caratteri per ogni stampa
        while (idx < CARATTERI_PER_VOLTA)
        {
            do
            {
                /* genero randomicamente un indice da sostituire all'interno della stringa criptata
                e controllo di non aver già sostituito in quella posizione */
                indiceDaSostituire = (rand() % (strlen(stringaIniziale) - 1));
            } while (caratteriSostituiti[indiceDaSostituire]);

            // sostituisco nella stringa criptata l'indice generato con il rispettivo carattere giusto
            stringaCriptata[indiceDaSostituire] = stringaIniziale[indiceDaSostituire];
            // segno in caratteriSostituiti l'indice che ho sostituito
            caratteriSostituiti[indiceDaSostituire] = true;
            nrCharDaSostituire--;
            idx++;

            for (int j = 0; j < (int)strlen(stringaCriptata); j++)
            {
                if (stringaCriptata[j] == stringaIniziale[j])
                    printf(BLU "%c" CRESET, stringaCriptata[j]);
                else
                    printf(GRN "%c" CRESET, stringaCriptata[j]);
            }
            printf("\n");
            /* se non ci sono più caratteri da sostituire ma non ho sostituto abbastanza caratteri
            per questo giro di stampa, esco comunque dal ciclo*/
            if (nrCharDaSostituire == 0)
                idx = CARATTERI_PER_VOLTA;
            else 
            {
                unsigned int time = 0;
                for (time = 0; time < 10000000; time++) { }
                CLEAR_CONSOLE;
            }
        }
    }

    return 0;
}
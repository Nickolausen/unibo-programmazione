#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms * 1000)
#define CLEAR_CONSOLE system("cls")
#else
#include <unistd.h>
#define SLEEP(s) sleep(s)
#define CLEAR_CONSOLE system("clear")
#endif
#define LINE_SPLITTER puts("\n\n----------")
#define LENGTH(a) (int)(sizeof(a) / sizeof(a[0]))
#define RND_CHAR (rand() % (126 - 32)) + 32
#define STRINGA_INIZIALE "e' difficile programmare in C quando ti hanno insegnato con C#..."
#define CARATTERI_PER_VOLTA 3
#define INTERVALLO_DI_TEMPO 0.1

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

int main()
{
    char stringaIniziale[] = STRINGA_INIZIALE;
    char stringaCriptata[LENGTH(stringaIniziale)];
    int caratteriSostituiti[LENGTH(stringaIniziale) - 1];
    srand(time(NULL));

    // imposto carattere di terminazione alla stringa criptata
    stringaCriptata[LENGTH(stringaIniziale) - 1] = '\0';
    // riempio la stringa criptata di char random e imposto i valori di caratteriSostituiti a 0
    for (int i = 0; i < LENGTH(stringaIniziale) - 1; i++)
    {
        stringaCriptata[i] = RND_CHAR;
        caratteriSostituiti[i] = 0;
    }

    int daSostituire = LENGTH(stringaIniziale) - 1;
    int i, indiceDaSostituire;
    // ripeto finché ci sono valori da sostituire
    while (daSostituire > 0)
    {

        CLEAR_CONSOLE;
        printf("%s", stringaCriptata);
        SLEEP(INTERVALLO_DI_TEMPO);
        i = 0;

        // sostiuisco n caratteri per ogni stampa
        while (i < CARATTERI_PER_VOLTA)
        {
            indiceDaSostituire;
            do
            {
                /* genero randomicamente un indice da sostituire all'interno della stringa criptata
                e controllo di non aver già sostituito in quella posizione */
                indiceDaSostituire = (rand() % (LENGTH(stringaIniziale) - 1));
            } while (caratteriSostituiti[indiceDaSostituire] == 1);

            // sostituisco nella stringa criptata l'indice generato con il rispettivo carattere giusto
            stringaCriptata[indiceDaSostituire] = stringaIniziale[indiceDaSostituire];
            // segno in caratteriSostituiti l'indice che ho sostituito
            caratteriSostituiti[indiceDaSostituire] = 1;
            daSostituire--;
            i++;
            /*se non ci sono più caratteri da sostituire ma non ho sostituto abbastanza caratteri
            per questo giro di stampa, esco comunque dal ciclo*/
            if (daSostituire == 0)
                i = CARATTERI_PER_VOLTA;
        }
    }

    CLEAR_CONSOLE;
    printf("%s", stringaCriptata);
}
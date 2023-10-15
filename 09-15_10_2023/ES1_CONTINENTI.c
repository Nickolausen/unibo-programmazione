// varie librerie utilizzate
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>

// Per separare nel terminale
#define LINE_SPLITTER puts("\n-------------")
#define MAX_ANSWER_LENGTH 8

// Per rendere uguali le funzioni di sleep() tra le varie piattaforme,
// rendiamo uguali le unità di misura del tempo che i parametri utilizzano;
// > windows accetta il tempo in millisecondi, per cui moltiplichiamo * 1000 per renderli secondi.
#ifdef _WIN32
#include <windows.h>
#define SLEEP(ms) Sleep(ms * 1000)
#define CLEAR_CONSOLE system("cls")
#else
#include <unistd.h>
#define SLEEP(s) sleep(s)
#define CLEAR_CONSOLE system("clear")
#endif

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

// Creo le struct necessarie
struct Coordinate
{
    int latitudine;
    int longitudine;
};

struct Continente
{
    char nome[100];
    struct Coordinate confineAltoSinistro;
    struct Coordinate confineBassoDestro;
};

// Creo i metodi per rendere il codice del main più pulito e meno ripetitivo
bool isCoordinateInterne(struct Continente cont, struct Coordinate coor)
{
    return (cont.confineBassoDestro.latitudine <= coor.latitudine && cont.confineAltoSinistro.latitudine >= coor.latitudine) &&
        (cont.confineAltoSinistro.longitudine <= coor.longitudine && cont.confineBassoDestro.longitudine >= coor.longitudine);
}

bool isContinenteCorrispondente(char risp[MAX_ANSWER_LENGTH], struct Continente cont, struct Coordinate daIndovinare)
{
    // Se la risposta coincide con il continente preso in analisi, e le coordinate
    // del continente mostrate sono contenute nel continente indicato dal giocatore
    // ritorno True; False altrimenti.
    // char normalizedAnswer[MAX_ANSWER_LENGTH];
    // for (int i = 0; i < MAX_ANSWER_LENGTH; i++)
    //     normalizedAnswer[i] = tolower(risp[i]);

    return (strcmp(strlwr(risp), cont.nome) == 0) && isCoordinateInterne(cont, daIndovinare);
}

void printContinente(struct Continente toPrint) {
    printf("Continente %s:\n", strupr(toPrint.nome));
    printf("(%d;%d)*********|\n", toPrint.confineAltoSinistro.longitudine, toPrint.confineAltoSinistro.latitudine);
    printf("   |*********(%d;%d)\n", toPrint.confineBassoDestro.longitudine, toPrint.confineBassoDestro.latitudine);
}

int main()
{
    CLEAR_CONSOLE;
    // Continenti modello ONU: America, Europa, Africa, Asia, Oceania;
    // Dichiaro tutti i continenti con le loro coordinate, ho semplificato rendendoli tutti dei rettangoli
    // ma anche cambiando le coordinate rimanendo tra 0-100 di latitudine e 0-250 di longitudine senza
    // sovrapporre i continenti funziona comunque
    struct Continente america;
    strcpy(america.nome, "america");
    america.confineAltoSinistro.latitudine = 100;
    america.confineAltoSinistro.longitudine = 0;
    america.confineBassoDestro.latitudine = 0;
    america.confineBassoDestro.longitudine = 50;
    printContinente(america);
    LINE_SPLITTER;

    struct Continente europa;
    strcpy(europa.nome, "europa");
    europa.confineAltoSinistro.latitudine = 100;
    europa.confineAltoSinistro.longitudine = 51;
    europa.confineBassoDestro.latitudine = 0;
    europa.confineBassoDestro.longitudine = 100;
    printContinente(europa);
    LINE_SPLITTER;
    
    struct Continente africa;
    strcpy(africa.nome, "africa");
    africa.confineAltoSinistro.latitudine = 100;
    africa.confineAltoSinistro.longitudine = 101;
    africa.confineBassoDestro.latitudine = 0;
    africa.confineBassoDestro.longitudine = 150;
    printContinente(africa);
    LINE_SPLITTER;
    
    struct Continente asia;
    strcpy(asia.nome, "asia");
    asia.confineAltoSinistro.latitudine = 100;
    asia.confineAltoSinistro.longitudine = 151;
    asia.confineBassoDestro.latitudine = 0;
    asia.confineBassoDestro.longitudine = 200;
    printContinente(asia);
    LINE_SPLITTER;
    
    struct Continente oceania;
    strcpy(oceania.nome, "oceania");
    oceania.confineAltoSinistro.latitudine = 100;
    oceania.confineAltoSinistro.longitudine = 201;
    oceania.confineBassoDestro.latitudine = 0;
    oceania.confineBassoDestro.longitudine = 250;
    printContinente(oceania);
    LINE_SPLITTER;

    // Dichiaro il random per estrarre le coordinate
    srand(time(0));

    // Dichiaro la variabile delle coordinate da indovinare
    struct Coordinate daIndovinare;

    bool keepPlaying = false;
    SLEEP(5);
    do
    {
        CLEAR_CONSOLE;
        bool onStreak = true;
        int score = -1;

        // Il gioco continua finché il giocatore non smette di indovinare
        while (onStreak)
        {
            score++;

            // Estraggo randomicamente delle coordinate
            daIndovinare.latitudine = rand() % 100 + 1;
            daIndovinare.longitudine = rand() % 100 * 2.5 + 1;

            printf("Punteggio: %d\n", score);
            // Mostro temporaneamente le coordinate generate
            printf("\nLATITUDINE: %d\nLONGITUDINE: %d", daIndovinare.latitudine, daIndovinare.longitudine);

            SLEEP(5);
            CLEAR_CONSOLE;

            // Chiedo di indovinare
            printf("\nDigita il nome del continente... (premi INVIO per continuare) ");
            char contRisp[MAX_ANSWER_LENGTH];
            scanf("%s", contRisp);

            onStreak = isContinenteCorrispondente(contRisp, america, daIndovinare) ||
                    isContinenteCorrispondente(contRisp, europa, daIndovinare) ||
                    isContinenteCorrispondente(contRisp, africa, daIndovinare) ||
                    isContinenteCorrispondente(contRisp, asia, daIndovinare) ||
                    isContinenteCorrispondente(contRisp, oceania, daIndovinare);

            if (onStreak) {
                printf("Ben fatto! Preparati al prossimo round.");
                SLEEP(3);
                CLEAR_CONSOLE;
            }
        }

        printf("\nHai sbagliato!\n> Punteggio ottenuto: %d", score);
        LINE_SPLITTER;
        fflush(stdin);
        printf("Vuoi rigiocare? [Y/n] ");
        char answer = getchar();

        keepPlaying = toupper(answer) == 'Y';
    } while (keepPlaying);

    return 0;
}
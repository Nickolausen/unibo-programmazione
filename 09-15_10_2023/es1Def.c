//varie librerie utilizzate
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Per separare nel terminale
#define LINE_SPLITTER puts("\n-------------")

#ifdef _WIN32 // valido sia per 32 che 64 bit
	#define CLEAR_CONSOLE system("cls");
#else
    #define CLEAR_CONSOLE system("clear");
#endif

#ifdef _WIN32
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms * 1000)
#else
    #include <unistd.h>
    #define SLEEP(s) sleep(s)
#endif

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

// Creo le struct che mi servono per dopo
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

bool isContinenteCorrispondente(char risp[7], struct Continente cont, struct Coordinate daIndovinare)
{
    // Se la risposta coincide con il continente preso in analisi, e le coordinate 
    // del continente mostrate sono contenute nel continente indicato dal giocatore
    // ritorno True; False altrimenti.
    char normalizedAnswer[7];
    for (int i = 0; i < 7; i++)
        normalizedAnswer[i] = tolower(risp[i]);
    
    return (strcmp(normalizedAnswer, cont.nome) == 0) && isCoordinateInterne(cont, daIndovinare);
}

int main()
{
    // Continenti modello ONU quindi 5;
    // Dichiaro tutti i continenti con le loro coordinate, ho semplificato rendendoli tutti dei rettangoli
    // ma anche cambiando le coordinate rimanendo tra 0-100 di latitudine e 0-250 di longitudine senza 
    // sovrapporre i continenti funziona comunque
    struct Continente america;
    strcpy(america.nome, "america");
    america.confineAltoSinistro.latitudine = 100;
    america.confineAltoSinistro.longitudine = 0;
    america.confineBassoDestro.latitudine = 0;
    america.confineBassoDestro.longitudine = 50;
    struct Continente europa;
    strcpy(europa.nome, "europa");
    europa.confineAltoSinistro.latitudine = 100;
    europa.confineAltoSinistro.longitudine = 51;
    europa.confineBassoDestro.latitudine = 0;
    europa.confineBassoDestro.longitudine = 100;
    struct Continente africa;
    strcpy(africa.nome, "africa");
    africa.confineAltoSinistro.latitudine = 100;
    africa.confineAltoSinistro.longitudine = 101;
    africa.confineBassoDestro.latitudine = 0;
    africa.confineBassoDestro.longitudine = 150;
    struct Continente asia;
    strcpy(asia.nome, "asia");
    asia.confineAltoSinistro.latitudine = 100;
    asia.confineAltoSinistro.longitudine = 151;
    asia.confineBassoDestro.latitudine = 0;
    asia.confineBassoDestro.longitudine = 200;
    struct Continente oceania;
    strcpy(oceania.nome, "oceania");
    oceania.confineAltoSinistro.latitudine = 100;
    oceania.confineAltoSinistro.longitudine = 201;
    oceania.confineBassoDestro.latitudine = 0;
    oceania.confineBassoDestro.longitudine = 250;

    // Dichiaro il random per estrarre le coordinate
    srand(time(0));

    // Dichiaro la variabile delle coordinate da indovinare
    struct Coordinate daIndovinare;

    bool onStreak = true;
    int score = -1;

    // Il gioco continua finché il giocatore non smette di indovinare
    while (onStreak)
    {
        score++;
        
        // estraggo le coordinate
        daIndovinare.latitudine = rand() % 100 + 1;
        daIndovinare.longitudine = rand() % 100 * 2.5 + 1;

        // Mostro temporaneamente le coordinate generate
        printf("\nLATITUDINE: %d\nLONGITUDINE:%d", daIndovinare.latitudine, daIndovinare.longitudine);

        SLEEP(5);
        CLEAR_CONSOLE;

        // Chiedo di indovinare
        printf("\nIndovina il continente (premi INVIO per continuare): ");
        char contRisp[7];
        scanf("%s", contRisp);

        onStreak = isContinenteCorrispondente(contRisp, america, daIndovinare) ||
            isContinenteCorrispondente(contRisp, europa, daIndovinare) ||
            isContinenteCorrispondente(contRisp, africa, daIndovinare) ||
            isContinenteCorrispondente(contRisp, asia, daIndovinare) ||
            isContinenteCorrispondente(contRisp, oceania, daIndovinare);

        SLEEP(5);
        CLEAR_CONSOLE;
    }

    printf("\nHai sbagliato \nPunteggio ottenuto: %d", score);

    return 0;
}
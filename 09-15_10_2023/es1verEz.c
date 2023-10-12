#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Per separare nel terminale
#define LINE_SPLITTER puts("\n-------------")
#define CLEAR_CONSOLE system("clear") == 1 ? system("cls") : system("clear")

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

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

bool ControlloGiusto(struct Continente cont, struct Coordinate coor)
{
    if (cont.confineBassoDestro.latitudine < coor.latitudine && cont.confineAltoSinistro.latitudine > coor.latitudine)
    {
        if (cont.confineAltoSinistro.longitudine < coor.longitudine && cont.confineBassoDestro.longitudine > coor.longitudine)
        {
            return true;
        }
    }
    return false;
}

void Dormi(int tempo)
{
    for (int i = 0; i < tempo * pow(10.0, 7); i++)
    {
    }
    CLEAR_CONSOLE;
}

bool Controllo(char risp[7], struct Continente cont, struct Coordinate daIndovinare)
{
    if (strcmp(risp, cont.nome) == 0)
    {
        if (ControlloGiusto(cont, daIndovinare))
        {
            printf("Hai indovinato!!!");
            return true;
        }
    }
    return false;
}

int main()
{
    // continenti modello ONU quindi 5
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

    srand(time(0));
    int start;
    while (true)
    {
        printf("\nIn 3 secondi ti verranno mostrate le coordinate, indovina in quale dei 5 continenti è");
        Dormi(5);
        printf("\n3");
        Dormi(2);
        printf("\n2");
        Dormi(2);
        printf("\n1");
        printf("\nVIA!!!");
        Dormi(1);

        struct Coordinate daIndovinare;
        daIndovinare.latitudine = rand() % 100 + 1;
        daIndovinare.longitudine = rand() % 100 * 2.5 + 1;
        printf("\nLa latidine è: %d La longitudine è:%d", daIndovinare.latitudine, daIndovinare.longitudine);
        Dormi(10);
        start = time(NULL);
        printf("\nIndovina il continente (quando hai finito di scrivere il continente premi ctrl+Z/D): ");
        char contRisp[7];
        int numCar = 0;
        while (getchar() != EOF)
        {
            numCar++;
        }
        scanf("%s", contRisp);
        if (Controllo(contRisp, america, daIndovinare))
            break;
        if (Controllo(contRisp, europa, daIndovinare))
            break;
        if (Controllo(contRisp, africa, daIndovinare))
            break;
        if (Controllo(contRisp, asia, daIndovinare))
            break;
        if (Controllo(contRisp, oceania, daIndovinare))
            break;
        printf("\nHai sbagliato \nRiprova con delle coordinate nuove");
        Dormi(1);
    }
    int tempo = start - time(NULL);
    printf("Ci hai messo %d ", tempo);
    return 0;
}
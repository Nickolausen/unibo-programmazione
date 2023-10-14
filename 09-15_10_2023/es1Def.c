//varie librerie utilizzate
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Per separare nel terminale
#define LINE_SPLITTER puts("\n-------------")
//per pulire la console
#define CLEAR_CONSOLE system("clear") == 1 ? system("cls") : system("clear")

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

//creo le struct che mi servono per dopo
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

//creo i metodi per rendere il codice del main più pulito e meno ripetitivo
bool ControlloGiusto(struct Continente cont, struct Coordinate coor)
{
    if (cont.confineBassoDestro.latitudine <= coor.latitudine && cont.confineAltoSinistro.latitudine >= coor.latitudine)
    {
        if (cont.confineAltoSinistro.longitudine <= coor.longitudine && cont.confineBassoDestro.longitudine >= coor.longitudine)
        {
            return true;
        }
    }
    return false;
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

//per non utilizzare la funzione sleep
void Dormi(int tempo)
{
    for (int i = 0; i < tempo * pow(10.0, 7); i++){
    }
    CLEAR_CONSOLE;
}



int main()
{
    // continenti modello ONU quindi 5
    //dichiaro tutti i continenti con le loro coordinate, ho semplificato rendendoli tutti dei rettangoli
    //ma anche cambiando le coordinate rimanendo tra 0-100 di latitudine e 0-250 di longitudine senza 
    //sovrapporre i continenti funziona comunque
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

    //dichiaro il random per estrarre le coordinate
    srand(time(0));
    //dichiaro l'int in cui metterò il timer
    int start;
    //dichiaro la variabile delle coordinate da indovinare
    struct Coordinate daIndovinare;

    //finchè non indovina il ciclo và avanti
    while (true)
    {
        //estraggo le coordinate
        daIndovinare.latitudine = rand() % 100 + 1;
        daIndovinare.longitudine = rand() % 100 * 2.5 + 1;

        //le faccio vedere temporaneamente
        printf("\nLa latidine è: %d La longitudine è:%d", daIndovinare.latitudine, daIndovinare.longitudine);

        //intanto starto il cronometro
        start = time(NULL);

        //chiedo di indovinare
        printf("\nIndovina il continente (quando hai finito di scrivere il continente premi invio): ");
        //non mettendo qui questa funzione non mi cleara le coordinate e non aspetta un po'
        //di tempo con il ciclo intutile 
        Dormi(13);
        //lo prendo in input
        char contRisp[7];
        scanf("%s", contRisp);

        //controllo se ha scritto giusto e dove sono le coordinate estratte
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
        //se ha sbagliato riprova a indovinare
        printf("\nHai sbagliato \nRiprova con delle coordinate nuove");
        Dormi(2);
    }
    //quando è uscito calcolo il tempo che ci ha messo per la risposta corrente
    int tempo = time(NULL) - start;
    //e lo mando in output
    printf("\nCi hai messo %d secondi\n", tempo);
    return 0;
}
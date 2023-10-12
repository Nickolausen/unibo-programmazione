#include <stdio.h>
#include <unistd.h>
#include <float.h>

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

struct coordinate{
    int latitudine;
    int longitudine;
};

struct Continente{

    struct coordinate confineAltoSinistro;
    struct coordinate confineBassoDestro;
};

int main(){

    // continenti modello ONU quindi 5
    struct Continente america;
    america.confineAltoSinistro.latitudine = 100;
    america.confineAltoSinistro.longitudine = 0;
    america.confineBassoDestro.latitudine = 0;
    america.confineBassoDestro.longitudine = 50;
    struct Continente europa;
    europa.confineAltoSinistro.latitudine = 100;
    europa.confineAltoSinistro.longitudine = 51;
    europa.confineBassoDestro.latitudine = 0;
    europa.confineBassoDestro.longitudine = 100;
    struct Continente africa;
    africa.confineAltoSinistro.latitudine = 100;
    africa.confineAltoSinistro.longitudine = 101;
    africa.confineBassoDestro.latitudine = 0;
    africa.confineBassoDestro.longitudine = 150;
    struct Continente asia;
    asia.confineAltoSinistro.latitudine = 100;
    asia.confineAltoSinistro.longitudine = 151;
    asia.confineBassoDestro.latitudine = 0;
    asia.confineBassoDestro.longitudine = 200;
    struct Continente oceania;
    oceania.confineAltoSinistro.latitudine = 100;
    oceania.confineAltoSinistro.longitudine = 201;
    oceania.confineBassoDestro.latitudine = 0;
    oceania.confineBassoDestro.longitudine = 250;

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define CLEAR_CONSOLE system("clear") == 1 ? system("cls") : system("clear")

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

typedef struct Statistiche {
    int nrAlphanumeric = 0;
    int nrAlpha = 0;
    int nrControl = 0;
    int nrDigit = 0;
    int nrGraph = 0;
    int nrLower = 0;
    int nrPrint = 0;
    int nrPunct = 0;
    int nrSpace = 0;
    int nrUpper = 0;
    int nrXDigit = 0;
} Statistiche;

int main()
{
    CLEAR_CONSOLE;
    char c;

    Statistiche stats;
    char * sLower;
    char * sUpper;

    while ((c = getchar()) != EOF)
    {
        if(isalnum(c))
            stats.nAlphanumeric++;
        if(isalpha(c))
            nAlpha++;
        if(iscntrl(c))
            nControl++;
        if(isdigit(c))
            nDigit++;
        if(isgraph(c))
            nGraph++;
        if(islower(c))
            nLower++;
        if(isprint(c))
            nPrint++;
        if(ispunct(c))
            nPunct++;
        if(isspace(c))
            nSpace++;
        if(isupper(c))
            nUpper++;
        if(isxdigit(c))
            nXDigit++;
        
        sLower += tolower(c);
        sUpper += toupper(c);
    }
    
    printf("Numero Caratteri Alfanumerici: %d\n", nAlphanumeric);
    printf("Numero Caratteri Alfabetici: %d\n", nAlpha);
    printf("Numero Caratteri di Controllo: %d\n", nControl);
    printf("Numero di Cifre: %d\n", nDigit);
    printf("Numero Caratteri Diversi da Spazio: %d\n", nGraph);
    printf("Numero Caratteri Stampabili: %d\n", nPrint);
    printf("Numero Caratteri di Punteggiatura: %d\n", nPunct);
    printf("Numero Caratteri di Spazio: %d\n", nSpace);
    printf("Numero Caratteri Maiuscoli: %d\n", nUpper);
    printf("Numero Caratteri Esadecimali: %d\n", nXDigit);
    printf("Stringa Minuscola: %s\n", sLower);
    printf("Stringa Maiuscola: %s\n", sUpper);
    

    return 0;
}
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

int main()
{
    CLEAR_CONSOLE;
    char c;

    int nAlphanumeric = 0;
    int nAlpha = 0;
    int nControl = 0;
    int nDigit = 0;
    int nGraph = 0;
    int nLower = 0;
    int nPrint = 0;
    int nPunct = 0;
    int nSpace = 0;
    int nUpper = 0;
    int nXDigit = 0;
    char * sLower;
    char * sUpper;

    while ((c = getchar()) != '#')
    {
        if(isalnum(c))
            nAlphanumeric++;
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
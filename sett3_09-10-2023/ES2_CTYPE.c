#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#else
#define CLEAR_CONSOLE system("clear")
#endif

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

typedef struct Statistiche {
    int nrAlphanumeric;
    int nrAlpha;
    int nrControl;
    int nrDigit;
    int nrGraph;
    int nrLower;
    int nrPrint;
    int nrPunct;
    int nrSpace;
    int nrUpper;
    int nrXDigit;
} Statistiche;

int main()
{
    CLEAR_CONSOLE;
    char c;

    Statistiche stats = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int length = 0;
    char upperChar = '#', lowerChar = '#';
    printf("Inserisci un testo terminato da #:\n");
    while ((c = getchar()) != '#')
    {
        if(isalnum(c))
            stats.nrAlphanumeric++;
        if(isalpha(c))
            stats.nrAlpha++;
        if(iscntrl(c))
            stats.nrControl++;
        if(isdigit(c))
            stats.nrDigit++;
        if(isgraph(c))
            stats.nrGraph++;
        if(isprint(c))
            stats.nrPrint++;
        if(ispunct(c))
            stats.nrPunct++;
        if(isspace(c))
            stats.nrSpace++;
        if(isxdigit(c))
            stats.nrXDigit++;
        
        if(islower(c)) {
            stats.nrLower++;
            if (upperChar == '#') upperChar = toupper(c);
        }

        if(isupper(c)) {
            stats.nrUpper++;
            if (lowerChar == '#') lowerChar = tolower(c);
        }
    }
    
    printf("> Numero caratteri alfanumerici: %d\n", stats.nrAlphanumeric);
    printf("> Numero caratteri alfabetici: %d\n", stats.nrAlpha);
    printf("> Numero caratteri di controllo: %d\n", stats.nrControl);
    printf("> Numero di cifre: %d\n", stats.nrDigit);
    printf("> Numero caratteri != white_space: %d\n", stats.nrGraph);
    printf("> Numero caratteri stampabili: %d\n", stats.nrPrint);
    printf("> Numero caratteri di punteggiatura: %d\n", stats.nrPunct);
    printf("> Numero caratteri di spazio: %d\n", stats.nrSpace);
    printf("> Numero caratteri maiuscoli: %d\n", stats.nrUpper);
    printf("> Numero caratteri esadecimali: %d\n", stats.nrXDigit);
    puts("----");
    printf("Primo carattere minuscolo trasformato in MAIUSCOLO: %c\n", upperChar);
    printf("Primo carattere MAIUSCOLO trasformato in minuscolo: %c\n", lowerChar);
    return 0;
}
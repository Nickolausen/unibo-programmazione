#include <stdio.h>
#include <limits.h>
#include <float.h>
#define LINE_SPLITTER puts("----------")

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

void printNrChars(int nrChars) {
    printf("Numero di caratteri stampati: %d\n", nrChars);
    LINE_SPLITTER;
    return;
}

int main() {
    // Dichiarazione e inizializzazione delle variabili
    char charVar = 'A';
    unsigned char ucharVar = 255;
    short shortVar = 32767;
    unsigned short ushortVar = 65535;
    int intVar = INT_MAX;
    unsigned int uintVar = UINT_MAX;
    long longVar = LONG_MAX;
    unsigned long ulongVar = ULONG_MAX;
    float floatVar = FLT_MAX;
    double doubleVar = DBL_MAX;
    char stringVar[] = { 'H', 'e', 'l', 'l', 'o', ' ', '!'};
    
    // Utilizzo di tutti gli argomenti della printf() studiati
    printNrChars(printf("Modificatori:\n"));
    printNrChars(printf("%%d: %d\n", intVar));
    printNrChars(printf("%%6d: %6d\n", intVar));
    printNrChars(printf("%%.2f: %.2f\n", doubleVar));
    printNrChars(printf("%%c: %c\n", charVar));
    printNrChars(printf("%%s: %s\n", stringVar));
    printNrChars(printf("%%10s: %10s\n", stringVar));
    printNrChars(printf("%%-10s: %-10s\n", stringVar));
    printNrChars(printf("%%5.3f: %5.3f\n", doubleVar));
    printNrChars(printf("%%+d: %+d\n", intVar));
    printNrChars(printf("%%#x: %#x\n", 255));
    printNrChars(printf("%%o: %o\n", 255));
    printNrChars(printf("%%lld: %lld\n", 123456789012345LL));

    // Stampa dei valori e dell'occupazione di memoria con il numero di caratteri stampati
    printNrChars(printf("char: %c, Occupazione: %lu byte\n", charVar, sizeof(charVar)));
    printNrChars(printf("unsigned char: %u, Occupazione: %lu byte\n", ucharVar, sizeof(ucharVar)));
    printNrChars(printf("short: %hi, Occupazione: %lu byte\n", shortVar, sizeof(shortVar)));
    printNrChars(printf("unsigned short: %hu, Occupazione: %lu byte\n", ushortVar, sizeof(ushortVar)));
    printNrChars(printf("int: %d, Occupazione: %lu byte\n", intVar, sizeof(intVar)));
    printNrChars(printf("unsigned int: %u, Occupazione: %lu byte\n", uintVar, sizeof(uintVar)));
    printNrChars(printf("long: %ld, Occupazione: %lu byte\n", longVar, sizeof(longVar)));
    printNrChars(printf("unsigned long: %lu, Occupazione: %lu byte\n", ulongVar, sizeof(ulongVar)));
    printNrChars(printf("float: %f, Occupazione: %lu byte\n", floatVar, sizeof(floatVar)));
    printNrChars(printf("double: %lf, Occupazione: %lu byte\n", doubleVar, sizeof(doubleVar)));
    
    // Stampa dei valori massimi e minimi ammissibili
    printNrChars(printf("\nValori massimi e minimi per variabili di diversi tipi:\n"));
    printNrChars(printf("char: Min: %d, Max: %d\n", CHAR_MIN, CHAR_MAX));
    printNrChars(printf("unsigned char: Min: %d, Max: %d\n", 0, UCHAR_MAX));
    printNrChars(printf("short: Min: %d, Max: %d\n", SHRT_MIN, SHRT_MAX));
    printNrChars(printf("unsigned short: Min: %d, Max: %u\n", 0, USHRT_MAX));
    printNrChars(printf("int: Min: %d, Max: %d\n", INT_MIN, INT_MAX));
    printNrChars(printf("unsigned int: Min: %u, Max: %u\n", 0, UINT_MAX));
    printNrChars(printf("long: Min: %ld, Max: %ld\n", LONG_MIN, LONG_MAX));
    printNrChars(printf("unsigned long: Min: %d, Max: %lu\n", 0, ULONG_MAX));
    printNrChars(printf("float: Min: %E, Max: %E\n", FLT_MIN, FLT_MAX));
    printNrChars(printf("double: Min: %E, Max: %E\n", DBL_MIN, DBL_MAX));

    return 0;
}
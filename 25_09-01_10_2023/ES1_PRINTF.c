#include <stdio.h>
#include <limits.h> // Library which includes the maximum and minimum values for: (s/uns)char, (s/uns)short, (s/uns)int, (s/uns)long;
#include <float.h> // Library which includes, other than float and double characteristics, constants for their minimum and maximum values;
#define LINE_SPLITTER puts("\n-------------") // Just a puts with some dashes to separate each data type description

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
*/

int main() 
{
    /*
        Primary data types:
        > float
        > int
        > double
        > char
    */
    signed char signedCharVar = 'A';
    unsigned char unsignedCharVar = 'F';
    
    signed short signedShortVar = -30;
    unsigned short unsignedShortVar = 25;
    
    signed int signedIntVar = -10;
    unsigned int unsignedIntVar = 10;
    
    signed long singedLongVar = -2500;
    unsigned long unsignedLongVar = 3200;
    
    float floatVar = 1.5;
    double doubleVar = -1.25;
    long double longDoubleVar = 100.25;

    /* 
        In order to print the number of characters displayed for each type's description,
        we used the fact that the function "printf" returns the number of characters it puts out.
    */ 
    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %u \nMIN VALUE: %d \nMAX VALUE: %u \nBYTE: %lu\n", "Unsigned Char", "unsignedCharVar", unsignedCharVar, 0, UCHAR_MAX, sizeof(unsigned char)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %c \nMIN VALUE: %d \nMAX VALUE: %d \nBYTE: %lu\n", "Signed Char", "signedCharVar", signedCharVar, SCHAR_MIN, SCHAR_MAX, sizeof(signed char)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %d \nMIN VALUE: %d \nMAX VALUE: %d \nBYTE: %lu\n", "Signed Short", "signedShortVar", signedShortVar, SHRT_MIN, SHRT_MAX, sizeof(short)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %u \nMIN VALUE: %d \nMAX VALUE: %u \nBYTE: %lu\n", "Unsigned Short", "unsignedShortVar", unsignedShortVar, 0, USHRT_MAX, sizeof(unsigned short)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %d \nMIN VALUE: %d \nMAX VALUE: %d \nBYTE: %lu\n", "Signed Int", "signedIntVar", signedIntVar, INT_MIN, INT_MAX, sizeof(int)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %u \nMIN VALUE: %d \nMAX VALUE: %u \nBYTE: %lu\n", "Unsigned Int", "unsignedIntVar", unsignedIntVar, 0, UINT_MAX, sizeof(unsigned int)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %ld \nMIN VALUE: %ld \nMAX VALUE: %ld \nBYTE: %lu\n", "Signed Long", "singedLongVar", singedLongVar, LONG_MIN, LONG_MAX, sizeof(long)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %lu \nMIN VALUE: %d \nMAX VALUE: %lu \nBYTE: %lu\n", "Unsigned Long", "unsignedLongVar", unsignedLongVar, 0, ULONG_MAX, sizeof(unsigned long)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %f \nMIN VALUE: %e \nMAX VALUE: %e \nBYTE: %lu\n", "Float", "floatVar", floatVar, FLT_MIN, FLT_MAX, sizeof(float)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %f \nMIN VALUE: %e \nMAX VALUE: %e \nBYTE: %lu\n", "Double", "doubleVar", doubleVar, DBL_MIN, DBL_MAX, sizeof(double)));
    LINE_SPLITTER;

    printf("> PRINTED CHARACTERS: %d", 
        printf("TYPE: %s \nVARIABLE NAME: %s \nVALUE: %.10e \nMIN VALUE: %.10e \nMAX VALUE: %.10e \nBYTE: %lu\n", "Long Double", "longDoubleVar", longDoubleVar, LDBL_MIN, LDBL_MAX, sizeof(long double)));
    LINE_SPLITTER;

    return 0;
}
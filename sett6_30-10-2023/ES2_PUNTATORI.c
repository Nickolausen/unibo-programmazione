// Librerie che mi servono
#include <stdio.h>

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

int main()
{
    //dichiarazione variabili
    int varInt;
    float varFloat;
    double varDouble;
    char varChar = 'a';
    int arrInt[5] = {10,20,30,40,50};

    //dichiarazione puntatori variabili
    int* pointInt = &varInt;
    float* pointFloat = &varFloat;
    double* pointDouble = &varDouble;
    char* pointChar = &varChar;
    int* pointArray = arrInt;

    //input variabili
    printf("Inserire un carattere: ");
    scanf("%c",&varChar);     
    
    printf("Inserire un intero: ");
    scanf("%d", &varInt);

    printf("Inserire un float: ");
    scanf("%f", &varFloat);

    printf("Inserire un double: ");
    scanf("%lf", &varDouble);

    printf("\nVisualizzazione varibili in modo diretto: \n");
    //visualizzazione varibili in modo diretto
    printf("\nNumero intero: %d", varInt);
    printf("\nNumero float: %.2f", varFloat);
    printf("\nNumero double: %.2lf", varDouble);
    printf("\nCarattere: %c", varChar);
    for(int i = 0; i < 5; i++)
    {
        printf("\nPosizione %d dell'array: %d", (i+1), arrInt[i]);
    }

    printf("\n\nVisualizzazione variabili tramite puntatore: \n");
    //visualizzazione variabili tramite puntatore
    printf("\nNumero intero: %d | Posizione in memoria : %p", *pointInt, pointInt);
    printf("\nNumero float: %.2f | Posizione in memoria : %p", *pointFloat, pointFloat);
    printf("\nNumero double: %.2lf | Posizione in memoria : %p", *pointDouble, pointDouble);
    printf("\nCarattere: %c | Posizione in memoria : %p", *pointChar, pointChar);
    printf("\nPosizione puntatore array : %p", pointArray);
    for(int i = 0; i < 5; i++)
    {
        printf("\nPosizione %d dell'array: %d", (i+1), pointArray[i]);
    }

    printf("\n\n\n\nCambio variabili con char = a, int = 5, float = 10.10, double 20.20\n\n\n\n");
    varChar = 'a';
    varInt = 5;
    varFloat = 10.10;
    varDouble = 20.20;

    printf("\nVisualizzazione varibili in modo diretto: \n");
    //visualizzazione varibili in modo diretto
    printf("\nNumero intero: %d", varInt);
    printf("\nNumero float: %.2f", varFloat);
    printf("\nNumero double: %.2lf", varDouble);
    printf("\nCarattere: %c", varChar);
    for(int i = 0; i < 5; i++)
    {
        printf("\nPosizione %d dell'array: %d", (i+1), arrInt[i]);
    }

    printf("\n\nVisualizzazione variabili tramite puntatore: \n");
    //visualizzazione variabili tramite puntatore
    printf("\nNumero intero: %d | Posizione in memoria : %p", *pointInt, pointInt);
    printf("\nNumero float: %.2f | Posizione in memoria : %p", *pointFloat, pointFloat);
    printf("\nNumero double: %.2lf | Posizione in memoria : %p", *pointDouble, pointDouble);
    printf("\nCarattere: %c | Posizione in memoria : %p", *pointChar, pointChar);
    printf("\nPosizione puntatore array : %p", pointArray);
    for(int i = 0; i < 5; i++)
    {
        printf("\nPosizione %d dell'array: %d", (i+1), pointArray[i]);
    }

    system( "PAUSE" );
    return 0;
}
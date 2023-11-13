#include <stdio.h>
#include <stdlib.h>

// Constant declaration - necessary to conversion
#define FATTORE_CONVERSIONE 235.214f

#define CLEAR_SCREEN_LINUX system("clear") // Clear previous messages in the terminal console (linux terminal)
#define CLEAR_SCREEN_WIN system("cls") // Clear previous messages in the terminal console (windows terminal)

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

int main()
{
    // Using a proper terminal cleaning command,
    // based on the Operating System the program is running on
    if (CLEAR_SCREEN_LINUX == 1)
        CLEAR_SCREEN_WIN;
    else
        CLEAR_SCREEN_LINUX;

    float migliaPercorse, galloniConsumati, migliaPerGallone, litriSuKM;

    // Asking the user to type the miles travelled, then storing the value in the
    // specific variable
    printf("Insert miles travelled: ");
    scanf("%f", &migliaPercorse);

    // Doing the same for the gallons consumed
    printf("Insert gallons consumed: ");
    scanf("%f", &galloniConsumati);

    // Calculating the miles per gallons
    migliaPerGallone = migliaPercorse / galloniConsumati;

    // Displaying the result with a 2-digit approx.
    printf("Miles per gallon calculated: %.2f\n", migliaPerGallone);

    // Converting MPG to the L/100 kilometers
    litriSuKM = FATTORE_CONVERSIONE / migliaPerGallone;
    
    // Displaying the result with a 3-digit approx.
    printf("Litres per 100 KM (european formatting): %.3f\n", litriSuKM);

    return 0;
}
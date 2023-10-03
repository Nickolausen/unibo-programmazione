#include <stdio.h>
// Constant declaration - necessary to conversions
#define CONV_G_IN_L 3.78541
#define CONV_M_IN_KM 1.60934

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

int main()
{
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

    // Converting miles per gallons to the litres per 100 kilometers
    litriSuKM = (galloniConsumati * CONV_G_IN_L) / (migliaPercorse * CONV_M_IN_KM * 100);
    
    // Displaying the result with a 3-digit approx.
    printf("Litres/(KM * 100) (european formatting): %.3f\n", litriSuKM);

    exit(0);
    return 0;
}
#include <stdio.h>
// Constant declaration - necessary to conversions
#define CONV_G_IN_L 3.78541
#define CONV_MIN_KIM 1.60934

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

int main()
{
    float migliaPercorse, galloniConsumati, galloniPerMiglia, kmSuLitro;

    // Asking the user to type the miles travelled, then storing the value in the
    // specific variable
    printf("Insert miles travelled: ");
    scanf("%f", &migliaPercorse);

    // Doing the same for the gallons consumed
    printf("Insert gallons consumed: ");
    scanf("%f", &galloniConsumati);

    // Calculating the gallons consumed per miles
    galloniPerMiglia = galloniConsumati / migliaPercorse;

    // Displaying the result with a 2-digit approx.
    printf("Gallon per miles calculated: %.2f\n", galloniPerMiglia);

    // Converting gallons per miles to the kilometers kilometers per litre
    kmSuLitro = (galloniConsumati * CONV_G_IN_L) / (migliaPercorse * CONV_MIN_KIM);
    
    // Displaying the result with a 3-digit approx.
    printf("KM/Litres (european formatting): %.3f\n", kmSuLitro);

    return 0;
}
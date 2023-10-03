#include <stdio.h>
#include <stdlib.h> // Library needed to use random generator
#include <time.h> // Library needed to access time functions

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
    // Set random generator with current time as seed, 
    // so it generates a different set of number each run
    srand(time(0));

    // Using a proper terminal cleaning command,
    // based on the Operating System the program is running on
    if (CLEAR_SCREEN_LINUX == 1)
        CLEAR_SCREEN_WIN;
    else
        CLEAR_SCREEN_LINUX;

    // Asking the user to input the minimum number CPU can generate,
    // ensuring it is not less than zero
    int lowerBound;
    do
    {
        printf("Insert lower bound: ");
        fflush(stdin);
        scanf("%d", &lowerBound);
    } while (lowerBound <= 0);
    
    // Asking the user to input the maximum number CPU can generate,
    // ensuring it is not less than the minimum number
    int upperBound;
    do
    {
        printf("Insert upper bound: ");
        fflush(stdin);
        scanf("%d", &upperBound);
    } while (upperBound < lowerBound);

    // Asking the user to input the number CPU has to guess,
    // ensuring it is included in the range min <= number <= max
    int numberToGuess;
    do
    {
        printf("Insert the number CPU has to guess [INPUT has to be between %d and %d]: ", lowerBound, upperBound);
        scanf("%d", &numberToGuess);
        fflush(stdin);

        if (numberToGuess < lowerBound || numberToGuess > upperBound)
            printf("Input not between %d and %d!\n", lowerBound, upperBound);

    } while (numberToGuess < lowerBound || numberToGuess > upperBound);

    // Generating the first CPU guess, included in min <= CPUGuess <= max
    int CPUGuess = rand() % (upperBound - lowerBound + 1) + lowerBound;
    int nrAttempts = 1;

    while (CPUGuess != numberToGuess) 
    {
        char userTip = '!';

        // Using a proper terminal cleaning command,
        // based on the Operating System the program is running on
        if (CLEAR_SCREEN_LINUX == 1)
            CLEAR_SCREEN_WIN;
        else
            CLEAR_SCREEN_LINUX;

        printf("Attempt #%d\n", nrAttempts);
        printf("CPU generated number: %d! {Number to guess: %d}\n", CPUGuess, numberToGuess);
        do
        {
            fflush(stdin);
            puts("\n- Tell it if its guess is greater (>) or smaller (<) than the number to be guessed...");
            scanf("%c", &userTip);

            // Displaying an error message if the user typed an unexpected character
            if ((userTip != '>') && (userTip != '<')) 
            {
                printf("\nPlease type '<' or '>' to continue...");
            }
            
        } while ((userTip != '>') && (userTip != '<'));
        
        // Changing the range boundaries based on the user suggestion
        if (userTip == '>') 
            lowerBound = CPUGuess + 1;
        else
            upperBound = CPUGuess - 1;

        // Generating another guess within the new range
        CPUGuess = rand() % (upperBound - lowerBound + 1) + lowerBound;

        nrAttempts++;
    }

    printf("CPU has won the game in just %d attempts!", nrAttempts);

    exit(0);
    return 0;
}
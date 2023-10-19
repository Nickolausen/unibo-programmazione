#include <stdio.h>
#include <stdlib.h> // Library needed to use random generator
#include <time.h> // Library needed to access time functions
#include <stdbool.h>

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
    // Set random generator with current time as seed, 
    // so it generates a different set of number each run
    srand(time(0));

    CLEAR_CONSOLE;

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

    int nrAttempts = 1;

    bool numberGuessed = false;
    while (!numberGuessed) 
    {
        char userTip = '!';
        
        // Generating the CPU guess, included in min <= CPUGuess <= max
        int CPUGuess = rand() % (upperBound - lowerBound + 1) + lowerBound;

        CLEAR_CONSOLE;

        printf("Attempt #%d\n", nrAttempts);
        printf("CPU generated number: %d!\n", CPUGuess);
        do
        {
            fflush(stdin);
            puts("\n- Tell it if its guess is greater than (>), smaller than (<) or equal to (=) the number to be guessed...");
            scanf("%c", &userTip);

            // Displaying an error message if the user typed an unexpected character
            if ((userTip != '>') && (userTip != '<') && (userTip != '=')) 
            {
                printf("\nPlease type '<' - '>' - '=' to continue...");
            }
            
        } while ((userTip != '>') && (userTip != '<') && (userTip != '='));
        
        switch (userTip)
        {
            case '>':
                lowerBound = CPUGuess + 1;
                nrAttempts++;
            break;
        
            case '<':
                upperBound = CPUGuess - 1;
                nrAttempts++;
            break;

            case '=':
                numberGuessed = true;
            break;

        }
    }

    printf("CPU has won the game in just %d attempts!", nrAttempts);

    exit(0);
    return 0;
}
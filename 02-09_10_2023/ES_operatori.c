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
    // OPERATORI ARITMETICI - ASSEGNAZIONE
    int variabile = 10;
    printf("ASSEGNAZIONE (variabile = %d):\n", variabile);
    
    // PRE-INCREMENTO
    printf("Pre-incremento (++variabile): %d\n", ++variabile);

    // POST-INCREMENTO
    printf("Pre-incremento (variabile++): %d\n", variabile++);

    // SOMMA
    variabile = 5 + 3;
    printf("SOMMA (variabile = 5 + 3): %d\n", variabile);

    // SOMMA COMPATTA
    variabile += 7;
    printf("SOMMA COMPATTA (variabile += 7): %d\n", variabile);

    // DIFFERENZA
    variabile = 5 - 3;
    printf("DIFFERENZA (variabile = 5 - 3): %d\n", variabile);

    // DIFFERENZA COMPATTA
    variabile -= 7;
    printf("DIFFERENZA COMPATTA (variabile -= 7): %d\n", variabile);

    // MOLTIPLICAZIONE
    variabile = 5 * 3;
    printf("MOLTIPLICAZIONE (variabile = 5 * 3): %d\n", variabile);

    // MOLTIPLICAZIONE COMPATTA
    variabile *= 7;
    printf("MOLTIPLICAZIONE COMPATTA (variabile *= 7): %d\n", variabile);

    // DIVISIONE
    variabile = 50 / 2;
    printf("DIVISIONE (variabile = 50 / 2): %d\n", variabile);

    // DIVISIONE COMPATTA
    variabile /= 5;
    printf("DIVISIONE COMPATTA (variabile /= 5): %d\n", variabile);

    // MODULO
    variabile = 10 % 7;
    printf("MODULO (variabile = 10 %% 7): %d\n", variabile);

    // MODULO COMPATTO
    variabile %= 0;
    printf("MODULO COMPATTO (variabile %%= 0): %d\n", variabile);

    // INVERTI SEGNO
    int other = -variabile;
    printf("INVERTI SEGNO (other = -variabile): %d\n", other);

    
    return 0;
}
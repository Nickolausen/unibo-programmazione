// Librerie che mi servono
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

// Definisco un funzione per trovare la lunghezza di un array
#define LENGHT(a) (int)(sizeof(a) / sizeof(a[0]))

/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

// Metodo per rendere più pulito il codice e cambiare la stringa iniziale in modo
// tale da rimpiazzare l'occorrenza con un * poi spostare gli altri caratteri
void RimpiazzaOccorrenza(char *pointer, int inizio, int fine)
{
    *(pointer + inizio) = '*';
    for (int i = 0; i < fine - 1; i++)
    {
        for (int j = inizio + 1; j < 50 - 1; j++)
        {
            *(pointer + j) = *(pointer + j + 1);
        }
    }
}

// Metodo per controllare se è effettivamente un'occorrenza costruendo una sottostringa
// per poi ritornare lo string n compare  
bool IsAnOccurence(char stringa1[], char stringa2[], int pos, int len)
{
    int i = 0;
    char substring[50];

    while (i < len)
    {
        substring[i] = stringa1[pos + i - 1];
        i++;
    }
    return strncmp(substring, stringa2, len);
}

int main()
{
    // Prendo in input la stringa iniziale in cui cercherò le occorrenze
    char inputIniziale[50];
    int lunghezzaInputIniziale = 0;
    char lettura = ' ';
    printf("Scrivi la prima stringa: ");
    while ((lettura = getchar()) != '\n' && lunghezzaInputIniziale < LENGHT(inputIniziale))
    {
        inputIniziale[lunghezzaInputIniziale] = lettura;

        // Mi segno la lunghezza così da utilizzarla per operazioni successive
        lunghezzaInputIniziale++;
    }

    // Prendo in input l'occorrenza che cercherò nell'altra stringa di input
    char occorrenza[lunghezzaInputIniziale];
    int lunghezzaOccorrenza = 0;
    lettura = ' ';
    printf("Scrivi la seconda stringa che deve essere contenuta nella prima: ");
    while ((lettura = getchar()) != '\n' && lunghezzaOccorrenza < LENGHT(occorrenza))
    {
        occorrenza[lunghezzaOccorrenza] = lettura;

        // Mi segno la lunghezza così da utilizzarla per operazioni successive
        lunghezzaOccorrenza++;
    }

    // Utilizzo un booleano per sapere se effetivamente dentro la stringa di input iniziale
    // c'è un'occorrenza 
    bool occorrenzaTrovata = false;

    // Faccio un ciclo per scorrere tutta la stringa di input iniziale per controllare
    // se ci sono delle occorrenze
    for (int i = 0; i < lunghezzaInputIniziale; i++)
    {
        // Se i caratteri corrispondono faccio controllare al metodo se è un'occorrenza
        if (inputIniziale[i] == occorrenza[0])
        {
            occorrenzaTrovata = IsAnOccurence(inputIniziale, occorrenza, i, lunghezzaOccorrenza);
        }

        // Se ha trovato l'occorrenza faccio sostituire al metodo l'occorrenza con *
        if (occorrenzaTrovata)
        {
            RimpiazzaOccorrenza(inputIniziale, i, lunghezzaOccorrenza);

            // Cambio la lunghezza perchè potrei togliere dei caratteri in più rispetto a
            // quelli che inserisco, in più quest'operazione serve per l'output
            lunghezzaInputIniziale -= (lunghezzaOccorrenza - 1);
        }

        // Resetto il booleano di controllo
        occorrenzaTrovata = false;
    }

    // Mando in output la stringa con le occorrenza sostituite da * un carattere alla volta
    printf("\nLa tua stringa finale: ");
    for (int i = 0; i < lunghezzaInputIniziale; i++)
    {
        printf("%c", inputIniziale[i]);
    }
    printf("\n");

    return 0;
}
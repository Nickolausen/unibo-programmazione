/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROW 10000
#define MAX_LEN 200

typedef enum {
    nessuno,
    qualcuno,
    pieno
} crowd_status;

typedef enum {
    cheap,
    mid,
    expensive
} price_tag;

typedef enum 
{
    italiano,
    francese,
    fastfood,
    thai
} restaurant_type;

typedef enum 
{
    under10,
    over10,
    over30,
    over60
} estimated_waiting; 
typedef struct 
{
    bool hasAlternative;
    bool hasBar;
    bool onFriOrSat;
    bool isHungry;
    crowd_status status;
    price_tag expensiveness;
    bool isRaining;
    bool hasReservation;
    restaurant_type type;
    estimated_waiting waiting;
} Hypothesis;

bool Aspettiamo(){
    bool risultato = false;

    return risultato;
}

char **LetturaFile(FILE *file)
{
    char fileText[MAX_ROW][MAX_LEN] = {0};
    char line[MAX_ROW][MAX_LEN];
    long long col = 0;

    // Leggo il file CSV riga per riga
    int i = 0;
    while (fgets(line[col], MAX_LEN, file))
    {
        char *token;
        int j = 0;
        token = strtok(line[col], ",");
        while (token != NULL)
        {
            fileText[i][j] = token;
            
            // Avanzo di colonna
            token = strtok(NULL, ",");

            // Cambio la colonna 
            j++;
        }
        i++;
    }

    return file;
}

char *Training(FILE *file)
{
    //Iniziallizzazione ipotesi vuota
    char h[] = {'ϕ','ϕ','ϕ','ϕ','ϕ','ϕ','ϕ','ϕ','ϕ'};
    
    char line[MAX_ROW][MAX_LEN];
    long long col = 0;

    // Leggo il file CSV riga per riga
    while (fgets(line[col], MAX_LEN, file))
    {
        char *token;
        int i = 0;
        token = strtok(line[col], ",");

        while (token != NULL)
        {
            //Controllo l'ipotesi solo se il "risultato" è vero 
            if(i == 0 && token == "vero")
            {
                if(h[i] == 'ϕ')
                    h[i] = token;
                else
                {
                    if(h[i] != token)
                         h[i] = '?';
                }

            }
            else{
                break;
            }
        // Avanzo di colonna
        token = strtok(NULL, ",");

        // Cambio la colonna
        i++;
        }
    }
    return h;
}

int main() 
{
    //Inizializzazione Input file
    FILE* pFile = NULL;

    //Controllo input file esistente
    if((pFile =fopen("dataset-finds.csv", "rwa"))== NULL){
        printf("ERRORE LETTURA FILE");
        return 1;
    }
    
    char model[] = Training(pFile);


    //Chiusura file
    fclose(pFile);
}
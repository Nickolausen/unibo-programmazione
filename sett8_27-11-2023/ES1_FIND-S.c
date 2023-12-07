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



int main() 
{
    FILE* pFile = fopen("dataset-finds.csv", "rwa");
}
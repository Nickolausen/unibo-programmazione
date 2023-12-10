/*
    Group components:
    > Nicholas Magi <nicholas.magi@studio.unibo.it>;
    > Tommaso Maestri <tommaso.maestri@studio.unibo.it>;
    > Leonardo Perretta <leonardo.perretta2@studio.unibo.it>;
    > Riccardo Ventrucci <riccardo.ventrucci@studio.unibo.it>;
*/

//Valore,Alternativa,Bar,Giorno,Fame,Affollato,Prezzo,Pioggia,Prenotazione,Tipo,Attesa stimata
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROW 6
#define MAX_LEN 100

typedef enum {
    nessuno = 0,
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
    italiano = 0,
    francese,
    fastfood,
    thai
} restaurant_type;

typedef enum 
{
    under10 = 0,
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

//Uso questo metodo per convertire gli enum in stringhe
char **EnumToString(Hypothesis ipo)
{
    char **str = (char **)malloc(4 * sizeof(char *));
    
    str[0] = NULL;
    str[1] = NULL;
    str[2] = NULL;
    str[3] = NULL;

    switch(ipo.status)
    {
        case nessuno:
            str[0]= "nessuno";
            break;
        case qualcuno:
            str[0]= "qualcuno";
            break;
        case pieno:
            str[0]= "pieno";
            break;
    }
    switch(ipo.expensiveness)
    {
        case cheap:
            str[1]= "$";
            break;
        case mid:
            str[1]= "$$";
            break;
        case expensive:
            str[1]= "$$$";
            break;
    }
    switch(ipo.type)
    {
        case italiano:
            str[2]= "italiano";
            break;
        case thai:
            str[2]= "thai";
            break;
        case fastfood:
            str[2]= "fast-food";
            break;
        case francese:
            str[2]= "francese";
            break;
    }
    switch(ipo.waiting)
    {
        case under10:
            str[3]= "<10";
            break;
        case over10:
            str[3]= "10-29";
            break;
        case over30:
            str[3]= "30-60";
            break;
        case over60:
            str[3] = ">60";
            break;
    }
    return str;
}

//Stampa struct ipotesi
void StampaStruct(Hypothesis ipo)
{
    char **str = EnumToString(ipo);
    char *valore[10] = {"Alternativa","Bar","Giorno","Fame","Affollato","Prezzo","Pioggia","Prenotazione","Tipo","Attesa stimata"};
    printf("%s : %s\n", valore[0], ipo.hasAlternative ? "true" : "false");
    printf("%s : %s\n", valore[1], ipo.hasBar ? "true" : "false");
    printf("%s : %s\n", valore[2], ipo.onFriOrSat ? "true" : "false");
    printf("%s : %s\n", valore[3], ipo.isHungry ? "true" : "false");
    printf("%s : %s\n", valore[4], str[0]);
    printf("%s : %s\n", valore[5], str[1]);
    printf("%s : %s\n", valore[6], ipo.isRaining ? "true" : "false");
    printf("%s : %s\n", valore[7], ipo.hasReservation ? "true" : "false");
    printf("%s : %s\n", valore[8], str[2]);
    printf("%s : %s\n", valore[9], str[3]);
}

//Stampa array dell'ipotesi
void StampaArray(char **point, int col) {
    char *valore[10] = {"Alternativa","Bar","Giorno","Fame","Affollato","Prezzo","Pioggia","Prenotazione","Tipo","Attesa stimata"};
    for (int i = 0; i < col; i++) {
        printf("\n %s : %s", valore[i], point[i]);
    }
}

char** Find_S(char*** dataset, int righe, int col)
{
    //inizializzo l'ipotesi allocando la memoria
    char** h = (char**)malloc((col - 1) * sizeof(char*));
    //metto in ogni campo uno spazio vuoto
    for(int i = 0; i < col - 1; i++)
    {
        //allocazione memoria per ogni stringa
        h[i] = (char*)malloc(2 * sizeof(char));
        strcpy(h[i], " ");
    }

    //Alternativa,Bar,Giorno,Fame,Affollato,Prezzo,Pioggia,Prenotazione,Tipo,Attesa stimata, VALORE IPOTESI
    for(int i = 0; i < righe; i++)
    {
        //se la stringa del file csv inizia per vero, vuol dire che quella riga è da prendere come ipotesi buona
        char compare[10];
        strcpy(compare, dataset[i][10]);
        char *strtk;
        strtk = strtok(compare, "\n");
        if(strtk[0] == 'v')
        {   
            //scorro tutti i valori di quella riga
            for(int j = 0; j < col-1; j++)
            {
                //se l'ipotesi è vuota in quella colonna ci aggiungo il valore
                if(strcmp(h[j], " ") == 0)
                {
                    strcpy(h[j], dataset[i][j]);
                }
                else
                {
                    //se la colonna dell'ipotesi è già piena ci metto un ?
                    if(strcmp(h[j], dataset[i][j]) != 0)
                    {
                        strcpy(h[j], "?");
                    }
                }
            }
        }
    }
    return h;
} 

char ***LetturaFile(FILE *file) {
    //allocazione memoria matrice di stringhe 
    //{
    //  {{'a','b','c',','} {'d','e','f',','}},
    //  {}
    //}
    char ***data = (char ***)malloc(MAX_ROW * sizeof(char **));
    for (int i = 0; i < MAX_ROW; i++) {
        data[i] = (char **)malloc(MAX_LEN * sizeof(char *));
        for (int j = 0; j < MAX_LEN; j++) {
            data[i][j] = (char *)malloc(MAX_LEN * sizeof(char));
        }
    }

    char line[MAX_LEN];
    int row = 0;
    //finchè c'è un'altra riga continuo a leggere il file csv
    while (fgets(line, MAX_LEN, file)) {
        char *token;
        int col = 0;
        //prendo come stringa tutti i char prima della ,
        token = strtok(line, ",");
        //se il token non è NULL, copio nel dataset il valore
        while (token != NULL) {
            strcpy(data[row][col], token);
            token = strtok(NULL, ",");
            col++;
        }
        row++;
    }
    return data;
}

Hypothesis ConvertiStruct(char **ip, int col)
{
    //Alternativa,Bar,Giorno,Fame,Affollato,Prezzo,Pioggia,Prenotazione,Tipo,Attesa stimata
    Hypothesis ipotesi;
    crowd_status st;
    price_tag ex;
    restaurant_type res;
    estimated_waiting est;
    ipotesi.hasAlternative = ip[0];
    ipotesi.hasBar = ip[1];
    ipotesi.onFriOrSat = ip[2];
    ipotesi.isHungry = ip[3];
    if(strcmp(ip[4], "nessuno"))
        st = nessuno;
    else if(strcmp(ip[4], "qualcuno"))
        st = qualcuno;
    else
        st = pieno;
    ipotesi.status = st;
    if(strcmp(ip[5], "$"))
        ex = cheap;
    else if(strcmp(ip[5], "$$"))
        ex = mid;
    else
        ex = expensive;
    ipotesi.expensiveness = ex;
    ipotesi.isRaining = ip[6];
    ipotesi.hasReservation = ip[7];
    if(strcmp(ip[8], "francese"))
        res = francese;
    else if(strcmp(ip[8], "thai"))
        res = thai;
    else if(strcmp(ip[8], "italiano"))
        res = italiano;
    else
        res = fastfood;
    ipotesi.type = res; 
    if(strcmp(ip[9], ">60"))
        est = over60;
    else if(strcmp(ip[9], "<10"))
        est = under10;
    else if(strcmp(ip[9], "10-29"))
        est = over10;
    else
        est = over30;
    ipotesi.waiting = est;
    return ipotesi;
}

//Manca implementazione con struct Hypotesis perchè non considera il valore ?
bool Aspettiamo(char** ipo, char** modello)
{
    //considero per buona l'opzione di aspettare se il risultato di count è >= 4
    // valore uguale per ipotesi e modello = 1
    // valore ? per modello = 0,25
    // valore diverso = 0
    bool aspetta = false;
    float count = 0;

    for(int i = 0; i < 10; i++)
    {
        //modello[i] == "?"
        //ipo[i] == modello[i]
        char str1[10];
        char str2[10];
        strncpy(str1, ipo[i], 5);
        strncpy(str2, modello[i], 5);
        if(strncmp(str1, str2, 5) == 0)
            count += 1;
        else if(strncmp(str2, "?", 1) == 0)
            count += 0,25;
    }

    if(count >= 4)
        aspetta = true;
    else
        aspetta = false;
    return aspetta;
}

int main() 
{
    //Inizializzazione Input file
    FILE* pFile = NULL;

    //Controllo input file esistente
    if((pFile =fopen("dataset-finds.csv", "r"))== NULL){
        printf("ERRORE LETTURA FILE");
        return 1;
    }
    
    //Inizializzazione dataset vuoto
    char*** dataset = LetturaFile(pFile);
    //Calcolo modello con algoritmo Find-S
    char** modello = Find_S(dataset, MAX_ROW, MAX_LEN);
    printf("Ipotesi calcolata dall'Algoritmo Find-S : \n");
    StampaArray(modello, 10);
    printf("\n");
    //Hypothesis ip = ConvertiStruct(ipotesi, 10);
    //StampaStruct(ip);
    //Chiusura file
    fclose(pFile);

    bool ok =false;
    bool oks[10]= {0, 0, 0, 0, 0, 0 ,0 ,0, 0, 0};
    char *valori[10] = {"Alternativa","Bar","Giorno","Fame","Affollato","Prezzo","Pioggia","Prenotazione","Tipo","Attesa stimata"};
    char **ipotesi = (char **)malloc(10 * sizeof(char *));
    while(!ok)
    {
        printf("Inserire i valori da testare: \n");
        for(int i = 0; i < 10; i++)
        {
            while(!oks[i])
            {
                printf("Inserire il valore di %s: ", valori[i]);
                char str[25];
                scanf("%s", str);
                ipotesi[i] = str;
                printf("\n");
                //Manca implementazione controllo input
                oks[i] = true;
            }
        }
        //Manca implementazione controllo input
        ok = true;
    }

    //ipotesi per debug
    //char *ipotesi[] = {"vero", "vero", "vero", "vero", "pieno", "$$", "falso", "vero", "italiano", ">60"};

    printf("Il modello prevede che per l'ipotesi data bisognerebbe: %s" , Aspettiamo(ipotesi, modello) ? "aspettare" : "NON aspettare");

    system("pause");
    return 0;
}
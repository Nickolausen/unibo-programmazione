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

#define FILE_ROWS 6
#define MAX_LEN 100

#pragma ENUMS
typedef enum {
    nessuno = 0,
    qualcuno,
    pieno,
    unknownStatus
} crowd_status;

typedef enum {
    cheap,
    mid,
    expensive,
    unknownPrice
} price_tag;

typedef enum 
{
    italiano = 0,
    francese,
    fastfood,
    thai,
    unknownRestaurant
} restaurant_type;

typedef enum 
{
    under10 = 0,
    over10,
    over30,
    over60,
    unknownWaiting
} estimated_waiting; 

typedef struct 
{
    char hasAlternative;
    char hasBar;
    char onFriOrSat;
    char isHungry;
    crowd_status status;
    price_tag expensiveness;
    char isRaining;
    char hasReservation;
    restaurant_type type;
    estimated_waiting waiting;
    bool value;
} Hypothesis;
#pragma endregion
//Metodo per conversione vero falso ?
char StringToChar(char *str)
{
    int comp1 = strcmp(str, "vero");
    int comp2 = strcmp(str, "falso");
    int comp3 = strcmp(str, "?");
    if(comp1 == 0)
        return 'v';
    else if(comp2 == 0)
        return 'f';
    else
        return '?';

}
//Metodo per conversione vero falso ?
char *CharToString(char ipo)
{
    switch (ipo)
    {
        case 'v':
            return "vero";
        case 'f':
            return "falso";
        case '?':
            return "?";
        default:
            return "?";
    }
}
//Uso questo metodo per convertire gli enum in stringhe
char **EnumToString(Hypothesis ipo)
{
    char **str = (char **)malloc(10 * sizeof(char *));
    
    str[0] = NULL;
    str[1] = NULL;
    str[2] = NULL;
    str[3] = NULL;
    str[4] = NULL;
    str[5] = NULL;
    str[6] = NULL;
    str[7] = NULL;
    str[8] = NULL;
    str[9] = NULL;

    str[0] = CharToString(ipo.hasAlternative);
    str[1] = CharToString(ipo.hasBar);
    str[2] = CharToString(ipo.onFriOrSat);
    str[3] = CharToString(ipo.isHungry);
    switch(ipo.status)
    {
        case nessuno:
            str[4]= "nessuno";
            break;
        case qualcuno:
            str[4]= "qualcuno";
            break;
        case pieno:
            str[4]= "pieno";
            break;
        case unknownStatus:
            str[4] = "?";
            break;
    }
    switch(ipo.expensiveness)
    {
        case cheap:
            str[5]= "$";
            break;
        case mid:
            str[5]= "$$";
            break;
        case expensive:
            str[5]= "$$$";
            break;
        case unknownPrice:
            str[5] = "?";
            break;
    }
    str[6] = CharToString(ipo.isRaining);
    str[7] = CharToString(ipo.hasReservation);
    switch(ipo.type)
    {
        case italiano:
            str[8]= "italiano";
            break;
        case thai:
            str[8]= "thai";
            break;
        case fastfood:
            str[8]= "fast-food";
            break;
        case francese:
            str[8]= "francese";
            break;
        case unknownRestaurant:
            str[8] = "?";
            break;
    }
    switch(ipo.waiting)
    {
        case under10:
            str[9]= "<10";
            break;
        case over10:
            str[9]= "10-29";
            break;
        case over30:
            str[9]= "30-60";
            break;
        case over60:
            str[9] = ">60";
            break;
        case unknownWaiting:
            str[9] = "?";
            break;
    }
    return str;
}
//Stampa struct ipotesi
void StampaStruct(Hypothesis ipo)
{
    char **str;
    str = EnumToString(ipo);
    char *valore[10] = {"Alternativa","Bar","Giorno","Fame","Affollato","Prezzo","Pioggia","Prenotazione","Tipo","Attesa stimata"};
    printf("%s : %s\n", valore[0], str[0]);
    printf("%s : %s\n", valore[1], str[1]);
    printf("%s : %s\n", valore[2], str[2]);
    printf("%s : %s\n", valore[3], str[3]);
    printf("%s : %s\n", valore[4], str[4]);
    printf("%s : %s\n", valore[5], str[5]);
    printf("%s : %s\n", valore[6], str[6]);
    printf("%s : %s\n", valore[7], str[7]);
    printf("%s : %s\n", valore[8], str[8]);
    printf("%s : %s\n", valore[9], str[9]);
}
//Stampa array dell'ipotesi
void StampaArray(char **point, int col) {
    char *valoriStruct[10] = {"Alternativa","Bar","Giorno","Fame","Affollato","Prezzo","Pioggia","Prenotazione","Tipo","Attesa stimata"};
    for (int i = 0; i < col; i++) {
        printf("\n %s : %s", valoriStruct[i], point[i]);
    }
}
//Metodo per stampare il dataset
void StampaDataSet(Hypothesis *dataset, int addedRows, int righe)
{
    printf("DATASET: \n");
    char *valoriStruct[11] = {"Alternativa","Bar","Giorno","Fame","Affollato","Prezzo","Pioggia","Prenotazione","Tipo","Attesa stimata","Valore"};
    printf("\n");
    for(int i = 0; i < 11; i++)
        printf("%s\t", valoriStruct[i]);
    printf("\n");
    for(int i = 0; i < righe + addedRows; i++)
    {
        char **strings;
        strings = EnumToString(dataset[i]); 
        for(int j = 0; j < 10; j++)
            printf("%s\t  ", strings[j]);
        printf("%d\t", dataset[i].value);
        printf("\n");
    }
    printf("\n");
}
//Metodo algoritmo find-S con stringhe
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
//Metodo algoritmo find-S con Struct
Hypothesis Find_S_Struct(Hypothesis *dataset, int righe, int col)
{
    //inizializzo l'ipotesi 
    Hypothesis h;

    bool full = false;
    //Alternativa,Bar,Giorno,Fame,Affollato,Prezzo,Pioggia,Prenotazione,Tipo,Attesa stimata, VALORE IPOTESI
    for(int i = 0; i < righe; i++)
    {
        //se la stringa del file csv inizia per vero, vuol dire che quella riga è da prendere come ipotesi buona
        if(dataset[i].value)
        {   
            //Alternativa,Bar,Giorno,Fame,Affollato,Prezzo,Pioggia,Prenotazione,Tipo,Attesa stimata,Valore
            if(!full)
            {
                h.hasAlternative = dataset[i].hasAlternative;
            }
            else
            {
                if(h.hasAlternative != dataset[i].hasAlternative)
                    h.hasAlternative = '?';
            }
            if(!full)
            {
                h.hasBar = dataset[i].hasBar;
            }
            else
            {
                if(h.hasBar != dataset[i].hasBar)
                    h.hasBar = '?';
            }
            if(!full)
            {
                h.onFriOrSat = dataset[i].onFriOrSat;
            }
            else
            {
                if(h.onFriOrSat != dataset[i].onFriOrSat)
                    h.onFriOrSat = '?';
            }
            if(!full)
            {
                h.isHungry = dataset[i].isHungry;
            }
            else
            {
                if(h.isHungry != dataset[i].isHungry)
                    h.isHungry = '?';
            }
            if(!full)
            {
                h.status = dataset[i].status;
            }
            else
            {
                if(h.status != dataset[i].status)
                    h.status = unknownStatus;
            }
            if(!full)
            {
                h.expensiveness = dataset[i].expensiveness;
            }
            else
            {
                if(h.expensiveness != dataset[i].expensiveness)
                    h.expensiveness = unknownPrice;
            }
            if(!full)
            {
                h.isRaining = dataset[i].isRaining;
            }
            else
            {
                if(h.isRaining != dataset[i].isRaining)
                    h.isRaining = '?';
            }
            if(!full)
            {
                h.hasReservation = dataset[i].hasReservation;
            }
            else
            {
                if(h.hasReservation != dataset[i].hasReservation)
                    h.hasReservation = '?';
            }
            if(!full)
            {
                h.type = dataset[i].type;
            }
            else
            {
                if(h.type != dataset[i].type)
                    h.type = unknownRestaurant;
            }
            if(!full)
            {
                h.waiting = dataset[i].waiting;
            }
            else
            {
                if(h.waiting != dataset[i].waiting)
                    h.waiting = unknownWaiting;
            }
            full = true;
        }
    }
    return h;
}
//Aggiunge una riga al dataset
void AggiungiADataSet(Hypothesis *dataset, Hypothesis ip, int count,int righe)
{   
    dataset[righe + count] = ip;
}
//Metodo di lettura file CSV
char ***LetturaFile(FILE *file, int fileRows, int maxLength) {
    //allocazione memoria matrice di stringhe 
    //{
    //  {{'a','b','c',','} {'d','e','f',','}},
    //  {}
    //}
    char ***data = (char ***)malloc(fileRows * sizeof(char **));
    for (int i = 0; i < fileRows; i++) {
        data[i] = (char **)malloc(maxLength * sizeof(char *));
        for (int j = 0; j < maxLength; j++) {
            data[i][j] = (char *)malloc(maxLength * sizeof(char));
        }
    }

    char line[MAX_LEN];
    int row = 0;
    //finchè c'è un'altra riga continuo a leggere il file csv
    while (fgets(line, maxLength, file)) {
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
//Conversione Ipotesi String in Struct
Hypothesis ConvertiStruct(char **ip, bool isDatasetRow, bool isAdded)
{
    //Alternativa,Bar,Giorno,Fame,Affollato,Prezzo,Pioggia,Prenotazione,Tipo,Attesa stimata
    Hypothesis ipotesi;
    crowd_status st;
    price_tag ex;
    restaurant_type res;
    estimated_waiting est;
    ipotesi.hasAlternative = StringToChar(ip[0]);
    ipotesi.hasBar = StringToChar(ip[1]);
    ipotesi.onFriOrSat = StringToChar(ip[2]);
    ipotesi.isHungry = StringToChar(ip[3]);
    if(strcmp(ip[4], "nessuno")== 0)
        st = nessuno;
    else if(strcmp(ip[4], "qualcuno") == 0)
        st = qualcuno;
    else if(strcmp(ip[4], "pieno") == 0)
        st = pieno;
    else
        st = unknownStatus;
    ipotesi.status = st;
    char *expens = ip[5];
    if(strcmp(ip[5], "$") == 0)
        ex = cheap;
    else if(strcmp(ip[5], "$$") == 0)
        ex = mid;
    else if(strcmp(ip[5], "$$$") == 0)
        ex = expensive;
    else 
        ex = unknownPrice;
    ipotesi.expensiveness = ex;
    ipotesi.isRaining = StringToChar(ip[6]);
    ipotesi.hasReservation = StringToChar(ip[7]);
    if(strcmp(ip[8], "francese") == 0)
        res = francese;
    else if(strcmp(ip[8], "thai") == 0)
        res = thai;
    else if(strcmp(ip[8], "italiano") == 0)
        res = italiano;
    else if(strcmp(ip[8], "fast-food") == 0)
        res = fastfood;
    else
        res = unknownRestaurant;
    ipotesi.type = res; 
    if(strcmp(ip[9], ">60") == 0)
        est = over60;
    else if(strcmp(ip[9], "<10") == 0)
        est = under10;
    else if(strcmp(ip[9], "10-29") == 0)
        est = over10;
    else if(strcmp(ip[9], "30-60") == 0)
        est = over30;
    else
        est = unknownWaiting;
    ipotesi.waiting = est;
    if(isDatasetRow)
    {
        int k = strncmp(ip[10], "v", 1);
        int k1 = strncmp(ip[10], "f", 1);
        if(k == 0)
            ipotesi.value = true;
        else if(k1 == 0)
            ipotesi.value = false;
    }

    if(isAdded)
    {
        ipotesi.value = true;
    }
    
    return ipotesi;
}
//Metodo Aspettiamo con stringhe
bool Aspettiamo(char** ipo, char** modello, float mult1, float mult2)
{
    //considero per buona l'opzione di aspettare se il risultato di count è >= 4
    // valore uguale per ipotesi e modello = 1
    // valore ? per modello = da input
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
            count += 1 * mult1;
        else if(strncmp(str2, "?", 1) == 0)
            count += mult2;
    }

    if(count >= 4)
        aspetta = true;
    else
        aspetta = false;
    return aspetta;
}
//Controllo Valori di input
bool ControlloInput(char* str, int i)
{
    int ok = 0;
    int ok2 = 0;
    int ok3 = 0;
    int ok4 = 0;
    if(i == 0 || i == 1 || i == 2 || i == 3 || i == 6 || i == 7)
    {
        ok = strcmp(str, "falso");
        ok2 = strcmp(str, "vero");
        if(ok == 0 || ok2 == 0)
            return true;
        else
            return false;
    }
    else if(i == 4)
    {
        ok = strcmp(str, "nessuno");
        ok2 = strcmp(str, "qualcuno");
        ok3 = strcmp(str, "pieno");
        if(ok == 0 || ok2 == 0 || ok3 == 0)
            return true;
        else
            return false;
    }
    else if(i == 5)
    {
        ok = strcmp(str, "$");
        ok2 = strcmp(str, "$$");
        ok3 = strcmp(str, "$$$");
        if(ok == 0 || ok2 == 0 || ok3 == 0)
            return true;
        else
            return false;
    }
    else if(i == 8)
    {
        ok = strcmp(str, "italiano");
        ok2 = strcmp(str, "thai");
        ok3 = strcmp(str, "francese");
        ok4 = strcmp(str, "fast-food");
        if(ok == 0 || ok2 == 0 || ok3 == 0 || ok4 == 0)
            return true;
        else
            return false;
    }
    else
    {
        ok = strcmp(str, ">60");
        ok2 = strcmp(str, "<10");
        ok3 = strcmp(str, "10-29");
        ok4 = strcmp(str, "30-60");
        if(ok == 0 || ok2 == 0 || ok3 == 0 || ok4 == 0)
            return true;
        else
            return false;
    }
}

int main() 
{
    //PER DEBUG
    // Hypothesis datasetText[] = {
    //     {'v', 'v', 'v', 'v', pieno, mid, 'f', 'v', italiano, over60, false},
    //     {'v', 'f', 'v', 'v', qualcuno, cheap, 'f', 'v', francese, over30, false},
    //     {'f', 'v', 'v', 'f', nessuno, expensive, 'v', 'f', fastfood, under10, true},
    //     {'v', 'v', 'f', 'f', qualcuno, cheap, 'f', 'f', thai, over10, false},
    //     {'f', 'f', 'f', 'v', pieno, expensive, 'v', 'v', italiano, over60, false},
    //     {'v', 'f', 'f', 'v', nessuno, mid, 'f', 'f', fastfood, under10, false}
    // };
    //------------------------------------------------------------------------------

    int addedRows = 0;
    int readRows = 0;

    bool okInputFile = false;
    //Inizializzazione Input file
    FILE* pFile = NULL;
    char fileOrText[2];
    printf("Caricare dataset da file o da testo? (0/1)");
    scanf(" %s", fileOrText);
    int fileOrTextcmp = strncmp(fileOrText, "1", 1);
    //Inizializzazione dataset vuoto
    char*** dataset;
    int righeInput = 0;
    //Input dataset da linea di comando
    if(fileOrTextcmp == 0)
    {
        //Righe in input per allocazione memoria
        printf("Quante righe vuoi inserire?:");
        scanf("%d", &righeInput);
        //Allocazione memoria dataset
        dataset = (char ***)malloc(righeInput * sizeof(char **));
        for (int i = 0; i < righeInput; i++)
        {
            dataset[i] = (char **)malloc(MAX_LEN * sizeof(char *));
            for (int j = 0; j < MAX_LEN; j++) 
            {
                dataset[i][j] = (char *)malloc(MAX_LEN * sizeof(char));
            }
        }
        printf("\n");
        int numeroRiga = 0;
        while(numeroRiga < righeInput)
        {
            //Variabili di input
            char inputAlternativa[5];
            char inputBar[5];
            char inputGiorno[5];
            char inputFame[5];
            char inputAffollato[10];
            char inputPrezzo[3];
            char inputPioggia[3];
            char inputPrenotazione[5];
            char inputTipo[15];
            char inputAttesa[6];
            char inputValore[5];

            //Input ipotesi
            printf("Alternativa: c e un ristorante nei paraggi (vero, falso)");
            scanf(" %s", inputAlternativa);
            printf("Bar: il ristorante ha un area bar per l attesa (vero, falso)");
            scanf(" %s", inputBar);
            printf("Giorno: giorno della settimana in cui si vuole andare al ristorante (vero se venerdi oppure sabato, falso diversamente)");
            scanf(" %s", inputGiorno);
            printf("Fame: siamo affamati (vero, falso)");
            scanf(" %s", inputFame);
            printf("Affollato: quante persone sono presenti nel ristorante (nessuno, qualcuno, pieno)");
            scanf(" %s", inputAffollato);
            printf("Prezzo: categoria di costo del ristorante ($, $$, $$$)");
            scanf(" %s", inputPrezzo);
            printf("Pioggia: fuori sta piovendo (vero, falso)");
            scanf(" %s", inputPioggia);
            printf("Prenotazione: abbiamo prenotato (vero, falso)");
            scanf(" %s", inputPrenotazione);
            printf("Tipo: tipo di ristorante (italiano, francese, fast-food, thai)");
            scanf(" %s", inputTipo);
            printf("Attesa stimata: stima del tempo di attesa (<10, 10-29, 30-60, >60)");
            scanf(" %s", inputAttesa);
            printf("Valore: questa ipotesi e considerata come buona? (vero, falso)");
            scanf(" %s", inputValore);

            dataset[numeroRiga][0] = inputAlternativa;
            dataset[numeroRiga][1] = inputBar;
            dataset[numeroRiga][2] = inputGiorno;
            dataset[numeroRiga][3] = inputFame;
            dataset[numeroRiga][4] = inputAffollato;
            dataset[numeroRiga][5] = inputPrezzo;
            dataset[numeroRiga][6] = inputPioggia;
            dataset[numeroRiga][7] = inputPrenotazione;
            dataset[numeroRiga][8] = inputTipo;
            dataset[numeroRiga][9] = inputAttesa;
            dataset[numeroRiga][10] = inputValore;

            numeroRiga++;
        }
    }
    else
    {
        //input dataset da file
        while(!okInputFile)
        {

            if((pFile = fopen("dataset-finds.csv", "r"))== NULL)
            {
                printf("ERRORE LETTURA FILE");
                return -1;
            }
            okInputFile = true;
            righeInput = 6;
        }
        //Inizializzazione dataset con file
        dataset = LetturaFile(pFile, righeInput, MAX_LEN);
    }
    
    //Creo una copia del dataset in un array della struct
    Hypothesis datasetStruct[50];
    for(int i = 0; i < righeInput; i++)
    {
        datasetStruct[i] = ConvertiStruct(dataset[i], true, false);
    }
    StampaDataSet(datasetStruct, addedRows, righeInput);
    //Calcolo modello con algoritmo Find-S
    char** modello = Find_S(dataset, righeInput, MAX_LEN);
    //Calcolo modello con Find-S e struct
    Hypothesis modelloStruct = Find_S_Struct(datasetStruct, righeInput, MAX_LEN);
    printf("Ipotesi calcolata dall'Algoritmo Find-S : \n");
    //StampaArray(modello, 10);
    //printf("\n");
    //printf("STAMPA VALORI STRUCT\n");
    //Hypothesis model = ConvertiStruct(modello, false);
    StampaStruct(modelloStruct);
    //Chiusura file
    fclose(pFile);

    bool continua = true;
    //------------
    int countDebug =0;
    //------------
    while(continua)
    {
        bool ok =false;
        bool ok2 = false;
        char *valori[10] = {"Alternativa (vero/falso)","Bar (vero/falso)","Giorno (vero/falso)","Fame (vero/falso)",
        "Affollato (nessuno/qualcuno/pieno)","Prezzo ($/$$/$$$)","Pioggia (vero/falso)",
        "Prenotazione (vero/falso)","Tipo","Attesa stimata"};
        int valoriMalloc[10] = {5,5,5,5,8,3,5,5,9,5};
        char **ipotesi;
        //PER DEBUG
        // char *ipotesi2[] = {"vero", "vero", "vero", "vero", "pieno", "$$", "falso", "vero", "italiano", ">60"};
        //                  falso,vero,vero,falso,nessuno,$$$,vero,falso,fast-food,<10
        // char *ipotesi3[] = {"vero", "vero", "vero", "vero", "pieno", "$", "vero", "falso", "fast-food", "10-29"};
        //-------------------------------------------------------------------------------------------------------
        ipotesi = malloc(10 * sizeof(char*));

        //lettura file exp per altre ipotesi
        FILE* expFile = NULL;
        if((expFile = fopen("exp.csv", "r"))== NULL)
        {
            printf("ERRORE LETTURA FILE");
            return -1;
        }
        char*** exp = LetturaFile(expFile, 10, MAX_LEN); 
        fclose(expFile);
        //---------------------------------------
        while(!ok)
        {
            char useFile[5];
            printf("Usare valori in input o da file? (1/2)");
            scanf(" %s", useFile);
            //PER DEBUG
            // char useFile[] = {"2"};
            //--------------------
            int useFileOk = strncmp(useFile, "2", 1);
            if(useFileOk == 0)
            {
                if(readRows == 10)
                {
                    printf("\nRaggiunto il numero massimo di righe da file\n");
                }
                else
                {
                    //nel caso si leggano gli input dal file exp, ogni iterazione si legge la riga dopo (MAX 10)
                    char **strings = exp[readRows];
                    for(int i = 0; i < 10; i++)
                    {
                        char *str = strings[i];
                        int len = strlen(str);
                        ipotesi[i] = malloc(len* sizeof(char));
                        strcpy(ipotesi[i], str);
                    }   
                    readRows++; 
                    ok = true;
                    printf("\nIpotesi da file exp : \n");
                    StampaArray(ipotesi, 10);
                }
            }
            else
            {
                printf("Inserire i valori da testare: \n");
                for(int i = 0; i < 10; i++)
                {
                    while(!ok2)
                    {
                        printf("Inserire il valore di %s: ", valori[i]);
                        char str[25];
                        scanf("%s", str);
                        ok2 = ControlloInput(str, i);
                        int len = strlen(str);
                        ipotesi[i] = malloc(len* sizeof(char));
                        strcpy(ipotesi[i], str);
                        printf("\n");

                        //PER DEBUG
                        // if(countDebug == 1)
                        // {
                        //      int len = strlen(ipotesi2[i]);
                        //     ipotesi[i] = malloc(len* sizeof(char));
                        //     strcpy(ipotesi[i], ipotesi2[i]);
                        // }
                        // else
                        // {
                        //     int len = strlen(ipotesi3[i]);
                        //     ipotesi[i] = malloc(len* sizeof(char));
                        //     strcpy(ipotesi[i], ipotesi3[i]);
                        //     ok2 = true;
                        // } 
                        //------------------------------------------            
                    }
                    ok2 = false;
                }
                ok = true;
                //------------
                //countDebug++;
                //------------
            }           
        }
        //Hypothesis ipotesi3Str = ConvertiStruct(ipotesi, false, false);

        printf("\nIl modello prevede che per l'ipotesi data bisognerebbe: %s\n\n" , Aspettiamo(ipotesi, modello, 1, 0.25) ? "aspettare" : "NON aspettare");

        //Controllo correttezza ipotesi da metodo aspettiamo
        bool okCorr = false;
        while(!okCorr)
        {
            printf("Il risultato e' corretto? (Y/N)");
            char corr[20];
            scanf(" %s",corr);
            //PER DEBUG
            //char corr[] = {"N"};
            //-----------------
            int yInt = strncmp(corr, "Y", 1);
            int nInt = strncmp(corr, "N", 1);
            if(yInt != 0 && nInt != 0)
                printf("Valore non riconosciuto, inserire un valore corretto\n");
            else if(yInt == 0)
            {
                okCorr = true;
            }
            else
            {
                //Se il risultato della funzione Aspettiamo non è corretto,
                //la rieseguo con un moltiplicatore diverso per ? e per uguale(= == 0,5 | ? == 0)
                printf("\nConsiderando che lo scorso risultato era errato, il modello prevede che per l'ipotesi data bisognerebbe: %s\n\n" , Aspettiamo(ipotesi, modello, 0.5 ,0) ? "aspettare" : "NON aspettare");
                okCorr = true;
            }
        }

        printf("Vuoi aggiungere questa ipotesi al modello di training? (Y/N):");
        char input[20];
        scanf(" %s", input);
        
        //PER DEBUG
        //char input[] = {"Y"};
        //--------------------
        printf("\n");
        int val = strncmp(input, "Y", 2);
        if(val == 0)
        {
            Hypothesis ip = ConvertiStruct(ipotesi, false, true);
            AggiungiADataSet(datasetStruct, ip, addedRows, righeInput);
            modelloStruct = Find_S_Struct(datasetStruct, righeInput + addedRows + 1, 10);
            printf("Modello ricalcolato dopo l'aggiunta di una nuova ipotesi: \n");
            StampaStruct(modelloStruct);
            printf("DATASET AGGIORNATO: ");
            addedRows++;
            StampaDataSet(datasetStruct, addedRows, righeInput);
        }

        char cont[20];
        printf("Vuoi continuare: (NO per uscire)...");
        scanf(" %s", cont);
        printf("\n\n\n");
        //PER DEBUG
        // char cont[] = "asdasd";
        //------------------------
        int intCont = strncmp(cont , "NO", 2);
        if(intCont == 0)
            continua = false;
    }
    

    system("pause");
    return 0;
}
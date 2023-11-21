#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#define MAX_ROW 10000
#define MAX_LEN 200

// region struct
#pragma region

// Creo la struct per poter inizializzare un valore standard da confrontare con
// gli elementi del file e poter memorizzare quelli che in quel momento sono più
// vicini allo standard
typedef struct Loan
{
    char *credit_policy;
    char *purpose;
    char *int_rate;
    char *installments;
    char *log_annual_inc;
    char *dti;
    char *fico;
    char *days_with_cr_line;
    char *revol_bal;
    char *revol_util;
    char *inq_last_6mths;
    char *delinq_2yrs;
    char *pub_rec;
    char *not_fully_paid;
} Loan;

// Creo questa struct per tenermi traccia dei punti dei Loan se calcolo che 
// sono uno dei più vicini al mio valore standard
typedef struct Pair
{
    Loan oggetto;
    int puntiSimilarita;
} Pair;
#pragma endregion

// Metodo per controllare se il valore che sto controllando quanto è simile al mio
// valore standard è uno dei più vicini, in quel caso ritorno la posizione in cui
// và immagazzinato, altrimenti -1
int IsOneOfTheNearest(Pair near[], int puntiTemp, int k)
{
    int min = 99999;
    int pos = 0;
    for (int i = 0; i < k; i++)
    {
        if (min > near[i].puntiSimilarita)
        {
            min = near[i].puntiSimilarita;
            pos = i;
        }
    }
    if (near[pos].puntiSimilarita < puntiTemp)
    {
        return pos;
    }
    return -1;
}

void PrintObject(int index, int similarity_score, Loan* pObject) 
{
    printf("Oggetto [%d] - punti di similarità: %d/13\n", index, similarity_score);
    puts("{");
    printf("\t%s: %s,\n", "\"credit_policy\"", pObject->credit_policy);
    printf("\t%s: %s,\n", "\"purpose\"", pObject->purpose);
    printf("\t%s: %s,\n", "\"int_rate\"", pObject->int_rate);
    printf("\t%s: %s,\n", "\"installments\"", pObject->installments);
    printf("\t%s: %s,\n", "\"long_annual_inc\"", pObject->log_annual_inc);
    printf("\t%s: %s,\n", "\"dti\"", pObject->dti);
    printf("\t%s: %s,\n", "\"fico\"", pObject->fico);
    printf("\t%s: %s,\n", "\"days_with_cr_line\"", pObject->days_with_cr_line);
    printf("\t%s: %s,\n", "\"revol_bal\"", pObject->revol_bal);
    printf("\t%s: %s,\n", "\"revol_util\"", pObject->revol_util);
    printf("\t%s: %s,\n", "\"inq_last_6mths\"", pObject->inq_last_6mths);
    printf("\t%s: %s,\n", "\"delinq_2yrs\"", pObject->delinq_2yrs);
    printf("\t%s: %s,\n", "\"pub_rec\"", pObject->pub_rec);
    printf("\t%s: %s,\n", "\"not_fully_paid\"", pObject->not_fully_paid);
    puts("}");
    puts("");
}

int main()
{
    int k;
    Loan standard;
// region inizializzazione standard
#pragma region
    standard.credit_policy = "0";
    standard.purpose = "debt_consolidation";
    standard.int_rate = "0.15";
    standard.installments = "986.3";
    standard.log_annual_inc = "13.036823";
    standard.dti = "7.89";
    standard.fico = "679";
    standard.days_with_cr_line = "3674.9";
    standard.revol_bal = "16749";
    standard.revol_util = "30.11";
    standard.inq_last_6mths = "2";
    standard.delinq_2yrs = "1";
    standard.pub_rec = "0";
    standard.not_fully_paid = "0";
#pragma endregion

    // Prendo in input quanti valori vicini vuole l'utente
    printf("\nQuanti vicini (k) vuoi visualizzare del valore di default? ");
    scanf("%d", &k);

    // Inizializzo tutti i valori di nearest a -1 cosìcche sicuramente ci saranno k 
    // elementi nell'array
    Pair nearest[k];
    for (int i = 0; i < k; i++)
    {
        nearest[i].puntiSimilarita = -1;
    }
    
    //Apro il file con un percorso non relativo, quindi da cambiare con il file messo nello zip
    FILE *file;
    char filename[] = "/Users/nickolausen/Library/CloudStorage/OneDrive-AlmaMaterStudiorumUniversitàdiBologna/UNI/1o Anno/Programmazione/Repo_ESERCIZI/elaborati-programmazione/sett7_06-11-2023/DS-Credit/loan_data.csv"; // Inserisci il nome del TUO file CSV

    // Apro il file
    file = fopen(filename, "r");
    
    // Se il file è stato aperto male interrompo l'esecuzione e mando un "messaggio d'errore"
    if (file == NULL)
    {
        printf("Impossibile aprire il file %s\n", filename);
        return 1;
    }

    // Dichiaro le variabili che mi serviranno durante l'esecuzione principale
    char line[MAX_ROW][MAX_LEN];
    long long col = 0;
    double puntiSimilarita;
    double val = 0;

    // Leggo il file CSV riga per riga
    while (fgets(line[col], MAX_LEN, file))
    {
        char *token;
        token = strtok(line[col], ",");
        puntiSimilarita = 0;
        int i = 0;
        Loan temp;

        // Analizz0 la riga del file CSV in colonne separate
        while (token != NULL)
        {

            // region switch
            #pragma region

            // Attraverso uno switch controllo in che colonna solo cosicchè da potermi regolare
            // con i controlli per la similarità
            switch (i)
            {
            case 0:
                temp.credit_policy = token;
                if (strcmp(token, standard.credit_policy) == 0)
                    puntiSimilarita++;
                break;
            case 1:
                temp.purpose = token;
                if (strcmp(token, standard.purpose) == 0)
                    puntiSimilarita++;
                break;
            case 2:
                temp.int_rate = token;
                if (strcmp(token, standard.int_rate) == 0)
                    puntiSimilarita++;
                break;
            case 3:
                temp.installments = token;
                val = fabs((double)*token - (double)*standard.installments);
                if (val < 3)
                    puntiSimilarita++;
                break;
            case 4:
                temp.log_annual_inc = token;
                val = fabs((float)*token - (float)*standard.log_annual_inc);
                if (val < 3)
                    puntiSimilarita++;
                break;
            case 5:
                temp.dti = token;
                if (strcmp(token, standard.dti) == 0)
                    puntiSimilarita++;
                break;
            case 6:
                temp.fico = token;
                val = fabs((double)*token - (double)*standard.fico);
                if (val < 1)
                    puntiSimilarita++;
                break;
            case 7:
                temp.days_with_cr_line = token;
                val = fabs((float)*token - (float)*standard.days_with_cr_line);
                if (val < 2)
                    puntiSimilarita++;
                break;
            case 8:
                temp.revol_bal = token;
                val = fabs((float)*token - (float)*standard.revol_bal);
                if (val < 3)
                    puntiSimilarita++;
                break;
            case 9:
                temp.revol_util = token;
                if (strcmp(token, standard.revol_util) == 0)
                    puntiSimilarita++;
                break;
            case 10:
                temp.inq_last_6mths = token;
                if (strcmp(token, standard.inq_last_6mths) == 0)
                    puntiSimilarita++;
                break;
            case 11:
                temp.delinq_2yrs = token;
                if (strcmp(token, standard.delinq_2yrs) == 0)
                    puntiSimilarita++;
                break;
            case 12:
                temp.pub_rec = token;
                if (strcmp(token, standard.pub_rec) == 0)
                    puntiSimilarita++;
                break;
            case 13:
                temp.not_fully_paid = token;
                if (strcmp(token, standard.not_fully_paid) == 0)
                    puntiSimilarita++;
                break;
            }
#pragma endregion

            // Avanzo di colonna
            token = strtok(NULL, ",");

            // Cambio la colonna su cui devo controllare la similarità
            i++;
        }

        // Cerco se l'oggetto in runtime è uno dei più simili al valore standard 
        // al momento e prendo la posizione in cui devo metterlo
        int pos = IsOneOfTheNearest(nearest, puntiSimilarita, k);
        if (pos != -1)
        {
            // Aggiorno quella posizione
            nearest[pos].oggetto = temp;
            nearest[pos].puntiSimilarita = puntiSimilarita;
        }
        // Avanzo di riga
        col++;
    }

    printf("\n>> Oggetti più vicini trovati: \n");
    for (int i = 0; i < k; i++)
    {
        PrintObject(i, nearest[i].puntiSimilarita, &nearest[i].oggetto);
    }

    // Chiudi il file
    fclose(file);

    return 0;
}

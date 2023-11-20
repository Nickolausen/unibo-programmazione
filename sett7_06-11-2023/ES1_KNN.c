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

typedef struct Pair
{
    Loan oggetto;
    int puntiSimilarita;
} Pair;
#pragma endregion

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

    printf("\nQuanti vicini (k) vuoi visualizzare del valore di default? ");
    scanf("%d", &k);
    Pair nearest[k];
    for (int i = 0; i < k; i++)
    {
        nearest[i].puntiSimilarita = 0;
    }

    FILE *file;
    char filename[] = "/Users/riccardo/Desktop/programmi/prove/loan_data.csv"; // Inserisci il nome del TUO file CSV

    file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Impossibile aprire il file %s\n", filename);
        return 1;
    }

    char line[MAX_ROW][MAX_LEN];
    long long col = 0;
    double puntiSimilarita;
    double val = 0;

    // Leggi il file CSV riga per riga
    while (fgets(line[col], MAX_LEN, file))
    {
        char *token;
        token = strtok(line[col], ",");
        puntiSimilarita = 0;
        int i = 0;
        Loan temp;

        // Analizza la riga del file CSV in colonne separate
        while (token != NULL)
        {

// region switch
#pragma region
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

            token = strtok(NULL, ",");
            i++;
        }
        int pos = IsOneOfTheNearest(nearest, puntiSimilarita, k);
        if (pos != -1)
        {
            nearest[pos].oggetto = temp;
            nearest[pos].puntiSimilarita = puntiSimilarita;
        }
        col++;
    }

    printf("\n Oggetti più vicini trovati: \n");
    for (int i = 0; i < k; i++)
    {
        printf("%s ", nearest[i].oggetto.credit_policy);
        printf("%s ", nearest[i].oggetto.purpose);
        printf("%s ", nearest[i].oggetto.int_rate);
        printf("%s ", nearest[i].oggetto.installments);
        printf("%s ", nearest[i].oggetto.log_annual_inc);
        printf("%s ", nearest[i].oggetto.dti);
        printf("%s ", nearest[i].oggetto.fico);
        printf("%s ", nearest[i].oggetto.days_with_cr_line);
        printf("%s ", nearest[i].oggetto.revol_bal);
        printf("%s ", nearest[i].oggetto.revol_util);
        printf("%s ", nearest[i].oggetto.inq_last_6mths);
        printf("%s ", nearest[i].oggetto.delinq_2yrs);
        printf("%s ", nearest[i].oggetto.pub_rec);
        printf("%s ", nearest[i].oggetto.not_fully_paid);
        printf("Con punti di similarità: %d \n", nearest[i].puntiSimilarita);
    }

    // Chiudi il file
    fclose(file);

    return 0;
}

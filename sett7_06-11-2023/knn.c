#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW  10000 
#define MAX_LEN  200  

typedef struct Loan{
    int credit_policy;
    char[100] debt_consolidation;
    double int_rate;
    double installments;
    double log_annual_inc;
    double dti;
    int fico;
    double days_with_cr_line;
    double revol_bal;
    double revol_util;
    int inq_last_6mths;
    int delinq_2yrs;
    int pub_rec;
    int not_fully_paid;
} Loan;

#pragma region 

enum Purpose{
    DEBTCONSOLIDATION="debt_consolidation",
    CREDITCARD="credit_card",
    ALLOTHER="all_other",
    HOMEIMPROVEMENT="home_improvement",
    SMALLBUISNESS="small_buisness",
    MAJORPURCHASE="major_purchase",
    EDUCATIONAL="educational"
};

#pragma endregion

int main() {
    int k;
    Loan standard;
#pragma inizializzazione standard
    standard.credit_policy=1;
    standard.debt_consolidaiton=DEBTCONSOLIDATION;
    standard.int_rate=0.15;
    standard.installments=986.3;
    standard.log_annual_inc=10.03682346;
    standard.dti=7.89;
    standard.fico=679;
    standard.days_with_cr_line=3674.98;
    standard.revol_bal=16749;
    standard.revol_util=30.11;
    standard.inq_last_6mths=2;
    standard.delinq_2yrs=1;
    standard.pub_rec=0;
    standard.not_fully_paid=0;
#pragma endregion

    printf("\nQuanti vicini (k) vuoi visualizzare del valore di default? ");
    scanf("%d", &k);
    double nearest[k];
    for(int i=0;i<k;i++){
        nearest[i]=0;
    }

    FILE *file;
    char filename[] = "/Users/riccardo/Desktop/programmi/prove/loan_data.csv";  // Inserisci il nome del TUO file CSV

    file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Impossibile aprire il file %s\n", filename);
        return 1;
    }

    char line[MAX_ROW][MAX_LEN];
    long long col = 0;

    // Leggi il file CSV riga per riga
    while (fgets(line[col], MAX_LEN, file)) {
        char *token;
        token = strtok(line[col], ",");

        // Analizza la riga del file CSV in colonne separate
        while (token != NULL) {
            // Stampa il valore della cella
            printf("%s ", token);
            token = strtok(NULL, ",");
        }
        col++;
    }

    // Chiudi il file
    fclose(file);

    return 0;
}

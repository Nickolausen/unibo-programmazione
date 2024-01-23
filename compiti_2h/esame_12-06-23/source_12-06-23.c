#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define NR_GIORNI 7
#define NR_TURNI 8
#define NR_MEDICI 200

#define MAX_ID_REPARTI 100
#define MAX_PAZIENTI 4

typedef struct singolo_turno {
    int id_turno;
    int giorno;
    int numero_pazienti;
} singolo_turno;

typedef struct medico {
    char id_medico[12 + 1];
    char reparto[5 + 1];
    singolo_turno turni[NR_GIORNI][NR_TURNI];
} medico;

typedef struct esubero {
    singolo_turno turni[MAX_ID_REPARTI];
} esubero;

void aggiungi_medico(medico *vect, medico *med) 
{
    /* [...] */
}

medico *get_medico_by_id(medico *vect, char *id_medico)
{
    for (int i = 0; i < NR_MEDICI; i++) 
    {
        if (strcmp(vect[i].id_medico, id_medico) == 0) 
            return &vect[i];
    }

    return NULL;
}

void leggi_appuntamenti(char *fileName, medico *out_medici, esubero *esuberi) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    int idxEsubero = 0;
    while (!feof(pFile)) 
    {
        char id_medico[12 + 1];
        int turno_richiesto, giorno_richiesto;

        char slice_id_medico, reparto[5 + 1];
        fscanf(pFile, "%*s %c-%s %*s %d %d\n", 
            &slice_id_medico, reparto, &turno_richiesto, &giorno_richiesto);

        snprintf(id_medico, 12 + 1, "%c-%s", slice_id_medico, reparto);

        medico *med = get_medico_by_id(out_medici, id_medico);
        /* Se il medico è NULL, allora non esiste - per cui lo creo */
        if (med == NULL) 
        {
            med = (medico *)malloc(sizeof(medico));
            assert(med != NULL);

            strcpy(med->id_medico, id_medico);
            strcpy(med->reparto, reparto);

            med->turni[giorno_richiesto - 1][turno_richiesto - 1].id_turno = turno_richiesto;
            med->turni[giorno_richiesto - 1][turno_richiesto - 1].giorno = giorno_richiesto;
            med->turni[giorno_richiesto - 1][turno_richiesto - 1].numero_pazienti = 0;

            /* Aggiungo il nuovo medico al vettore */
            aggiungi_medico(out_medici, med);
        }

        med->turni[giorno_richiesto - 1][turno_richiesto - 1].numero_pazienti++;

        /* Se per il turno richiesto nel giorno richiesto si crea un esubero, lo aggiungo alla lista */
        if (med->turni[giorno_richiesto - 1][turno_richiesto - 1].numero_pazienti >= MAX_PAZIENTI)
        {
            esuberi[idxEsubero].turni[atoi(reparto)] = med->turni[giorno_richiesto - 1][turno_richiesto - 1];
            idxEsubero++;
            continue;
        }

        free(med);
    }
}

void stampa_esuberi(esubero *esuberi, int index)
{
    if (index == NR_MEDICI) return;
    /* Stampa ricorsiva */
    stampa_esuberi(esuberi, index + 1);
}

void sort_medici_by_reparto(medico *vect) 
{
    bool swapping = true;
    while (swapping) 
    {
        swapping = false;
        for (int i = 0; i < NR_MEDICI - 1; i++) 
        {
            medico *swapEl;
            if (strcmp(vect[i].reparto, vect[i + 1].reparto) > 0) 
            {
                swapping = true;
                swapEl = &vect[i];
                vect[i] = vect[i + 1];
                vect[i + 1] = *swapEl;
            } 
        }
    }
}

void occupazione_reparti(medico *medici) 
{
    int max_pazienti_settimana = 7 * 8 * 4; /* 224 pazienti totali */

    /* (I) Ordina i medici per 'reparto' */
    medico *medici_sorted_by_reparto = medici;
    sort_medici_by_reparto(medici_sorted_by_reparto);

    /* (II) Calcola occupazione finché non cambia il 'reparto' */
    int nr_reparti = 0;
    for (int i = 0; i < NR_MEDICI - 1; i++) 
    {
        if (strcmp(medici_sorted_by_reparto[i].reparto, medici_sorted_by_reparto[i + 1].reparto) != 0)
            nr_reparti++;
    }

    int idxMedico = 0;
    for (int i = 0; i < nr_reparti; i++)
    {
        float* perc_occupazione = NULL;
        int idxReparto = 0;

        /* Calcolo le statistiche per un reparto */
        while (strcmp(medici_sorted_by_reparto[idxMedico].reparto, medici_sorted_by_reparto[idxMedico + 1].reparto) == 0 && 
            idxMedico < (NR_MEDICI - 1)) 
        {
            perc_occupazione = (float *)realloc(perc_occupazione, sizeof(float) * (idxReparto + 1));
            assert(perc_occupazione != NULL);
            
            for (int giorno = 0; giorno < NR_GIORNI; giorno++) 
            {
                for (int turno = 0; turno < NR_TURNI; turno++) 
                {
                    perc_occupazione[idxReparto] += medici_sorted_by_reparto[idxMedico].turni[giorno][turno].numero_pazienti;
                }
            }

            idxMedico++;
        }
    }
}

int main() 
{
    char *fileName = "appuntamenti.txt";
    medico *medici = (medico *)malloc(sizeof(medico) * NR_MEDICI);
    assert(medici != NULL);

    
    return 0;
}
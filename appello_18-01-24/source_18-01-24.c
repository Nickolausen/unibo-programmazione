/* Nicholas Magi, Matricola: 0001113915*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include <limits.h>

#define EMPTY_STRING ""
#define NR_GIORNI 7
#define NR_TURNI 8
#define COUNT_REPARTI 200
#define COUNT_ESUBERI 100

#define SIZEOF(vect) (sizeof(vect) / sizeof(vect[0]))

typedef struct singolo_turno {
    int id_turno;
    int pazienti_per_turno;

    char id_medico1[12 + 1];
    int pazienti_medico1;
    int pazienti_medico1_extra;

    char id_medico2[12 + 1];
    int pazienti_medico2;
    int pazienti_medico2_extra;

    int pazienti_totali;
} singolo_turno;

typedef struct reparto {
    char id_reparto[5 + 1];
    singolo_turno turni[NR_GIORNI][NR_TURNI];
} reparto;

typedef struct reparto_medici {
    char codice_prestazione_richiesta[25 + 1];
    char id_reparto[5 + 1];
} reparto_medici;

void aggiungi_reparto(reparto *reparti, reparto *rep) 
{
    /* 
     * Poiché il vettore reparti è ordinato per 'id_reparto' crescente,
     * ogni volta che inserisco un nuovo reparto devo mantenere tale ordine.
     */
    
    /* [PRIORITY INSERT] */
}

char *get_reparto_id_by_codice_prestazsione(char *codice_prestazione_richiesta, reparto_medici *repartoMedici) 
{
    /* Ciclo che continua per tutta la lunghezza del vettore */
    for (int i = 0; i < SIZEOF(repartoMedici); i++) 
    {
        if (strcmp(codice_prestazione_richiesta, repartoMedici[i].codice_prestazione_richiesta) == 0) 
        {
            return repartoMedici[i].id_reparto;
        }
    }

    return NULL;
}

int get_reparto_index_by_id(reparto *reparti, char *id_reparto) 
{
    for (int i = 0; i < COUNT_REPARTI; i++) 
    {
        if (strcmp(reparti[i].id_reparto, id_reparto) == 0) 
            return i;
    }

    return -1;
}

void leggi_appuntamenti(char *fileName, reparto *reparti, reparto_medici *repartoMedici, reparto *esuberi) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    int idxEsubero = 0, idxReparto = 0;
    while (!feof(pFile)) 
    {
        char id_medico_richiesto[12 + 1], codice_prestazione_richiesta[25 + 1];
        int giorno_richiesto, id_turno_richiesto;

        fscanf(pFile, "%*s %s %s %d %d\n", 
            id_medico_richiesto, codice_prestazione_richiesta, 
            &giorno_richiesto, &id_turno_richiesto);

        char *id_reparto = get_reparto_id_by_codice_prestazione(codice_prestazione_richiesta, repartoMedici);
        /* 
         *  Suppongo che la corrispondenza 
         *  codice_prestazione_richiesta - id_reparto sia garantita per qualsiasi id_reparto 
         */
        assert(id_reparto != NULL);

        int nuovo_reparto_idx = get_reparto_index_by_id(reparti, id_reparto);
        reparto *rep;
        if (nuovo_reparto_idx == -1) 
        {
            /* Se il nuovo reparto ha indice -1 allora non esiste, dunque lo creo */
            rep = (reparto *)malloc(sizeof(reparto));
            assert(rep != NULL);

            strcpy(rep->id_reparto, id_reparto);
            strcpy(rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].id_medico1, EMPTY_STRING);
            strcpy(rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].id_medico2, EMPTY_STRING);

            rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].id_turno = id_turno_richiesto;
            rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].pazienti_per_turno = (rand() % 10) + 1;

            rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].pazienti_medico1 =
                rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].pazienti_medico2 =
                rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].pazienti_medico1_extra =
                rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].pazienti_medico2_extra =
                rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1].pazienti_totali = 0;

            aggiungi_reparto(reparti, rep);      
        }
        else 
        {
            rep = &reparti[nuovo_reparto_idx];
        } 

        singolo_turno *turno = &rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1];
        
        /* Assegno il medico richiesto - se ancora risulta vuoto */
        if (strcmp(turno->id_medico1, EMPTY_STRING))
            strcpy(turno->id_medico1, id_medico_richiesto);
        else if (strcmp(turno->id_medico2, EMPTY_STRING))
            strcpy(turno->id_medico2, id_medico_richiesto);
        
        /* Se supero il numero massimo di pazienti visitabili per quel turno, allora 
        si crea un esubero */
        if (turno->pazienti_totali + 1 >= turno->pazienti_per_turno) 
        {
            strcmp(turno->id_medico1, id_medico_richiesto) == 0 
                ? turno->pazienti_medico1_extra++ 
                : turno->pazienti_medico2_extra++;

            rep->turni[giorno_richiesto - 1][id_turno_richiesto - 1] = *turno;
            esuberi[idxEsubero] = *rep;
            
            idxEsubero++;
            continue;
        }
         
        strcmp(turno->id_medico1, id_medico_richiesto) == 0 
            ? turno->pazienti_medico1++
            : turno->pazienti_medico2++;

        turno->pazienti_totali++;
    }
}

char *get_medico_con_max_richieste(reparto *esuberi)
{
    int maxValue = INT_MIN;
    char *id_medico_max_pazienti = NULL;

    for (int i = 0; i < COUNT_ESUBERI; i++) 
    {
        for (int giorno = 0; giorno < NR_GIORNI; giorno++) 
        {
            for(int turno = 0; turno < NR_TURNI; turno++)
            {
                if (esuberi[i].turni[giorno][turno].pazienti_medico1_extra > maxValue) 
                {
                    maxValue = esuberi[i].turni[giorno][turno].pazienti_medico1_extra;
                    strcpy(id_medico_max_pazienti, esuberi[i].turni[giorno][turno].id_medico1);
                }

                if (esuberi[i].turni[giorno][turno].pazienti_medico2_extra > maxValue) 
                {
                    maxValue = esuberi[i].turni[giorno][turno].pazienti_medico2_extra;
                    strcpy(id_medico_max_pazienti, esuberi[i].turni[giorno][turno].id_medico2);
                }
            }
        } 
    }

    return id_medico_max_pazienti;
}

void medici_esuberi(reparto *esuberi) 
{
    char *medico_con_max_richieste = get_medico_con_max_richieste(esuberi);
    
    printf("Medico con più richieste: %s\n\n", medico_con_max_richieste);

    for (int i = 0; i < COUNT_ESUBERI; i++) 
    {
        for (int giorno = 0; giorno < NR_GIORNI; giorno++) 
        {
            for(int turno = 0; turno < NR_TURNI; turno++)
            {
                printf("=== Reparto [%s] ===\n", esuberi->id_reparto);
                printf("\tRichieste per medico '%s': %d\n", esuberi->turni[giorno][turno].id_medico1, esuberi->turni[giorno][turno].pazienti_medico1_extra);
                printf("\tRichieste per medico '%s': %d\n", esuberi->turni[giorno][turno].id_medico2, esuberi->turni[giorno][turno].pazienti_medico2_extra);
            }
        }

        puts(""); 
    }
}

void occupazione_reparti(reparto *reparti)
{
    for (int i = 0; i < COUNT_REPARTI; i++) 
    {
        for (int giorno = 0; giorno < NR_GIORNI; giorno++) 
        {
            int max_pazienti_giorno = 0, pazienti_effettivi = 0;
            for (int turno = 0; turno < NR_TURNI; turno++) 
            {
                pazienti_effettivi += reparti[i].turni[giorno][turno].pazienti_totali;
                max_pazienti_giorno += reparti[i].turni[giorno][turno].pazienti_per_turno;
            }

            float occupazione_giornaliera = ((float)pazienti_effettivi / (float)max_pazienti_giorno) * 100;
            
            printf("Reparto [%s]: nel giorno %d, occupato al %.2f", 
                reparti[i].id_reparto, giorno + 1, occupazione_giornaliera);

            puts("");
        }
    }
}

int main() 
{
    srand(time(NULL));
    char *fileName = "appuntamenti.txt";

    /* Vettore allocato dinamicamente */
    reparto *reparti = malloc(sizeof(reparto) * COUNT_REPARTI);
    assert(reparti != NULL);

    /* Vettore già riempito - dato dal testo */
    reparto_medici *repartoMedici = (reparto_medici *)malloc(sizeof(reparto_medici) * (rand() % 10 + 1));
    assert(repartoMedici != NULL);

    reparto esuberi[100];

    leggi_appuntamenti(fileName, reparti, repartoMedici, esuberi);
    medici_esuberi(esuberi);

    /* 
     * Non passo il vettore repartoMedici tra i parametri di input come da richiesta poiché 
     * il campo 'id_reparto' è già contenuto nel vettore 'reparti' 
     */
    occupazione_reparti(reparti);
    return 0;
}
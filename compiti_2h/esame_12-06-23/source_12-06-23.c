#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define NR_MEDICI 200
#define NR_GIORNI 7
#define NR_TURNI 8
#define MAX_PAZIENTI_PER_TURNO 4

typedef struct singolo_turno {
    int id_turno;
    int numero_pazienti;
} singolo_turno;

typedef struct esubero {
    singolo_turno turni[NR_GIORNI][NR_TURNI];
    bool is_empty;
} esubero;

typedef struct list_esubero {
    esubero *data;
    int size;
} list_esubero;

typedef struct medico {
    char id_medico[12 + 1];
    char reparto[5 + 1];
    singolo_turno turni[NR_GIORNI][NR_TURNI];
} medico;

typedef struct list_medico {
    medico *data;
    int last_index;
    int size;
} list_medico;

medico *find_medico(list_medico *medici, char *id_medico)
{
    for (int i = 0; i <= medici->last_index; i++) 
    {
        if (strcmp(medici->data[i].id_medico, id_medico) == 0)
            return &medici->data[i];
    }

    return NULL;
}

void aggiungi_medico(list_medico *medici, medico *nuovo_medico) 
{
    /* Inserimento ordinato - ordine crescente di 'id_medico' */
    int first_index_available = medici->last_index + 1;
    
    /* se non posso più aggiungere medici (superati quindi i 200 medici presenti), esco */
    if (first_index_available => medici->size) 
    {
        printf("Errore - non è possibile aggiungere ulteriori medici.\n");
        return;
    }

    /* Se al momento la lista è vuota, aggiungo senza fare altro */
    if (medici->last_index == -1) 
    {
        medici->data[first_index_available] = *med;
        medici->last_index = first_index_available;
        return;
    }

    /* Scorro il vettore in cerca della posizione in cui inserire il nuovo medico */
    for (int i = 0; i <= medici->last_index; i++)
    {
        /* Se ho trovato la posizione, */
        if (strcmp(medici->data[i].id_medico, nuovo_medico->id_medico) < 0) 
        {
            /* shifto tutti gli elementi a destra di 1 */
            for (int j = medici->last_index; j > i; j--) 
            {
                medici->data[j] = medici->data[j - 1];
            }

            /* aggiungo il nuovo medico */
            medici->data[i] = *med;

            /* aggiorno l'indice dell'ultimo elemento presente nel vettore */
            medici->last_index++;
            return;
        }
    }
}

void aggiungi_esubero_at(list_esubero *esuberi, int idx, singolo_turno *new_esubero)
{
    /* 
     * se voglio aggiungere un elemento che sfora 
     * la dimensione del vettore attuale, 
     */
    if (idx >= esuberi->size) 
    {
        int new_size = idx + 1;

        /* aggiungo le celle in più */
        esuberi->data = (esubero *)realloc((esubero *)esuberi->data, sizeof(esubero) * new_size);
        assert(esuberi->data != NULL);
        esuberi->size = new_size;

        for (int i = 0; i < idx; i++)
        {
            /* aggiungo 'esuberi vuoti' nelle posizioni precedenti all'esubero richiesto */
            esuberi->data[i].is_empty = true;
        }
    }

    esuberi[idx] = *new_esubero;
}

void leggi_appuntamenti(char *fileName, list_medico *medici, list_esubero *esuberi) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    while(!feof(pFile)) /* Leggo finchè non ho raggiunto la fine del file */
    {
        char id_medico[12 + 1], slice_id_medico[12 + 1];
        int reparto;
        int turno_richiesto, giorno_richiesto;

        fscanf(pFile, "%*s %s-%d %*s %d %d\n", 
            slice_id_medico,
            &reparto,
            &turno_richiesto,
            &giorno_richiesto);
        
        /* Compatto 'id_medico' */
        snprintf(id_medico, 12, "%s-%d", slice_id_medico, reparto);

        medico *med = find_medico(medici, id_medico);
        if (med == NULL) /* Se nel 'database' non esiste, allora lo inizializzo e lo aggiungo */
        {
            strcpy(med->id_medico, id_medico);
            snprintf(med->reparto, 5, "%d", reparto);

            for (int giorno = 0; giorno < NR_GIORNI; giorno++)
            {
                for (int turno = 0; turno < NR_TURNI; turno++)
                {
                    med->turni[giorno][turno].id_turno = turno + 1;
                    med->turni[giorno][turno].numero_pazienti = 0;
                }
            }

            /* aggiungo il medico alla lista */
            aggiungi_medico(medici, med);
        }

        if (med->turni[giorno_richiesto][turno_richiesto].numero_pazienti + 1 > MAX_PAZIENTI_PER_TURNO) 
        {
            /* si crea un esubero - lo inizializzo */
            esubero *new_esubero = (esubero *)malloc(sizeof(esubero));
            assert(new_esubero != NULL);
            new_esubero->is_empty = false;

            for (int giorno = 0; giorno < NR_GIORNI; giorno++)
            {
                for (int turno = 0; turno < NR_TURNI; turno++) 
                {
                    new_esubero->turni[giorno][turno].id_turno = turno + 1;
                    new_esubero->turni[giorno][turno].numero_pazienti = 0;
                }
            }

            new_esubero->turni[giorno_richiesto][turno_richiesto].id_turno = turno_richiesto + 1;
            new_esubero->turni[giorno_richiesto][turno_richiesto].numero_pazienti = 
                med->turni[giorno_richiesto][turno_richiesto].numero_pazienti + 1;
            
            /* aggiungo alla lista esuberi il nuovo esubero */
            aggiungi_esubero_at(esuberi, reparto);
        }
        else
        {
            /* aggiungo il paziente al turno richiesto */
            med->turni[giorno_richiesto][turno_richiesto].numero_pazienti++;
        }
    }
}

void stampa_esuberi(list_esubero *esuberi, int idx) 
{
    if (idx >= esuberi->size) return;

    printf("Settimana [%d]\n", idx);
    if (!esuberi->data[idx].is_empty) 
    {
        for (int giorno = 0; giorno < )
    }
    else
    {
        printf("Nessun esubero!\n");
    }

    putchar('\n');

    stampa_esuberi(esuberi, idx + 1);
}

int main() 
{
    list_medico *medici = (list_medico *)malloc(sizeof(list_medico));
    assert(medici != NULL);
    
    /* Allocazione dinamica del vettore - salvato in una struttura 'di supporto' per avere informazioni aggiuntive */
    medici->data = (medici *)malloc(sizeof(medici) * NR_MEDICI);
    assert(medici->data != NULL);
    
    medici->last_index = -1;
    medici->size = NR_MEDICI;
    
    list_esubero *esuberi = (list_esubero *)malloc(sizeof(list_esubero));
    assert(esuberi != NULL);

    esuberi->data = NULL;
    esuberi->last_index = -1;
    esuberi->size = 0;

    return EXIT_SUCCESS;
}
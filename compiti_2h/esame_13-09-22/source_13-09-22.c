#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NR_MEDICI 200
#define EMPTY_STRING ""
#define NR_GIORNI 7
#define NR_TURNI 8

typedef struct singolo_turno {
    int id_turno;
    int pazienti_per_turno;

    struct singolo_turno *next;
} singolo_turno;

typedef struct medico {
    char id_medico[12 + 1];
    char reparto[30 + 1];
    singolo_turno *turni[NR_GIORNI];
} medico;

typedef struct list_medico {
    medico *data;
    int last_index;
    int size;
} list_medico;

typedef struct esubero {
    singolo_turno *turni[NR_GIORNI];
} esubero;

typedef struct list_esubero {
    esubero *data;
    int size;
    int last_index;
} list_esubero;

void aggiungi_medico(list_medico *medici, medico *med) 
{
    int first_index = medici->last_index + 1;
    if (first_index >= medici->size) return; /* se non posso aggiungere altri elementi, non faccio niente */   
    
    if (first_index == 0) /* se la lista è vuota, inserisco il medico e non faccio altro */
    {
        medici->data[first_index] = *med;
        medici->last_index = first_index;
        return;
    }

    for (int i = 0; i < first_index; i++) 
    {
        /* cerco la posizione in cui inserire il nuovo medico */
        if (strcmp(med->id_medico, medici->data[i].id_medico) < 0) 
        {
            /* shifto tutti gli altri medici di un posto a destra */
            for (int j = first_index; j >= i; j--) {
                medici->data[j] = medici->data[j - 1];
            }

            /* aggiungo il nuovo medico */
            medici->data[i] = *med;

            /* aggiorno l'indice dell'ultimo elemento presente nel vettore */
            medici->last_index = first_index;
            return;
        }
    }
}

medico *find_medico(list_medico *medici, char *id_medico) 
{
    for (int i = 0; i <= medici->last_index; i++) 
    {
        if (strcmp(medici->data[i].id_medico, id_medico) == 0) {
            return &medici->data[i];
        }
    }

    return NULL;
}

singolo_turno *find_turno(singolo_turno *turni, int giorno_richiesto, int turno_richiesto)
{
    for (int i = 0; i < NR_TURNI; i++) 
    {
        if (turni[giorno_richiesto - 1].id_turno == turno_richiesto)
            return &turni[giorno_richiesto - 1];
    }
    return NULL;
}

/* inserimento in coda */
void aggiungi_turno(singolo_turno **list, singolo_turno *turno) 
{
    if (*list == NULL)
    {
        turno->next = NULL;
        *list = turno;
        return;
    }

    singolo_turno *current_node = *list;
    singolo_turno *prev_node = NULL;

    /* scorro fino a fine lista */
    while (current_node != NULL) 
    {
        prev_node = current_node;
        current_node = current_node->next;
    }

    /* 
     * una volta uscito mi trovo con 'current_node' = NULL 
     * (elemento successivo all'ultimo elemento della lista)
     * e 'prev_node' = valore (ultimo elemento della lista)  
     */
    prev_node->next = turno;
}

esubero *find_esubero(esubero *esuberi, int giorno_richiesto, int turno_richiesto) 
{
    for (int i = 0; i < NR_TURNI; i++) 
    {
        if (esuberi->turni[giorno_richiesto - 1]->id_turno == turno_richiesto)
            return esuberi->turni[giorno_richiesto - 1];
    }

    return NULL;
}

esubero* leggi_appuntamenti(char *fileName, list_medico **medici) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    list_esubero *esuberi = (list_esubero *)malloc(sizeof(list_esubero));
    assert(esuberi != NULL);

    esuberi->data = NULL;
    esuberi->last_index = -1;
    esuberi->size = 0;

    while (!feof(pFile)) 
    {
        char id_medico[12 + 1];
        int turno_richiesto, giorno_richiesto;
        fscanf(pFile, "%*s %s %d %d", 
            id_medico, &turno_richiesto, &giorno_richiesto);

        medico *med = find_medico(*medici, id_medico);
        if (med == NULL) /* se il medico non esiste, allora lo creo */
        {
            med = (medico *)malloc(sizeof(medico));
            assert(med != NULL);

            strcpy(med->id_medico, id_medico);
            strcpy(med->reparto, EMPTY_STRING);

            for (int i = 0; i < NR_TURNI; i++) 
            {
                singolo_turno *new_turno = (singolo_turno *)malloc(sizeof(singolo_turno));
                assert(new_turno != NULL);
                new_turno->id_turno = i + 1;
                new_turno->pazienti_per_turno = 0;

                aggiungi_turno(&med->turni[giorno_richiesto - 1], new_turno);
            }
        }
        
        singolo_turno *turno = find_turno(med->turni, giorno_richiesto, turno_richiesto);
        assert(turno != NULL);

        /* se si crea un esubero, aggiungo il turno al vettore di output */
        if (turno->pazienti_per_turno + 1 >= 5) 
        {
            esuberi->size++;
            esuberi = (esubero *)realloc(esuberi, sizeof(esuberi) * esuberi->size);
            assert(esuberi != NULL);

            /* 
             * Comprensione del testo: se il testo mi chiede di avere un vettore di esuberi, in cui 
             * ciascuna posizione ha un vettore di 7 puntatori a singolo turno, concettualmente si può visualizzare
             * il vettore esuberi come raccolta di settimane, in cui ogni settimana contiene una matrice 7*8 (7 giorni, 8 turni per giorno)
             * di singolo_turno. Come posso ritrovare uno stesso turno andato in esubero più volte se manca un identificatore univoco di un singolo turno?
             * Vero è che un turno è identificato da id_turno (numero da 1 a 8), ma così facendo si ha turno 1-giorno 1-settimana 1, turno 1-giorno 1-settimana 2 ecc...
             * e quindi non basta. 
             * 
             * Enjoy the esubero!
             */
            esuberi->data[esuberi->last_index + 1].turni[giorno_richiesto] = turno;
            esuberi->last_index++;
        } 
        else 
        { /* altrimenti aggiungo il paziente al turno richiesto */
            turno->pazienti_per_turno++;
        }
    }
    
}

void stampa_esuberi(list_esubero *esuberi, int current_index) 
{
    /* se ho raggiunto la fine del vettore, termino la funzione */
    if (current_index > esuberi->last_index) return;

    /*
     * L'implementazione completa di questa funzione dipende dalla comprensione del testo e dalla 
     * soluzione del dubbio precedentemente esposto
     */

    stampa_esuberi(&esuberi[current_index + 1], current_index + 1);
}

float *occupazione_medico(list_medico *medici) 
{
    float *perc_occupazioni = (float *)malloc(sizeof(float) * (medici->last_index + 1));
    assert(perc_occupazioni != NULL);
    const int max_pazienti_per_week = 5 * NR_TURNI * NR_GIORNI; /* 5 pazienti x 8 turni al giorno x 7 giorni a settimana*/

    /* scorro tutti i medici */
    for (int i = 0; i <= medici->last_index; i++) 
    {
        int tot_pazienti_medico = 0;
        /* 
         * conto tutti i pazienti previsti nella settimana, analizzando giorno per 
         * giorno e, per ciascun giorno, turno per turno 
         */
        for (int idx_giorno = 0; idx_giorno < NR_GIORNI; idx_giorno++) 
        {
            singolo_turno *current_turno = medici->data[i].turni[idx_giorno];
            while (current_turno != NULL) 
            {
                tot_pazienti_medico += current_turno->pazienti_per_turno;
                current_turno = current_turno->next;
            }
        }

        perc_occupazioni[i] = (tot_pazienti_medico / max_pazienti_per_week) * 100;
    }
}

int main() 
{
    list_medico *medici = (list_medico *)malloc(sizeof(list_medico));
    assert(medici != NULL);

    medici->data = (medico *)malloc(sizeof(medico) * NR_MEDICI);
    assert(medici->data != NULL);
    medici->size = NR_MEDICI;
    medici->last_index = -1;

    list_esubero *esuberi = leggi_appuntamenti("appuntamenti.txt", &medici);
    stampa_esuberi(esuberi, 0);

    float *occupazioni = occupazione_medico(medici);
    
    return 0;
}
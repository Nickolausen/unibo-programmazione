#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h> /* NULL CHECK */

#define NR_AGENTI 100
#define DEFAULT_STRING ""

typedef struct Agente {
    char nome_e_cognome[70 + 1];
    char id_agente[10 + 1];
    int n_clienti_agente;

    /* Campi aggiuntivi */
    int n_clienti_unici_agente;
    struct Agente *next;
} Agente;

typedef struct List_Agente {
    Agente *data;
    int size;
    int last_index;
} List_Agente;

typedef struct Agente_Cliente {
    char id_agente[10 + 1];
    char id_cliente[10 + 1];

    struct Agente_Cliente *next;
} Agente_Cliente;

typedef struct Prestazione {
    char codice_richiesta_prestazione[15 + 1];
    Agente_Cliente *secondary_list;

    struct Prestazione *next;
} Prestazione;

void aggiungi_agente(List_Agente **vect, Agente *nuovo_agente) 
{
    /* NULL CHECK e controllo di poter aggiungere altri agenti al vettore - per non sforare la dimensione predefinita */
    assert(*vect != NULL && nuovo_agente != NULL && (*vect)->last_index + 1 < (*vect)->size);

    int first_index_available = (*vect)->last_index + 1;
    (*vect)->data[first_index_available] = *nuovo_agente;
    (*vect)->last_index = first_index_available;
}

void aggiungi_prestazione(Prestazione **list, Prestazione *nuova_prestazione) 
{
    assert(nuova_prestazione != NULL);

    /* HEAD INSERT */
    nuova_prestazione->next = *list;
    *list = nuova_prestazione;
}

void aggiungi_to_secondary_list(Agente_Cliente **list, Agente_Cliente *nuovo_elemento) 
{
    assert(nuovo_elemento != NULL);

    /* HEAD INSERT */
    nuovo_elemento->next = *list;
    *list = nuovo_elemento;
}

Agente_Cliente *find_in_secondary_list(Agente_Cliente *list, char *id_agente, char *id_cliente) 
{
    Agente_Cliente *current_node = list;
    while (current_node != NULL) 
    {
        if (strcmp(current_node->id_agente, id_agente) == 0 && 
            strcmp(current_node->id_cliente, id_cliente) == 0)
            return current_node;
        
        current_node = current_node->next;
    }

    return NULL;
}

Prestazione *find_prestazione(Prestazione *list, char *codice_richiesta_prestazione) 
{
    Prestazione *current_node = list;
    while (current_node != NULL) 
    {
        if (strcmp(current_node->codice_richiesta_prestazione, codice_richiesta_prestazione) == 0)
            return current_node;

        current_node = current_node->next;
    }

    return NULL;
}

Agente *find_agente_in_vettore(List_Agente* agenti, char *id_agente, int *idx_agente)
{
    for (int i = 0; i <= agenti->last_index; i++) 
    {
        if (strcmp(agenti->data[i].id_agente, id_agente) == 0) 
        {
            *idx_agente = i;
            return &agenti->data[i];
        }
    }

    return NULL;
}

Prestazione *leggi_appuntamenti(char *fileName, List_Agente **agenti) 
{
    Prestazione *out_list = NULL;
    Agente_Cliente *support_list = NULL;

    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL); /* NULL CHECK */

    while (!feof(pFile)) /* Ciclo finchè non ho raggiunto la fine del file */
    {
        char id_cliente[10 + 1], id_agente[10 + 1], codice_richiesta_prestazione[15 + 1];
        fscanf(pFile, "%s %s %s\n", id_cliente, id_agente, codice_richiesta_prestazione); /* Leggo un'intera riga del file */

        /* Cerco la prestazione corrente */
        Prestazione *current_prestazione = find_prestazione(out_list, codice_richiesta_prestazione);
        if (current_prestazione == NULL) /* Se non la trovo, la creo e la aggiungo nella lista */
        {
            current_prestazione = (Prestazione *)malloc(sizeof(Prestazione));
            assert(current_prestazione != NULL);

            strcpy(current_prestazione->codice_richiesta_prestazione, codice_richiesta_prestazione);
            current_prestazione->secondary_list = NULL;

            aggiungi_prestazione(&out_list, current_prestazione);
        }

        /* Cerco l'agente richiesto nell'appuntamento: se non esiste nel "database", lo aggiungo */
        int idx_agente = -1;
        Agente *current_agente = find_agente_in_vettore(*agenti, id_agente, &idx_agente);
        if (current_agente == NULL) 
        {
            current_agente = (Agente *)malloc(sizeof(Agente));
            assert(current_agente != NULL);

            strcpy(current_agente->id_agente, id_agente);
            strcpy(current_agente->nome_e_cognome, DEFAULT_STRING);
            current_agente->n_clienti_agente = 0;
            current_agente->n_clienti_unici_agente = 0;

            aggiungi_agente(agenti, current_agente);
            idx_agente = (*agenti)->last_index;
        }

        Agente_Cliente *new_el = (Agente_Cliente *)malloc(sizeof(Agente_Cliente));
        assert(new_el != NULL);
        strcpy(new_el->id_agente, id_agente);
        strcpy(new_el->id_cliente, id_cliente);

        aggiungi_to_secondary_list(&(current_prestazione->secondary_list), new_el);
        
        /* Conteggio clienti unici - (utile per funzione da 9 p.ti) */
        if (find_in_secondary_list(support_list, new_el->id_agente, id_cliente) == NULL) 
        {
            aggiungi_to_secondary_list(&support_list, new_el);
            (*agenti)->data[idx_agente].n_clienti_unici_agente++;
        }
        
        /* Aggiorno il numero di clienti per il determinato agente */
        (*agenti)->data[idx_agente].n_clienti_agente++;
    }
    
    return out_list;
}

void scorri_vettore(List_Agente *agenti, int idx) 
{
    if (idx > agenti->last_index) return;

    printf("[%d] ID: %s - Agente: %s\n", idx, agenti->data[idx].id_agente, agenti->data[idx].nome_e_cognome);
    printf("\tNumero clienti: %d\n", agenti->data[idx].n_clienti_agente);
    puts("");

    scorri_vettore(agenti, idx + 1);
}

Agente *find_agente_in_list(Agente *list, char *id_agente) 
{
    Agente *current_agente = list;
    while (current_agente != NULL) 
    {
        if (strcmp(current_agente->id_agente, id_agente) == 0)
            return current_agente;

        current_agente = current_agente->next;
    }

    return NULL;
}

void aggiungi_agente_visto(Agente **list, Agente *seen)
{
    assert(seen != NULL);
    seen->next = *list;
    *list = seen;
}

/* Parametro aggiuntivo di supporto per la stampa finale - per riutilizzare codice già scritto */
void premio_agente_anno(Prestazione *appuntamenti, List_Agente *vect) 
{
    /* 
     * Ragionamento step-by-step:
     * Poiché ho salvato nel vettore allocato dinamicamente il numero di clienti unici per ogni agente,
     * partendo dalla lista di liste 'appuntamenti' mi salvo in un vettore ausiliario 'agenti_n_clienti_unici'
     * le singole occorrenze di agente (se uno stesso agente compare più volte nella lista, comparirà una sola volta nel vettore)
     * 
     * La lista 'agenti_already_seen' mi permette di tracciare gli agenti che, iterazione dopo iterazione, compaiono.
     * 
     * Una volta ottenuto il vettore sostanzialmente 'copia' del vettore allocato dinamicamente nel main, lo ordino per
     * n_clienti_unici_agente in senso decrescente e stampo le prime tre posizioni
     * 
     * N.B.: Chiaramente lo stesso obiettivo sarebbe stato raggiungibile utilizzando solamente il vettore allocato dinamicamente
     * "agenti", ma la consegna richiede esplicitamente di avere e lavorare con la lista di liste costruita nella funzione 'leggi_appuntamenti'. 
     */

    const int length = vect->last_index + 1;

    Agente agenti_n_clienti_unici[length];
    int index_clienti_unici = 0;
    Agente *agenti_already_seen = NULL;

    Prestazione *current_prestazione = appuntamenti;
    while (current_prestazione != NULL) 
    {
        Agente_Cliente *current_pair = current_prestazione->secondary_list;
        while (current_pair != NULL) 
        {
            /* Parametro inutile in questo caso - necessario per chiamare una funzione già utilizzata in precedenza */
            int idx = -1;
            Agente *agente = find_agente_in_vettore(vect, current_pair->id_agente, &idx);
            Agente *agente_esistente = find_agente_in_list(agenti_already_seen, agente->id_agente); 
            if (agente_esistente == NULL) /* Se l'agente non era già comparso, allora lo aggiungo al vettore e alla lista di supporto */
            {
                agenti_n_clienti_unici[index_clienti_unici++] = *agente;
                aggiungi_agente_visto(&agenti_already_seen, agente);
            }

            current_pair = current_pair->next;
        }

        current_prestazione = current_prestazione->next;
    }

    /* Ordinamento vettore - ordine decrescente */
    bool swapping = true;
    while (swapping)
    {
        swapping = false;
        for (int i = 0; i < length - 1; i++) 
        {
            Agente swapEl;
            if (agenti_n_clienti_unici[i].n_clienti_unici_agente < agenti_n_clienti_unici[i + 1].n_clienti_unici_agente) 
            {   
                swapping = true;

                swapEl = agenti_n_clienti_unici[i];
                agenti_n_clienti_unici[i] = agenti_n_clienti_unici[i + 1];
                agenti_n_clienti_unici[i + 1] = swapEl;
            }
        }
    }

    printf("Classifica agenti: \n");
    printf("\t[1*] %s - nr_client_unici: %d\n", agenti_n_clienti_unici[0].id_agente, agenti_n_clienti_unici[0].n_clienti_unici_agente);
    printf("\t[2*] %s - nr_client_unici: %d\n", agenti_n_clienti_unici[1].id_agente, agenti_n_clienti_unici[1].n_clienti_unici_agente);
    printf("\t[3*] %s - nr_client_unici: %d\n", agenti_n_clienti_unici[2].id_agente, agenti_n_clienti_unici[2].n_clienti_unici_agente);
}

int main() 
{
    List_Agente *agenti = (List_Agente *)malloc(sizeof(List_Agente));
    assert(agenti != NULL); /* NULL check */
    
    /* Vettore allocato dinamicamente - salvato in una struttura "di supporto" per memorizzare informazioni aggiuntive */
    agenti->data =  (Agente *)malloc(sizeof(Agente) * NR_AGENTI);
    assert(agenti->data != NULL); /* NULL check */
    agenti->last_index = -1;
    agenti->size = NR_AGENTI;

    Prestazione *appuntamenti = leggi_appuntamenti("appuntamenti.txt", &agenti);
    scorri_vettore(agenti, 0);

    premio_agente_anno(appuntamenti, agenti);

    return EXIT_SUCCESS;
}
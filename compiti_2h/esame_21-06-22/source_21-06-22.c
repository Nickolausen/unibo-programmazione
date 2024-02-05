#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h> /* NULL check */

#define N_NOMI_AGENTI 100
#define N_PRESTAZIONI 100

typedef struct appuntamento {
    char id_cliente[10 + 1];
    char id_agente[10 + 1];
    char codice_richiesta_prestazione[15 + 1];

    struct appuntamento *next;
} appuntamento;

typedef struct agente {
    char nome_e_cognome[70 + 1];
    char id_agente[10 + 1];
    appuntamento *appuntamenti;
    int nr_clienti;

    struct agente *next;
} agente;

typedef struct agente_nomi {
    char id_agente[10 + 1];
    char nome_e_cognome[70 + 1];
} agente_nomi;

agente *find_agente(agente *list, char *id_agente) 
{
    agente *current_node = list;
    while (current_node != NULL) 
    {
        if (strcmp(current_node->id_agente, id_agente) == 0)
            return current_node;
        
        current_node = current_node->next;
    }
    
    return NULL;
}

void aggiungi_agente(agente **list, agente *nuovo_agente) 
{
    assert(nuovo_agente != NULL);

    nuovo_agente->next = *list;
    *list = nuovo_agente;
}

char *get_nome_agente(agente_nomi *id_nomi_agenti, char *id_agente) 
{
    for (int i = 0; i < N_NOMI_AGENTI; i++) 
    {
        if (strcmp(id_nomi_agenti[i].id_agente, id_agente) == 0)
            return id_nomi_agenti[i].nome_e_cognome;
    }

    return NULL;
}

void inserisci_appuntamento(appuntamento **list, appuntamento *app)
{
    /* se la lista è vuota, inserisco l'appuntamento e non faccio altro */
    if (*list == NULL) 
    {
        app->next = *list;
        *list = app;
        return;
    }

    appuntamento *current_appuntamento = *list;
    appuntamento *prev_appuntamento = NULL;
    bool found = false;

    /* scorrimento della lista di appuntamenti */
    while (current_appuntamento != NULL) 
    {
        if (strcmp(current_appuntamento->id_cliente, app->id_cliente) == 0) 
        {
            found = true;
            break;
        }
        
        prev_appuntamento = current_appuntamento;
        current_appuntamento = current_appuntamento->next; 
    }

    /* se ho trovato il cliente in lista, allora memorizzo il nuovo appuntamento con lo stesso cliente nella posizione adiacente */
    if (found) {
        prev_appuntamento->next = app;
        app->next = current_appuntamento;
        return;
    }

    /* altrimenti faccio un inserimento in testa */
    app->next = *list;
    *list = app;
}

agente *leggi_appuntamenti(char *fileName, agente_nomi *id_nomi_agenti) 
{
    agente *out_list = NULL;
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL); /* NULL check */

    while (!feof(pFile)) /* Scorro finché non ho raggiunto la fine del file */ 
    {
        char id_cliente[10 + 1], id_agente[10 + 1], codice_richiesta_prestazione[15 + 1];
        fscanf(pFile, "%s %s %s\n", id_cliente, id_agente, codice_richiesta_prestazione);

        /* Cerco l'agente in lista - se non lo trovo, lo creo e lo aggiungo */
        agente *agent = find_agente(out_list, id_agente);
        if (agent == NULL) 
        {
            agent = (agente *)malloc(sizeof(agente));
            assert(agent != NULL);

            strcpy(agent->id_agente, id_agente);
            strcpy(agent->nome_e_cognome, get_nome_agente(id_nomi_agenti, id_agente));

            agent->nr_clienti = 0;
            agent->appuntamenti = NULL;
            agent->next = NULL;
            aggiungi_agente(&out_list, agent);
        }

        appuntamento *app = (appuntamento *)malloc(sizeof(appuntamento));
        assert(app != NULL);
        strcpy(app->id_cliente, id_cliente);
        strcpy(app->codice_richiesta_prestazione, codice_richiesta_prestazione);
        strcpy(app->id_agente, id_agente);

        inserisci_appuntamento(&(agent->appuntamenti), app);
    }

    return out_list;
}

void stampa_agenti(agente *agenti) 
{
    if (agenti == NULL) return;

    printf("Agente: %s - #%s\n", agenti->nome_e_cognome, agenti->id_agente);
    printf("Appuntamenti in agenda:\n");

    appuntamento *current_appuntamento = agenti->appuntamenti;
    while (current_appuntamento != NULL) 
    {
        printf("\tCliente: %s - Prestazione: %s\n", current_appuntamento->id_cliente, current_appuntamento->codice_richiesta_prestazione);
        current_appuntamento = current_appuntamento->next;
    }

    puts("");

    stampa_agenti(agenti->next);
}

void priority_insert(agente **list, agente *element) 
{
    if (*list == NULL) 
    {
        *list = element;
        return;
    }

    agente *current_node = *list;
    agente *prev_node = NULL;

    while (current_node != NULL) 
    {
        if (current_node->nr_clienti > element->nr_clienti) 
            break;
        
        prev_node = current_node;
        current_node = current_node->next;
    }

    if (prev_node == NULL) 
    {
        current_node->next = element; 
        return;
    }

    prev_node->next = element;
    element->next = current_node;
}

/* Manca comprensione del testo - da sistemare */
void premio_agente_anno(agente *agenti) 
{
    agente *ranking = NULL;

    agente *current_agente = agenti;
    while (current_agente != NULL) 
    {
        appuntamento *current_appuntamento = current_agente->appuntamenti;
        appuntamento *prev_appuntamento = NULL;
        
        while (current_appuntamento != NULL) 
        {
            if (prev_appuntamento != NULL 
                && strcmp(current_appuntamento->id_cliente, prev_appuntamento->id_cliente) == 0)
            {
                current_agente->nr_clienti++;
            }

            prev_appuntamento = current_appuntamento;
            current_appuntamento = current_appuntamento->next;
        }

        current_agente = current_agente->next;
    }
}

int main() 
{
    agente_nomi id_nomi_agenti[N_NOMI_AGENTI];
    id_nomi_agenti[0] = (agente_nomi){"10021", "Giacomo Leopardi"};
    id_nomi_agenti[1] = (agente_nomi){"10034", "Francesco Baluardo"};
    id_nomi_agenti[2] = (agente_nomi){"10051", "Davide Bonaparte"};
    // [...]

    agente *agenti = leggi_appuntamenti("appuntamenti.txt", id_nomi_agenti);
    stampa_agenti(agenti);

    return EXIT_SUCCESS;
}
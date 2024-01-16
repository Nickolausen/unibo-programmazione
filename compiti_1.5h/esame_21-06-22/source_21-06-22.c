#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define COUNT_NOMI_AGENTI 100

typedef struct appuntamento {
    char id_cliente[10 + 1];
    char id_agente[10 + 1];
    char codice_richiesta_prestazione[15 + 1];

    struct appuntamento *next;
} appuntamento;

typedef struct appuntamento *appuntamenti;

typedef struct agente {
    char nome_e_cognome[70 + 1];
    char id_agente[10 + 1];
    int n_clienti_agente;
    appuntamenti appuntamenti;

    struct agente *next;
} agente;

typedef struct agente_nome {
    char nome_e_cognome[70 + 1];
    char id_agente[10 + 1];
} agente_nome;

typedef struct list_agente_nome {
    agente_nome vector[COUNT_NOMI_AGENTI];
    int size;
    int lastIndex;
} list_agente_nome;

/* Ordina il vettore per id_agente crescente */
void sort_by_ascending(list_agente_nome **list) 
{
    bool swapping = true;
    while (swapping) 
    {
        swapping = false;
        for (int i = 0; i <= (*list)->lastIndex; i++) 
        {
            agente_nome swap;
            if (strcmp((*list)->vector[i].id_agente, (*list)->vector[i + 1].id_agente) > 0) 
            {
                swapping = true;
                swap = (*list)->vector[i];
                (*list)->vector[i] = (*list)->vector[i + 1];
                (*list)->vector[i + 1] = swap; 
            }
        }
    }
}

void head_insert(agente **list, agente *node) 
{
    if (node == NULL) return;

    (*list)->next = node->next;
    node = *list;
}

agente* leggi_appuntamenti(char *fileName) 
{
    agente* lista_agenti = NULL;
    FILE* pFile = fopen(fileName, "r");
    if (pFile == NULL) {
        printf("Could not open '%s'. Exiting...", fileName);
        return;
    }

    list_agente_nome *id_nomi_agenti = (list_agente_nome *)malloc(sizeof(list_agente_nome));
    if (id_nomi_agenti == NULL) return;

    id_nomi_agenti->lastIndex = -1;
    id_nomi_agenti->size = COUNT_NOMI_AGENTI;

    for (int i = 0; i < COUNT_NOMI_AGENTI; i++) 
    {
        /* DA CONTINUARE... */
    }

    while (!feof(pFile)) 
    {
        agente *ag;
        char id_cliente[10 + 1], id_agente[10 + 1], codice_prestazione[15 + 1];
        
        /* Leggo l'intera riga e passo immediatamente a quella successiva */
        fscanf(pFile, "%s %s %s\n", id_cliente, id_agente, codice_prestazione);

        /*
            [...]
        */
       
        head_insert(&lista_agenti, ag);
    }

    fclose(pFile);
    return NULL;
}

void stampa_agenti(agente *list) 
{
    if (list == NULL) return;

    printf("Agente: %s, codice identificativo #%s\n", list->nome_e_cognome, list->id_agente);
    printf("> Clienti raggiunti: %d\n", list->n_clienti_agente);

    appuntamento *current_appuntamento = list->appuntamenti;

    int idxAppuntamento = 0;
    while (current_appuntamento != NULL) 
    {
        printf("[%d]\t ID cliente: %s - Codice prestazione richiesta: %s\n", 
            idxAppuntamento++ + 1,
            current_appuntamento->id_cliente,
            current_appuntamento->codice_richiesta_prestazione);
        
        current_appuntamento = current_appuntamento->next;
    }

    puts("");
    stampa_agenti(list->next);
}

int main() 
{

    return 0;
}
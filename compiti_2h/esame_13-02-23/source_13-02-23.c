#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

typedef struct Prodotto {
    int id_prodotto;
    char descrizione[100 + 1];
    float prezzo;
    int disponibilita_residua;
    int codice_errore;
} Prodotto;

typedef struct Ordine {
    int id_prodotto;
    int quantita;
    struct Ordine *next;
} Ordine;

typedef struct OrdineCliente {
    char nome_e_cognome[70 + 1];
    char indirizzo[70 + 1];
    Ordine *prodotti_ordinati;
    struct OrdineCliente *next; 
} OrdineCliente;

OrdineCliente *find_cliente(OrdineCliente *list, char *nome_e_cognome, char *indirizzo) 
{
    OrdineCliente *current_node = list;
    while (current_node != NULL) 
    {
        if (strcmp(current_node->nome_e_cognome, nome_e_cognome) == 0 &&
            strcmp(current_node->indirizzo, indirizzo) == 0)
            return current_node;

        current_node = current_node->next;
    }

    return NULL;
}

Ordine *find_ordine(Ordine *list, int id_prodotto) 
{
    Ordine *current_node = list;

    while (current_node != NULL) 
    {   
        if (current_node->id_prodotto == id_prodotto)
            return current_node;
        
        current_node = current_node->next;
    }

    return NULL;
}

void head_insert_ordini(Ordine **list, Ordine *ord)
{
    assert(ord != NULL);

    ord->next = *list;
    *list = ord;
}

void head_insert_ordini_clienti(OrdineCliente **list, OrdineCliente *ord_cliente)
{
    assert(ord_cliente != NULL);

    ord_cliente->next = *list;
    *list = ord_cliente;
}

OrdineCliente *leggi_ordini(char *fileName) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    OrdineCliente *out_list = NULL;

    while (!feof(pFile)) 
    {
        char nome[70 + 1], cognome[70 + 1], nome_e_cognome[70 + 1], indirizzo[70 + 1];
        fscanf(pFile, "%s %s %s", nome, cognome, indirizzo);

        /* Unisco nome e cognome in un unica variabile - poiché da file li leggo separati da uno spazio */
        snprintf(nome_e_cognome, 70, "%s %s", nome, cognome);

        /* cerco il cliente qualora avesse già fatto degli ordini prima - era già nella lista */
        OrdineCliente *cliente = find_cliente(out_list, nome_e_cognome, indirizzo);
        if (cliente == NULL) /* se non lo trovo, lo creo */
        {
            cliente = (OrdineCliente *)malloc(sizeof(OrdineCliente));
            assert(cliente != NULL);

            strcpy(cliente->nome_e_cognome, nome_e_cognome);
            strcpy(cliente->indirizzo, indirizzo);
            cliente->prodotti_ordinati = NULL;
        }

        while (fgetc(pFile) == ' ') 
        {

        }
    }

    fclose(pFile);
    return out_list;
}

int main() 
{
    return 0;
}
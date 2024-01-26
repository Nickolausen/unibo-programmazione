#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define NR_PRODOTTI_CATALOGO 300

typedef struct Prodotto {
    int id_prodotto;
    char descrizione[100 + 1];
    float prezzo;
    int disponibilita_residua;
    int codice_errore;
} Prodotto;

typedef struct ListProdotto {
    Prodotto *data;
    int size;
    int lastIndex;
} ListProdotto;

typedef struct Ordine {
    int id_prodotto;
    int quantita;
    struct Ordine *next;
} Ordine;

typedef struct Cliente {
    char nome_e_cognome[70 + 1];
    char indirizzo[70 + 1];
    Ordine *prodotti_ordinati;
    struct Cliente *next; 
} Cliente;

void insert_prodotto(ListProdotto *catalogo, Prodotto *prodotto) 
{
    if ((catalogo)->lastIndex == -1) 
    {
        catalogo->data[catalogo->lastIndex + 1] = *prodotto;
        catalogo->lastIndex++;
        return;
    }

    /* prima di fare qualsiasi cosa, mi assicuro di poter aggiungere altri elementi al vettore */
    assert(catalogo->lastIndex + 1 < catalogo->size);

    for (int i = 0; i <= catalogo->lastIndex; i++) 
    {
        /* trovo la posizione in cui inserire il nuovo prodotto in catalogo */
        if (prodotto->id_prodotto > catalogo->data[i].id_prodotto) 
        {
            /* shifto tutti gli elementi a destra di una posizione */
            for (int j = catalogo->lastIndex + 1; j > i; j--) 
            {
                catalogo->data[j] = (catalogo)->data[j - 1];
            }

            /* inserisco il prodotto e aggiorno l'indice dell'ultimo elemento inserito */
            catalogo->data[i] = *prodotto;
            catalogo->lastIndex++;
            return;
        }
    }
}

int find_index_prodotto(ListProdotto *catalogo, int id_prodotto) 
{
    for (int i = 0; i <= catalogo->lastIndex; i++) 
    {
        if (catalogo->data[i].id_prodotto == id_prodotto)
            return i;
    }

    return -1;
}

Cliente *find_cliente(Cliente *list, char *nome_e_cognome, char *indirizzo) 
{
    Cliente *current_node = list;
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

void head_insert_ordini_clienti(Cliente **list, Cliente *ord_cliente)
{
    assert(ord_cliente != NULL);

    ord_cliente->next = *list;
    *list = ord_cliente;
}

Cliente *leggi_ordini(char *fileName, ListProdotto *catalogo) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    Cliente *out_list = NULL;

    while (!feof(pFile)) 
    {
        char nome[70 + 1], cognome[70 + 1], nome_e_cognome[70 + 1], indirizzo[70 + 1];
        fscanf(pFile, "%s %s %s", nome, cognome, indirizzo);

        /* Unisco nome e cognome in un unica variabile - poiché da file li leggo separati da uno spazio */
        snprintf(nome_e_cognome, 70, "%s %s", nome, cognome);

        /* cerco il cliente qualora avesse già fatto degli ordini prima - era già nella lista */
        Cliente *cliente = find_cliente(out_list, nome_e_cognome, indirizzo);
        if (cliente == NULL) /* se non lo trovo, lo creo */
        {
            cliente = (Cliente *)malloc(sizeof(Cliente));
            assert(cliente != NULL);

            strcpy(cliente->nome_e_cognome, nome_e_cognome);
            strcpy(cliente->indirizzo, indirizzo);
            cliente->prodotti_ordinati = NULL;
            head_insert_ordini_clienti(&out_list, cliente);
        }

        /* leggo tutti gli ordini del cliente */
        while (fgetc(pFile) == ' ') 
        {
            int id_prodotto, quantita;
            fscanf(pFile, "%d %d", &id_prodotto, &quantita);

            int idx_prod_ordinato = find_index_prodotto(catalogo, id_prodotto);
            if (idx_prod_ordinato == -1) 
            {
                printf("Prodotto non presente in catalogo!\n");
                continue;
            }

            Prodotto prod_ordinato = catalogo->data[idx_prod_ordinato];

            /* cerco l'ordine del cliente tra quelli già presenti in lista */
            Ordine *ord = find_ordine(cliente->prodotti_ordinati, id_prodotto);
            if (ord == NULL) /* se non lo trovo, lo creo */
            {
                ord = (Ordine *)malloc(sizeof(Ordine));
                assert(ord != NULL);

                ord->id_prodotto = id_prodotto;
                head_insert_ordini(&cliente->prodotti_ordinati, ord);
            }

            /* se la quantità richiesta eccede la disponibilità in magazzino, allora aggiorno il codice errore */
            if (quantita > prod_ordinato.disponibilita_residua) 
            {
                catalogo->data[idx_prod_ordinato].codice_errore = 1;
                ord->quantita = catalogo->data[idx_prod_ordinato].disponibilita_residua;
                catalogo->data[idx_prod_ordinato].disponibilita_residua = 0;
            }
            else 
            {
                ord->quantita = quantita;
            }

        }
    }

    fclose(pFile);
    return out_list;
}

bool already_seen(int id_prodotti[], int id_prodotto, int lastIndex) 
{
    for (int i = 0; i <= lastIndex; i++) 
    {
        if (id_prodotti[i] == id_prodotto)
            return true;
    }

    return false;
}

void insert_by_descending(Ordine **list, Ordine *ord) 
{
    Ordine *current_node = *list;

    while (current_node->quantita > ord->quantita) {
        current_node = current_node->next;
    }

    ord->next = current_node->next;
    current_node->next = ord;
}

Ordine *ordina_prodotti(Cliente *list, ListProdotto *prodotti)
{
    Ordine *new_list = NULL;

    int idxFlag = 0;
    int prod_gia_visti[NR_PRODOTTI_CATALOGO];

    for (int i = 0; i <= prodotti->lastIndex; i++) 
    {
        int current_prod_id = prodotti->data[i].id_prodotto;
        if (already_seen(prod_gia_visti, current_prod_id, idxFlag))
            continue;

        Cliente *current_cliente = list;
        Ordine sum = {current_prod_id, 0};

        /* controllo per tutti i clienti che hanno fatto un ordine */
        while (current_cliente != NULL) 
        {
            /* tutti gli ordini di ciascun cliente */
            Ordine *ordini = current_cliente->prodotti_ordinati;
            while (ordini != NULL) 
            {
                if (ordini->id_prodotto == current_prod_id) {
                    sum.quantita += ordini->quantita;
                }

                ordini = ordini->next;
            }

            current_cliente = current_cliente->next;
        }

        /* inserisco il prodotto solo se effettivamente ordinato */
        if (sum.quantita != 0) {
            insert_by_descending(&new_list, &sum);
        }
        
        prod_gia_visti[idxFlag++] = current_prod_id;
    }

    return new_list;
}

int main() 
{
    ListProdotto *Prodotti = (ListProdotto *)malloc(sizeof(ListProdotto));
    assert(Prodotti != NULL);

    Prodotti->data = (Prodotto *)malloc(sizeof(Prodotto) * NR_PRODOTTI_CATALOGO);
    assert(Prodotti->data != NULL);

    Prodotti->lastIndex = -1;
    Prodotti->size = NR_PRODOTTI_CATALOGO;

    Cliente *ordini_clienti = leggi_ordini("ordini.txt", Prodotti);
    Ordine *ordered_ordini = ordina_prodotti(ordini_clienti, Prodotti);
    return 0;
}
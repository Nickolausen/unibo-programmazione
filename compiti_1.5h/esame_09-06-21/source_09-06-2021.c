#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_PRODOTTI 150
#define MAX_ORDINI 15

typedef struct Prodotto {
    int id_prodotto;
    char descrizione[100 + 1];
    float prezzo;
    int disponibilita_residua;
    int codice_errore;
} Prodotto;

typedef struct ListProdotto {
    Prodotto data[MAX_PRODOTTI];
    int count;
    int lastIndex;
} ListProdotto;

typedef struct Ordine {
    int id_prodotto;
    int quantita;
} Ordine;

typedef struct OrdiniClienti {
    char nome_e_cognome[70 + 1];
    char indirizzo[70 + 1];
    Ordine prodotti_ordinati[MAX_ORDINI];
    int nr_prodotti;

    struct OrdiniClienti *next;
} OrdiniClienti;

void check_malloc(void *ptr) 
{
    if (ptr == NULL) 
    {
        printf("Errore nell'allocazione della memoria.");
        exit(EXIT_FAILURE);
    }
}

void sort_by_id(ListProdotto **vect) 
{
    if ((*vect)->count == 1) return;

    bool swapping = true;
    while (swapping) 
    {
        swapping = false;
        for (int i = 0; i < (*vect)->lastIndex; i++) 
        {
            Prodotto *swapEl;
            if ((*vect)->data[i].id_prodotto > (*vect)->data[i + 1].id_prodotto) 
            {
                swapping = true;
                swapEl = &(*vect)->data[i];
                (*vect)->data[i] = (*vect)->data[i + 1];
                (*vect)->data[i] = *swapEl;
            }
        }
    }
}

void aggiungi_prodotto(ListProdotto *list, Prodotto prod) 
{
    int firstFreeIndex = list->lastIndex + 1;

    if (firstFreeIndex < list->count) 
    {
        printf("Non posso memorizzare altri prodotti. Massimo raggiunto.\n");
        return;
    }

    list->data[firstFreeIndex] = prod;
    list->count++;
    list->lastIndex = firstFreeIndex;

    sort_by_id(&list);
}

Ordine *get_prodotto_by_id(Ordine *lista_ordini[MAX_ORDINI], int nr_prodotti, int id_prodotto) 
{
    for (int i = 0; i < nr_prodotti; i++) 
    {
        if (lista_ordini[i]->id_prodotto == id_prodotto) 
            return lista_ordini[i];
    }

    return NULL;
}

OrdiniClienti *get_cliente_by_nome(OrdiniClienti *list, char *nome_e_cognome)
{
    OrdiniClienti *current_node = list;
    while (current_node != NULL) 
    {
        if (strcmp(current_node->nome_e_cognome, nome_e_cognome) == 0) return current_node;

        current_node = current_node->next;
    }

    return NULL;
}

OrdiniClienti *leggi_ordini(char* fileName) 
{
    OrdiniClienti *out_list = NULL;
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) 
    {
        printf("Non riesco ad aprire '%s'. Uscendo...", fileName);
        exit(EXIT_FAILURE);
    }

    while (!feof(pFile)) 
    {
        OrdiniClienti *ordine;
        if (ordine == NULL) return NULL;

        char tmpNome[70 + 1], tmpCognome[70 + 1], indirizzo[70 + 1], nome_e_cognome[70 + 1];
        fscanf(pFile, "%s %s %s", tmpNome, tmpCognome, indirizzo);

        ordine = get_cliente_by_nome(out_list, nome_e_cognome); /* Cerco il cliente appena letto */
        if (ordine == NULL) /* Se non esiste, lo creo */
        {
            ordine = (OrdiniClienti *)malloc(sizeof(OrdiniClienti));
            strcpy(ordine->nome_e_cognome, nome_e_cognome);
            strcpy(ordine->indirizzo, indirizzo);
        }

        while (fgetc(pFile) == ' ') 
        {
            int id_prodotto, quantita;
            fscanf(pFile, "%d %d", &id_prodotto, &quantita);

            Ordine *prodotto_ordinato = get_prodotto_by_id(ordine->prodotti_ordinati, ordine->nr_prodotti, id_prodotto);
            if (prodotto_ordinato == NULL) 
            {
                prodotto_ordinato = (Ordine *)malloc(sizeof(Ordine));
                check_malloc(prodotto_ordinato);

                
            }
        }
    }

    return out_list;
}

void stampa_lista(OrdiniClienti *list) 
{
    if (list == NULL) return;
    printf("Cliente: %s\t Residenza: %s", list->nome_e_cognome, list->indirizzo);
    
    for (int i = 0; i < list->nr_prodotti; i++) {
        printf("Prodotto [%d] - Q.ta: [%d]\n",  list->prodotti_ordinati[i].id_prodotto, 
            list->prodotti_ordinati[i].quantita);
    }

    puts("");
    stampa_lista(list->next);
}

int main() 
{
    ListProdotto *Prodotti = (ListProdotto *)malloc(sizeof(ListProdotto));
    Prodotti->count = 0;
    Prodotti->lastIndex = -1;

    aggiungi_prodotto(Prodotti, (Prodotto){3256, "Shampoo", 35.50, 50, 0});
    aggiungi_prodotto(Prodotti, (Prodotto){5234, "Bagnoschiuma", 50.50, 4, 0});
    aggiungi_prodotto(Prodotti, (Prodotto){2323, "Patatine", 5.50, 2, 0});
    aggiungi_prodotto(Prodotti, (Prodotto){2356, "Pesce", 21.50, 50, 0});
    aggiungi_prodotto(Prodotti, (Prodotto){7689, "Carne", 45.30, 10, 0});
    aggiungi_prodotto(Prodotti, (Prodotto){7689, "Lego", 45.30, 3, 0});

    
    return 0;
}
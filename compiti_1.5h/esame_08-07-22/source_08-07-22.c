#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define NR_PRODOTTI_CATALOGO 200

typedef struct prodotto {
    int codice_prodotto;
    int codice_fornitore;
    int quantita_presente;

    /* Linked List */
    struct prodotto *next;
} prodotto;

typedef struct prodotto_catalogo {
    int codice_prodotto;
    float prezzo_unitario;
    int codice_fornitore;
    int quantita_minima;
} prodotto_catalogo;

typedef struct supermercato {
    int codice_supermercato;
    prodotto *prodotti;

    /* Linked List */
    struct supermercato *next;
} supermercato;

/* Inserimento ordinato */
void inserisci_prodotto_supermercato(prodotto **list, prodotto *prod) 
{
    /* Mi assicuro di non star inserendo un elemento vuoto */
    assert(prod != NULL);

    /* 
     * Se la lista è vuota, inserisco il nuovo prodotto in 
     * testa e non faccio altro 
     */
    if (*list == NULL) 
    {
        prod->next = *list;
        *list = prod;

        return;
    }

    /* Nello scorrimento della lista salvo l'elemento corrente e il suo precedente */
    prodotto *current_prodotto = *list;
    prodotto *prev_prodotto = NULL;

    while (current_prodotto != NULL) 
    {
        /* Cerco la posizione in cui inserire il nuovo prodotto */
        if (current_prodotto->codice_prodotto < prod->codice_prodotto || 
            (current_prodotto->codice_prodotto == prod->codice_prodotto && current_prodotto->codice_fornitore < prod->codice_fornitore)) 
        {
            break;
        }

        prev_prodotto = current_prodotto;
        current_prodotto = current_prodotto->next;
    }

    /* inserimento in coda */
    if (prev_prodotto == NULL) 
    {
        current_prodotto->next = prod;
    } 
    else 
    {
        /* inserisco l'elemento all'interno della lista */
        prod->next = current_prodotto;
        prev_prodotto->next = prod;
    } 
}

/* Inserimento ordinato */
void inserisci_prodotto_catalogo(prodotto_catalogo *vect, prodotto_catalogo *prod) 
{
    /* Mi assicuro di non star inserendo un elemento vuoto */
    assert(prod != NULL);

    for (int i = 0; i < NR_PRODOTTI_CATALOGO; i++) 
    {
        if (prod->codice_prodotto < vect[i].codice_prodotto || 
            (prod->codice_prodotto == vect[i].codice_prodotto && prod->codice_fornitore < vect[i].codice_fornitore)) 
        {
            /* shifto tutti gli elementi a destra di 1 */
            for (int j = NR_PRODOTTI_CATALOGO; j > i; j--) {
                vect[j] = vect[j - 1];
            }

            /* inserisco il nuovo elemento nella posizione liberata */
            vect[i] = *prod;

            /* inserimento avvenuto, esco dalla funzione */
            return;
        }
    }
}

/* inserimento in testa di nuovi supermercati alla lista di supermercati */
void aggiungi_supermercati(supermercato **list, supermercato *el) 
{
    assert(el != NULL);

    el->next = *list;
    *list = el;
}

supermercato *find_supermercato(supermercato *list, int codice_supermercato) 
{
    supermercato *current_node = list;
    while (current_node != NULL) 
    {
        if (current_node->codice_supermercato == codice_supermercato)
            return current_node;
        
        current_node = current_node->next;
    }

    return NULL;
}

prodotto_catalogo find_in_catalogo(prodotto *prod, prodotto_catalogo *listino) 
{
    prodotto_catalogo output;
    for (int i = 0; i < NR_PRODOTTI_CATALOGO; i++) 
    {
        if (listino[i].codice_prodotto == prod->codice_prodotto)
            output = listino[i];
    }

    return output;
}

prodotto *find_prodotto(prodotto *list, int codice_prodotto) 
{
    prodotto *current_node = list;
    while (current_node != NULL) 
    {
        if (current_node->codice_prodotto == codice_prodotto)
            return current_node;
        
        current_node = current_node->next;
    }
    return NULL;
}

void chiudi_supermercato(supermercato **list, int codice_supermercato, int secondo_supermercato) 
{
    supermercato *current_node = *list;
    supermercato *prev_node = NULL;

    prodotto *elenco_prodotti_da_trasferire = NULL;

    while (current_node != NULL) 
    {
        if (current_node->codice_supermercato == codice_supermercato)
        {
            /* 
             * se ho trovato il supermercato ricercato, 
             * inizio a trasferire i prodotti nel secondo supermercato 
             */

            supermercato *secondo_market = find_supermercato(*list, secondo_supermercato);
            
            /* mi assicuro che esista il secondo supermercato, altrimenti esco dal programma */
            assert(secondo_market != NULL);

            prodotto *current_prodotto = current_node->prodotti;
            while (current_prodotto != NULL) /* trasferisco ogni prodotto nel secondo supermercato */
            {
                prodotto *corrispondente = find_prodotto(secondo_market->prodotti, current_prodotto->codice_prodotto);
                if (corrispondente == NULL) /* se il secondo supermercato non dispone già del prodotto, glielo aggiungo */
                {
                    inserisci_prodotto_supermercato(&secondo_market->prodotti, current_prodotto);
                }
                else
                {
                    /* altrimenti aggiungo la quantità del prodotto presente nel supermercato da chiudere alla quantità di prodotto presente nel secondo supermercato */
                    corrispondente->quantita_presente += current_prodotto->quantita_presente;
                }

                current_prodotto = current_prodotto->next;
            }

            break;
        }

        prev_node = current_node;
        current_node = current_node->next;
    }

    prev_node->next = current_node->next;
    free(current_node); /* elimino il supermercato dalla lista */
}

void stampa_prodotti_in_esaurimento(supermercato *elenco_supermercati, int codice_supermercato, prodotto_catalogo *listino)
{
    supermercato *target = find_supermercato(elenco_supermercati, codice_supermercato);
    assert(target != NULL);

    printf("%d - Prodotti in esaurimento\n", target->codice_supermercato);
    prodotto *current_prodotto = target->prodotti;
    while (current_prodotto != NULL) 
    {
        prodotto_catalogo in_catalogo = find_in_catalogo(current_prodotto, listino);
        if (current_prodotto->quantita_presente < in_catalogo.quantita_minima) 
        {
            printf("\tProdotto ID: %d\n", current_prodotto->codice_prodotto);
            printf("\tFornito da ID: %d\n", current_prodotto->codice_fornitore);
            printf("\tQuantita residua: %d - (prevista %d)\n", current_prodotto->quantita_presente, in_catalogo.quantita_minima);
        }
        puts("---");

        current_prodotto = current_prodotto->next;
    }
}

int miglior_supermercato(supermercato *elenco_supermercati, prodotto_catalogo *listino_prodotti) 
{
    int cod_migliore = -1;
    float valore_massimo = -1;

    supermercato *current_supermercato = elenco_supermercati;
    while (current_supermercato != NULL) /* scorro tutti i supermercati */
    {
        prodotto *current_prodotto = current_supermercato->prodotti;
        float valore_market = 0; /* somma di tutti i prezzi presenti nel supermercato */

        while (current_prodotto != NULL) /* scorro tutti i prodotti del supermercato */
        {
            prodotto_catalogo in_catalogo = find_in_catalogo(current_prodotto, listino_prodotti); /* cerco il corrispettivo prodotto nel catalogo */
            valore_market += in_catalogo.prezzo_unitario * current_prodotto->quantita_presente; /* aggiungo il suo valore alla sommatoria */

            current_prodotto = current_prodotto->next;
        }

        if (valore_market > valore_massimo) /* salvo il valore massimo e il corrispondente codice supermercato che me l'ha generato */
        {
            valore_massimo = valore_market;
            cod_migliore = current_supermercato->codice_supermercato;
        }
        
        current_supermercato = current_supermercato->next;
    }

    return cod_migliore;
}

int main() 
{
    prodotto_catalogo *listino = (prodotto_catalogo *)calloc(NR_PRODOTTI_CATALOGO, sizeof(prodotto_catalogo));
    assert(listino != NULL);

    /* elenco di supermercati della catena EUROMERCATI */
    supermercato *elenco_supermercati = NULL;

    printf("Codice migliore supermercato: %d\n", 
        miglior_supermercato(elenco_supermercati, listino));

    return EXIT_SUCCESS;
}
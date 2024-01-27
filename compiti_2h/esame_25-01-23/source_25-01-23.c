#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

typedef struct Tornei 
{
    char codice_torneo[3 + 1];
    int livello_torneo; /* 0 <= valore <= 48 */

    struct Tornei *next;
} Tornei;

typedef struct Giocatore {
    char id_giocatore[10 + 1];
    Tornei *elenco_tornei;

    struct Giocatore *next; 
} Giocatore;

/* Priority insert */
void aggiungi_torneo(Tornei **list, Tornei *torneo) 
{
    assert(torneo != NULL);

    /* 
     * Se la lista è vuota, allora aggiungo 
     * il nuovo elemento e non faccio nient'altro
     */
    if (*list == NULL) 
    {
        *list = torneo;
        return;
    }

    Tornei *current_node = *list;
    Tornei *prev_node = NULL;

    while (current_node != NULL) 
    {
        if (strcmp(torneo->codice_torneo, current_node->codice_torneo) < 0)
            break;

        prev_node = current_node;
        current_node = current_node->next;
    }

    /* 
     * se ho raggiunto la fine della lista, 
     * allora aggancio il nuovo torneo all'ultimo nodo presente
     */
    torneo->next = current_node;

    if (prev_node != NULL) {
        prev_node->next = torneo;
    } 
    else {
        *list = torneo;
    }
}

void aggiungi_giocatore(Giocatore **list, Giocatore *player) 
{
    assert(player != NULL);

    player->next = *list;
    *list = player;
}

Giocatore *leggi_partecipanti(char *fileName) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    Giocatore *out_list = NULL;

    while (!feof(pFile)) /* Leggo finché non raggiungo la fine del file */
    {
        Giocatore *new_player = (Giocatore *)malloc(sizeof(Giocatore));
        assert(new_player != NULL);

        new_player->elenco_tornei = NULL;

        fscanf(pFile, "%s", new_player->id_giocatore);

        /* Leggo tutte le coppie codice_torneo - livello_torneo */
        while (fgetc(pFile) == ' ')
        {
            Tornei *new_torneo = (Tornei *)malloc(sizeof(Tornei));
            assert(new_torneo != NULL);

            fscanf(pFile, "%s %d", new_torneo->codice_torneo, &new_torneo->livello_torneo);

            aggiungi_torneo(&new_player->elenco_tornei, new_torneo);
        }

        aggiungi_giocatore(&out_list, new_player);
    }

    fclose(pFile);
    return out_list;
}

int iscritti_torneo(Giocatore *elenco_giocatori, char *codice_torneo) 
{
    int totale_iscritti = 0;

    Giocatore *current_player = elenco_giocatori;

    while (current_player != NULL) 
    {
        Tornei *current_torneo = current_player->elenco_tornei;
        bool found_torneo = false;

        while (current_torneo != NULL && !found_torneo) 
        {
            if (strcmp(current_torneo->codice_torneo, codice_torneo) == 0) {
                totale_iscritti++;
                found_torneo = true;
            }

            current_torneo = current_torneo->next;
        }

        current_player = current_player->next;
    }

    return totale_iscritti;
}

int nuovi_iscritti_torneo(Giocatore *elenco_giocatori, char *codice_torneo) 
{
    int totale_nuovi_iscritti = 0;

    Giocatore *current_player = elenco_giocatori;

    while (current_player != NULL) 
    {
        Tornei *current_torneo = current_player->elenco_tornei;
        bool found_torneo = false;

        while (current_torneo != NULL && !found_torneo) 
        {
            if (strcmp(current_torneo->codice_torneo, codice_torneo) == 0) {
                found_torneo = true;
            }

            current_torneo = current_torneo->next;
        }

        if (!found_torneo) 
            totale_nuovi_iscritti++;

        current_player = current_player->next;
    }

    return totale_nuovi_iscritti;
}

void stampa_lista(Giocatore *list) 
{
    if (list == NULL) return;

    printf("Giocatore: %s\n", list->id_giocatore);
    
    Tornei *current_torneo = list->elenco_tornei;
    while (current_torneo != NULL) 
    {
        printf("\tTorneo: %s - Punteggio: %d\n", 
            current_torneo->codice_torneo,
            current_torneo->livello_torneo);
        
        current_torneo = current_torneo->next;
    }

    puts("");

    stampa_lista(list->next);
}

int main() 
{
    Giocatore *giocatori = leggi_partecipanti("partecipanti.txt");
    stampa_lista(giocatori);
    printf("Nuovi iscritti a Wim: %d\n", nuovi_iscritti_torneo(giocatori, "Wim"));
    printf("Iscritti a Wim: %d\n", iscritti_torneo(giocatori, "Wim"));
    return 0;
}
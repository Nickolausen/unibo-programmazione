#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NR_SET 3

typedef struct Partita {
    char id_partita[11 + 1];
    char giocatore1[20 + 1];
    char giocatore2[20 + 1];
    int ris1[NR_SET];
    int ris2[NR_SET];
    struct Partita *next;
} Partita;

void insert_partita(Partita **list, Partita *part) 
{
    if (*list == NULL) {
        *list = part;
        (*list)->next = NULL;
        return;
    }

    Partita *current_node = *list;

    /* scorro la lista finché non trovo il nodo nel quale agganciare la nuova partita */
    while (current_node != NULL) 
    {
        /* ... DA SISTEMARE ...*/
        if (strcmp(current_node->id_partita, part->id_partita) < 0) 
            break;
        
        current_node = current_node->next;
    }

    part->next = current_node;
    current_node = part; 
}

int vittorie_giocatore_torneo(Partita *list, char nominativo[20 + 1], char id_torneo[3 + 1], float *perc_vincita)
{
    int nr_vittorie = 0, totale_partite = 0;
    Partita *current_node = list;

    while (current_node != NULL) 
    {
        if (strncmp(current_node->id_partita, id_torneo, 3) && 
            (strcmp(current_node->giocatore1, nominativo) == 0 || strcmp(current_node->giocatore2, nominativo) == 0))
        {
            int setG1 = 0, setG2 = 0;

            int idxGiocatore = 0 + (strcmp(current_node->giocatore2, nominativo) == 0);
            for (int i = 0; i < NR_SET; i++) 
            {
                current_node->ris1[i] > current_node->ris2[i]
                    ? setG1++
                    : setG2++;
            }

            if ((idxGiocatore == 0 && setG1 > setG2) || 
                (idxGiocatore == 1 && setG2 > setG1)) nr_vittorie++;

            totale_partite++; 
        }

        current_node = current_node->next;
    }

    *perc_vincita = ((float)nr_vittorie / (float)totale_partite) * 100;
    return nr_vittorie;
}

int stampa_partite(Partita *list) 
{
    if (list == NULL) return 1;
    
    printf("Partita: %s - %s vs. %s\n", 
        list->id_partita, list->giocatore1, list->giocatore2);
    
    for (int i = 0; i < NR_SET; i++) {
        printf("\t[%d° Set] := %d/%d\n", 
            i + 1, list->ris1[i], list->ris2[i]);
    }
    puts("");

    return stampa_partite(list->next);
}

Partita *leggi_partite(char *fileName) 
{
    Partita *out_list = NULL;
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    while (!feof(pFile)) 
    {
        Partita *p = (Partita *)malloc(sizeof(Partita));
        assert(p != NULL);

        fscanf(pFile, "%s %s %s", p->id_partita, p->giocatore1, p->giocatore2);
        
        int setIdx = 0;
        while (fgetc(pFile) == ' ') 
        {
            fscanf(pFile, "%d %d", &p->ris1[setIdx], &p->ris2[setIdx]);
            setIdx++;
        }

        insert_partita(&out_list, p);
    }

    fclose(pFile);
    return out_list;
}

char *MVP_torneo(Partita *list, char *id_torneo) 
{
    Partita *current_node = list;

    while (current_node != NULL) 
    {
        if (strncmp(current_node->id_partita, id_torneo, 3) == 0) 
        {
            int setG1 = 0, setG2 = 0;
            for (int i = 0; i < NR_SET; i++) 
            {
                current_node->ris1[i] > current_node->ris2[i] 
                    ? setG1++
                    : setG2++;
            }

            return setG1 >= setG2 ? 
                current_node->giocatore1 : current_node->giocatore2;
        }

        current_node = current_node->next;
    }

    return NULL;
}

int main() 
{
    Partita *torneo = leggi_partite("partite.txt");
    stampa_partite(torneo);

    float perc_vincita = 0; 
    printf("Partite vinte da Rossi: %d - %.2f\n", 
        vittorie_giocatore_torneo(torneo, "Rossi", "Wim", &perc_vincita),
        perc_vincita);
    
    return EXIT_SUCCESS;
}
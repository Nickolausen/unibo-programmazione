/* Nicholas Magi, Matricola: 0001113915 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define NR_GIORNI 7

/* Supponiamo l'esistenza di massimo 3 reparti 
(dato che il numero non è specificato dal testo) */
#define NR_REPARTI 3

typedef struct singolo_turno {
    int id_turno;
    int pazienti_per_turno;
    int pazienti_effettivi;
    char id_medico1[12 + 1]; /* 12 char utili + 1 di terminatore */
    char id_medico2[12 + 1];
} singolo_turno;

typedef struct reparto {
    char id_reparto[5 + 1]; /* 5 char utili + 1 di terminatore */
    int pazienti_extra;
    singolo_turno turni[NR_GIORNI];
} reparto;

typedef struct list_reparto {
    reparto *data;
    int lastIndex;
    int size;
} list_reparto;

typedef struct reparto_medici {
    char id_reparto[5 + 1];
    char codice_richiesta_prestazione[25 + 1];
} reparto_medici;

char *get_reparto_id_by_codice_prestazione(reparto_medici *repartoMedici, char *codice_richiesta_prestazione)
{
    for (int i = 0; i < NR_REPARTI; i++) 
    {
        if (strcmp(repartoMedici->codice_richiesta_prestazione, codice_richiesta_prestazione) == 0)
            return repartoMedici->id_reparto;
    }

    /* se non trovo l'id_reparto, allora ritorno NULL */
    return NULL;
}

reparto *get_reparto_index_by_id(list_reparto *list, char *id_reparto) 
{
    for (int i = 0; i <= list->lastIndex; i++) 
    {
        /* Cerco il rispettivo reparto - quando l'ho trovato, allora lo restituisco */
        if (strcmp(list->data[i].id_reparto, id_reparto) == 0) 
            return &list->data[i];
    }

    return NULL;
}

void leggi_appuntamenti(char *fileName, list_reparto *reparti, reparto *esuberi) 
{
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL); /* NULL check */

    /* Vettore dato dal testo - corrispondenza tra codice_prestazione_richiesta e id_reparto */
    reparto_medici repartoMedici[NR_REPARTI];

    /* Vettore 'esuberi' richiesto dal testo */
    int idxEsubero = 0;

    while (!feof(pFile)) /* Il ciclo continua finché il cursore in lettura del file non ha raggiunto la fine del file */
    {
        char id_paziente[12 + 1], id_medico[12 + 1], codice_richiesta_prestazione[25 + 1];
        int turno_richiesto, giorno_richiesto;

        /* Leggo tutta la riga e memorizzo le relative informazioni - sposto il cursore in lettura alla riga successiva */
        fscanf(pFile, "%s %s %s %d %d\n", 
            id_paziente, 
            id_medico, 
            codice_richiesta_prestazione, 
            &turno_richiesto, 
            &giorno_richiesto);

        int firstIndexAvailable = reparti->lastIndex + 1;
        assert(firstIndexAvailable <= reparti->size); /* Controllo se posso aggiungere altri elementi al vettore reparti */

        /* Se sono qui, vuol dire che posso ancora aggiungere visite */
        char *id_reparto = get_reparto_id_by_codice_prestazione(&repartoMedici, codice_richiesta_prestazione);
        
        /* Suppongo il vettore abbia tutte le corrispondenze possibili, altrimenti esco dal programma */
        assert(id_reparto != NULL);

        /* Cerco il reparto interessato dalla visita */
        reparto *rep = get_reparto_index_by_id(&reparti, id_reparto);

        /* Se il reparto non esiste, allora posso aggiungerlo e aggiungere la visita richiesta */        
        if (rep == NULL) 
        {
            rep = (reparto *)malloc(sizeof(reparto));
            assert(rep != NULL); /* NULL check */

            strcpy(rep->id_reparto, id_reparto);
        }

        if (rep->turni[giorno_richiesto].pazienti_effettivi + 1 >= rep->turni[giorno_richiesto].pazienti_per_turno) 
        {
            /* Se in quel reparto, per il turno richiesto, sforo il numero massimo 
             * di pazienti visitabili allora si crea un esubero 
             */
            esuberi[idxEsubero] = *rep;
            idxEsubero++;
        }
        else 
        {
            /* altrimenti aggiorno il numero di pazienti visitati
             * e aggiungo il reparto al vettore
             */
            rep->turni[giorno_richiesto].pazienti_effettivi += 1;
            reparti->data[firstIndexAvailable] = *rep;
            reparti->lastIndex = firstIndexAvailable;
        }
        
    }
}

void occupazione_reparti(reparto_medici *repartoMedici, list_reparto *reparti) 
{
    for (int i = 0; i <= reparti->lastIndex; i++) 
    {
        /* ... */
    }
}

void medici_esuberi(reparto *esuberi) 
{
    for (int i = 0; i < 100; i++) 
    {
        printf("ID Reparto: %s, Pazienti extra: %d\n", 
            esuberi->id_reparto,
            esuberi->pazienti_extra);
    }
}

int main() 
{
    /* 
     * Utilizzo una struct ausiliaria per tenermi memorizzato anche l'indice dell'ultimo 
     * elemento che posso trovare
     */
    list_reparto *reparti = (list_reparto *)malloc(sizeof(list_reparto));
    assert(reparti != NULL); /* NULL check */
    reparti->lastIndex = -1;
    reparti->data = (reparto *)malloc(sizeof(reparto) * 200); /* Vettore allocato dinamicamente */
    reparti->size = 200;

    reparto esuberi[100];
    /* Leggo il file 'appuntamenti.txt' e inizializzo il vettore 'reparti' */
    leggi_appuntamenti("appuntamenti.txt", reparti, &esuberi);

    /* Stampo gli esuberi per ogni reparto */
    medici_esuberi(&esuberi);
    return 0;
}
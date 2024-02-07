#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define DEFAULT_COSTO 80
#define SOGLIA_SCONTO 10
#define PERC_SCONTO 15
#define SCONTO_APPLICATO 1 - (PERC_SCONTO / 100)

typedef struct appuntamento {
    int id_medico;
    int ora_inizio;
    int ora_fine;
} appuntamento;

typedef struct list_appuntamento {
    appuntamento *data;
    int last_index;
    int size;
} list_appuntamento;

typedef struct paziente {
    int id_paziente;
    char nome_e_cognome[100 + 1];
    float preventivo;
    list_appuntamento *appuntamenti; /* vettore allocato dinamicamente */

    /* linked list */
    struct paziente *next;
} paziente;

/* Struttura inutilizzata, descrive come sono disposti i dati nel file */
typedef struct file_row {
    int id_paziente;
    int id_medico;
    char nome_e_cognome[100 + 1];
    float preventivo;
    list_appuntamento *appuntamenti;
} file_row;

typedef struct tariffa {
    int id_medico;
    float costo_orario;
} tariffa;

/* Struttura di supporto per salvare informazioni aggiuntive del vettore allocato dinamicamente */
typedef struct list_tariffa {
    tariffa *data;
    int last_index;
    int size;
} list_tariffa;

void aggiungi_tariffa(list_tariffa *tariffe, tariffa *tar) 
{
    int first_index_available = tariffe->last_index + 1;
    /* 
     * se aggiungere un nuovo elemento comporta 
     * fuoriuscire dal vettore, allora aggiungo una cella in più al vettore
     */
    if (first_index_available >= tariffe->size)
    {
        int new_size = tariffe->size + 1;
        tariffe->data = realloc((tariffa *)tariffe->data, new_size * sizeof(tariffa));
        assert(tariffe->data != NULL);

        tariffe->size = new_size;
    }

    /* inserimento ordinato */
    for (int i = 0; i <= tariffe->last_index; i++) 
    {
        if (tar->id_medico < tariffe->data[i].id_medico)
        {
            /* shifto tutti gli elementi a destra di 1 */
            for (int j = first_index_available; j > i; j--) 
            {
                tariffe->data[j] = tariffe->data[j - 1];
            }

            /* aggiungo la nuova tariffa */
            tariffe->data[i] = *tar;

            /* aggiorno l'indice dell'ultimo elemento presente in lista */
            tariffe->last_index = first_index_available;
            return;
        }
    }
}

void aggiungi_appuntamento(list_appuntamento *appuntamenti, appuntamento *app) 
{
    /* logica analoga ad 'aggiungi_tariffa()' */
    int first_index_available = appuntamenti->last_index + 1;
    if (first_index_available >= appuntamenti->size)
    {
        int new_size = appuntamenti->size + 1;
        appuntamenti->data = realloc((appuntamento *)appuntamenti->data, new_size * sizeof(appuntamento));
        assert(appuntamenti->data != NULL);

        appuntamenti->size = new_size;
    }

    /* aggiungo un elemento senza fare nessun ordinamento */
    appuntamenti->data[first_index_available] = *app;
    appuntamenti->last_index = first_index_available;
}

/* HEAD INSERT nella linked list pazienti */
void aggiungi_paziente(paziente **list, paziente *paz) 
{
    assert(paz != NULL);

    paz->next = *list;
    *list = paz;
}

paziente *find_paziente(int id_paziente, paziente *list)
{
    paziente *current_node = list;
    while (current_node != NULL) 
    {
        if (current_node->id_paziente == id_paziente)
            return current_node;

        current_node = current_node->next;
    }

    return NULL;
}

paziente *leggi_appuntamenti(char *fileName)
{
    paziente *out_list = NULL;
    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL);

    while (!feof(pFile)) /* Continuo finché non ho raggiunto la fine del file */
    {
        int id_paziente, id_medico;
        char nome[100 + 1], cognome[100 + 1];
        fscanf(pFile, "%d %d %s %s", 
            &id_paziente,
            &id_medico,
            nome,
            cognome);

        /* Cerco il paziente nella lista che sto costruendo */
        paziente *paz = find_paziente(id_paziente, out_list);
        if (paz == NULL) /* Se non lo trovo, lo creo e lo aggiungo */
        {
            paz = (paziente *)malloc(sizeof(paziente));
            assert(paz != NULL);

            snprintf(paz->nome_e_cognome, 100, "%s %s", nome, cognome);
            paz->id_paziente = id_paziente;
            paz->preventivo = 0;

            paz->appuntamenti = (list_appuntamento *)malloc(sizeof(list_appuntamento));
            assert(paz->appuntamenti != NULL);

            paz->appuntamenti->data = NULL;
            paz->appuntamenti->last_index = -1;
            paz->appuntamenti->size = 0;

            aggiungi_paziente(&out_list, paz);
        }

        /* Leggo tutti gli appuntamenti */
        while (fgetc(pFile) == ' ') 
        {
            appuntamento new_app;

            new_app.id_medico = id_medico;
            fscanf(pFile, "%d %d", new_app.ora_inizio, new_app.ora_fine);

            aggiungi_appuntamento(paz->appuntamenti, &new_app);
        }
    }

    fclose(pFile);
    return out_list;
}

void duplica_pazienti(paziente *node, paziente **out_node) 
{
    if (node == NULL) return;

    duplica_pazienti(node->next, out_node);

    aggiungi_paziente(out_node, node);
}

tariffa *get_tariffa_by_id_medico(list_tariffa *tariffe, int id_medico)
{
    for (int i = 0; i <= tariffe->last_index; i++)
    {
        if (tariffe->data[i].id_medico == id_medico)
            return &tariffe->data[i];
    }

    tariffa *default_tariffa = (tariffa *)malloc(sizeof(tariffa));
    assert(default_tariffa != NULL);

    default_tariffa->id_medico = id_medico;
    default_tariffa->costo_orario = DEFAULT_COSTO;

    aggiungi_tariffa(tariffe, &default_tariffa);
    return default_tariffa;
}

void calcola_preventivi(list_tariffa *tariffe, paziente **list)
{
    paziente *current_paziente = *list;

    while (current_paziente != NULL) 
    {
        int durata_totale = 0;
        for (int idxApp = 0; idxApp <= current_paziente->appuntamenti->last_index; idxApp++) 
        {
            int durata = current_paziente->appuntamenti->data[idxApp].ora_fine - current_paziente->appuntamenti->data[idxApp].ora_inizio;
            current_paziente->preventivo += 
                get_tariffa_by_id_medico(tariffe, current_paziente->appuntamenti->data[idxApp].id_medico)->costo_orario * durata;

            durata_totale += durata;
        }

        /* applico lo sconto se le ore trattamento sono più di 10 */
        if (durata_totale >= SOGLIA_SCONTO)
            current_paziente->preventivo *= SCONTO_APPLICATO;

        current_paziente = current_paziente->next;
    }
}

int main() 
{
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

#define NR_TARIFFE 200
#define NR_PAZIENTI 100

typedef struct { /* suppongo di trovarla nel file 'appuntamenti.txt' in formato DD/MM/YYYY */
    int giorno;
    int mese;
    int anno;
} date;

typedef struct appuntamento {
    date data;
    int ora_inizio;
    int ora_fine;
    int durata;
    struct appuntamento *next;
} appuntamento;

typedef struct { /* struttura per memorizzare le informazioni fornite da file - non utilizzata */
    char id_paziente[15 + 1];
    char id_medico[20 + 1];
    char nome_e_cognome[100 + 1];
    appuntamento *appuntamenti;
} filerow;

typedef struct tariffa {
    char id_medico[20 + 1];
    float costo_orario;
} tariffa;

typedef struct list_tariffa {
    tariffa* data;
    int size;
    int lastIndex;
} list_tariffa;

typedef struct paziente {
    char id_paziente[15 + 1];
    char id_medico[20 + 1];
    float preventivo;
    appuntamento *appuntamenti;

    struct paziente *next;
} paziente;

/* Utility per gestire la pila di appuntamenti */
void push(appuntamento **appuntamenti, appuntamento *app) 
{
    assert(app != NULL);

    app->next = *appuntamenti;
    *appuntamenti = app;
}

/* Utility per gestire la pila di appuntamenti - non necessaria */
appuntamento *pop(appuntamento **appuntamenti) 
{
    appuntamento *out = *appuntamenti;
    *appuntamenti = (*appuntamenti)->next;

    /* 'stacco' l'elemento dalla pila */
    out->next = NULL;
    return out;
}

void insert_tariffa(list_tariffa *tariffe, tariffa *tar)
{
    /* se la lista è ancora vuota, allora aggiungo la tariffa senza fare altro */
    if (tariffe->lastIndex == -1) 
    {
        tariffe->lastIndex++;
        tariffe->data[tariffe->lastIndex] = *tar;
        return;
    }

    /* controllo di poter aggiungere un elemento al vettore */
    assert(tariffe->lastIndex + 1 < tariffe->size);

    for (int i = 0; i < tariffe->lastIndex; i++) 
    {
        /* 
         * Se l'id_medico della tariffa che si vuole inserire è più grande 
         * l'i-esimo id_medico salvato nel vettore, allora ho trovato la posizione in cui inserire
         * la nuova tariffa. 
         */
        if (strcmp(tar->id_medico, tariffe->data[i].id_medico) < 0) 
        {
            /*
             * Parto dall'indice successivo all'ultimo elemento memorizzato
             * e shifto tutti gli elementi a destra
             */
            for (int lastIdx = tariffe->lastIndex + 1; lastIdx > i; lastIdx--)
            {
                tariffe->data[lastIdx] = tariffe->data[lastIdx - 1];
            }

            /* inserisco il nuovo elemento nella posizione liberata */
            tariffe->data[i] = *tar;

            /* aggiorno l'indice dell'ultimo elemento inserito */
            tariffe->lastIndex++;
            return;
        }
    }
}

void priority_insert_paziente(paziente **list, paziente *el) 
{
    paziente *current_node = *list;

    /* 
     * scorro la lista finché non ho trovato la posizione
     * in cui finirà il nuovo paziente 
     */
    while (current_node != NULL && 
        strcmp(el->id_paziente, current_node->id_paziente) > 0) 
    {
        current_node = current_node->next;
    }

    el->next = current_node->next;
    current_node->next = el;
}

paziente *get_paziente_by_id_and_id_medico(paziente *list, char *id_paziente, char *id_medico) 
{
    /* 
     * poiché il testo indica che il paziente può comparire più volte 
     * nella lista degli appuntamenti sotto medici diversi, vado a cercare se compare nella lista
     * sotto lo stesso medico con cui è già stato inserito
     */
    paziente *current_node = list;
    while (current_node != NULL) 
    {
        if (strcmp(current_node->id_paziente, id_paziente) == 0 &&
            strcmp(current_node->id_paziente, id_medico) == 0)
            return current_node;
        
        current_node = current_node->next;
    }

    return NULL;
}

paziente *leggi_appuntamenti(char *fileName) 
{
    paziente *out_list = NULL;

    FILE *pFile = fopen(fileName, "r");
    assert(pFile != NULL); /* null check */

    while (!feof(pFile)) /* Continua a leggere finché il cursore in lettura del file non arriva a fine file */
    {
        char id_paziente[12 + 1], id_medico[20 + 1];
        fscanf(pFile, "%s %s %*s", id_paziente, id_medico);
        
        /* cerco il paziente appena letto nella lista che sto costruendo - criterio spiegato nella funzione  */
        paziente *paz = get_paziente_by_id_and_id_medico(out_list, id_paziente, id_medico);
        if (paz == NULL) /* se non lo trovo, lo creo */
        {
            paz = (paziente *)malloc(sizeof(paziente));
            assert(paz != NULL);

            strcpy(paz->id_paziente, id_paziente);
            strcpy(paz->id_medico, id_medico);
            paz->preventivo = 0;
            paz->appuntamenti = NULL;
        }

        while (fgetc(pFile) == ' ') 
        {
            /* 
             * leggo la tripla di valori degli appuntamenti:
             * - data
             * - ora_inizio
             * - ora_fine
             */
            int ora_inizio, ora_fine;
            date data;

            fscanf(pFile, "%d/%d/%d %d %d", 
                &data.giorno, &data.mese, &data.anno,
                &ora_inizio,
                &ora_fine);

            appuntamento *ap = (appuntamento *)malloc(sizeof(appuntamento));
            assert(ap != NULL);

            ap->data = data;
            ap->ora_inizio = ora_inizio;
            ap->ora_fine = ora_fine;
            ap->durata = ora_fine - ora_inizio;

            push(&paz->appuntamenti, ap);
        }

        /* inserimento del paziente mantenendo la lista ordinata per id_paziente - crescente */
        priority_insert_paziente(&out_list, paz);
    }

    return out_list;
}

void stampa_agenda_paziente(paziente *list, char *id_paziente) 
{
    paziente *current_node = list;
    printf("Agenda appuntamenti paziente %s: \n", id_paziente);
    while (current_node != NULL) 
    {
        /* se ho trovato il paziente corrispondente, stampo le informazioni relative ai suoi appuntamenti con un determinato dottore */
        if (strcmp(current_node->id_paziente, id_paziente) == 0)
        {
            printf("== con il dottor #%s: \n", current_node->id_medico);
            appuntamento *current_appuntamento = current_node->appuntamenti; 
            while (current_appuntamento != NULL) 
            {
                printf("\tData: %d/%d/%d - ora inizio: %d - ora fine: %d\n", 
                    current_appuntamento->data.giorno, current_appuntamento->data.mese, current_appuntamento->data.anno,
                    current_appuntamento->ora_inizio, current_appuntamento->ora_fine);
                
                current_appuntamento = current_appuntamento->next;
            }
        }

        current_node = current_node->next;
    }
}

bool is_paziente_gia_calcolato(char *id_pazienti[NR_PAZIENTI], char *id_paziente) 
{
    for (int i = 0; i < NR_PAZIENTI; i++) 
    {
        if (strcmp(id_pazienti[i], id_paziente) == 0) 
            return true;
    }

    return false;
}

tariffa *get_tariffa_by_id_medico(list_tariffa *tariffe, char *id_medico)
{
    tariffa *output = (tariffa *)malloc(sizeof(tariffa));
    assert(output != NULL);

    output->costo_orario = 100;
    strcpy(output->id_medico, id_medico);

    for (int i = 0; i <= tariffe->lastIndex; i++)
    {
        if (strcmp(tariffe->data[i].id_medico, id_medico) == 0)
            output = &tariffe->data[i];
    }

    return output;
}

void calcola_preventivi(paziente **pazienti, list_tariffa *tariffe) 
{
    char *id_pazienti_visitati[NR_PAZIENTI];
    paziente *current_node = *pazienti;
    
    int idxPaziente = 0;
    while (current_node != NULL) 
    {
        if (!is_paziente_gia_calcolato(id_pazienti_visitati, current_node->id_paziente))
        {
            int totale_ore_trattamento = 0;
            paziente *current_paziente = current_node;
            while (current_paziente != NULL) 
            {
                /* 
                 * se il paziente del secondo scorrimento corrisponde con il paziente del primo scorrimento,
                 * calcolo il preventivo previsto per quel set di appuntamenti con il dottore dato
                 */
                if (strcmp(current_paziente->id_paziente, current_node->id_paziente) == 0) 
                {
                    /* se la tariffa corrispondente al medico visitante non è trovata, questa è di base 100euro/ora */
                    tariffa *tariffa_corrispondente = get_tariffa_by_id_medico(tariffe, current_paziente->id_medico);

                    /* scorro tutta la lista degli appuntamenti */
                    appuntamento *current_appuntamento = current_paziente->appuntamenti;
                    while (current_appuntamento != NULL) 
                    {
                        /* calcolo il preventivo sul totale del primo paziente di scorrimento */
                        current_node->preventivo += current_appuntamento->durata * tariffa_corrispondente->costo_orario;
                        
                        current_appuntamento = current_appuntamento->next;
                    }
                }

                current_paziente = current_paziente->next;
            }

            if (totale_ore_trattamento >= 10) 
            {
                /* calcolo uno sconto del 15% per coloro che superano le 10 ore di trattamento */
                float sconto = (15*current_node->preventivo) / 100;
                current_node->preventivo -= sconto;
            }

            /* segnalo di aver già controllato tutte le occorrenze del paziente x all'interno della lista pazienti */
            strcpy(id_pazienti_visitati[idxPaziente++], current_node->id_paziente);
        }

        /* passo al prossimo paziente da cercare all'interno di tutta la lista pazienti */
        current_node = current_node->next;
    }
}

int main() 
{
    list_tariffa *tariffe = (list_tariffa *)malloc(sizeof(list_tariffa));
    assert(tariffe != NULL); /* null check */

    tariffe->data = (tariffa *)malloc(sizeof(tariffa) * NR_TARIFFE);
    assert(tariffe->data != NULL); /* null check */

    tariffe->size = NR_TARIFFE;
    /* supponiamo di avere il vettore tariffe->data riempito di tariffe - poiché il testo non da particolari specifiche per questo caso */
    // insert_tariffa(tariffe, /* tariffa #1 */);
    // insert_tariffa(tariffe, /* tariffa #2 */);
    // insert_tariffa(tariffe, /* tariffa #3 */);
    // [...]

    paziente *pazienti = leggi_appuntamenti("appuntamenti.txt");
    stampa_agenda_paziente(pazienti, "PZ013915");
    calcola_preventivi(&pazienti, tariffe);
    return 0;
}
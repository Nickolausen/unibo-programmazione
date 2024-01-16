#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define NR_MEDICI 200
#define NR_TURNI 7
#define UNDEFINED_REPARTO "Undefined"

typedef struct singolo_turno {
    int id_turno;
    int pazienti_per_turno;

    struct singolo_turno *next;
} singolo_turno;

typedef struct medico {
    char id_medico[12 + 1];
    char reparto[5 + 1];
    struct singolo_turno *turni[NR_TURNI];
} medico;

typedef struct list_medico {
    medico *data;
    int size;
    int lastIndex;
} list_medico;

typedef struct singolo_turno *lista_turni;

typedef struct esubero_reparto {
    char reparto[5 + 1];
    lista_turni *turni[NR_TURNI];
} esubero_reparto;

void aggiungi_medico(list_medico **list, medico *elem) 
{
    int firstAvailableIndex = (*list)->lastIndex + 1;

    /* Se ho raggiunto la fine del vettore, esco dalla funzione */
    if (firstAvailableIndex >= (*list)->size) return;
    
    /* Altrimenti aggiungo il medico al vettore e aggiorno l'ultimo indice */
    (*list)->data[firstAvailableIndex] = *elem;
    (*list)->lastIndex++;
}

int find_index(list_medico **list, char id_medico[12 + 1]) 
{
    if ((*list)->lastIndex == -1) return -1;

    for (int i = 0; i <= (*list)->lastIndex; i++)
        if (strcmp((*list)->data[i].id_medico, id_medico) == 0) return i;

    return -1;
}

int to_index(int giorno) { return giorno - 1; }

void head_insert(singolo_turno **list, singolo_turno *node) 
{
    node->next = *list;
    *list = node;
}

void aggiungi_esubero(esubero_reparto **lista_esuberi, esubero_reparto *esubero) 
{

}

void leggi_appuntamenti(char fileName[], list_medico **output) 
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) 
    {
        printf("Unable to open '%s'", fileName);
        return;
    }

    char *repartiMedici[50];
    for (int i = 0; i < 50; i++)
    {
        strcpy(repartiMedici[i], UNDEFINED_REPARTO);
    }

    strcpy(repartiMedici[21], "OCL");
    strcpy(repartiMedici[34], "ORT");

    esubero_reparto *esuberi = (esubero_reparto *)malloc(sizeof(esubero_reparto));
    if (esuberi == NULL) return;

    /* Continua finché il cursore in lettura del file non raggiunge la fine del file */
    while (!feof(pFile)) 
    {
        char id_paziente[12 + 1];
        char id_medico[12 + 1];
        int idxReparto;
        char slice_id_medico[5 + 1];

        int turno_richiesto, giorno_richiesto;
        fscanf("%s %s-%d %*s %d %d", 
            id_paziente, slice_id_medico, &idxReparto, &turno_richiesto, &giorno_richiesto);

        /* Siccome id_medico comprende anche reparto, ho letto prima reparto separatamente, poi
        unisco i due attributi in id_medico */
        snprintf(id_medico, 12 + 1, "%s-%d", slice_id_medico, idxReparto);

        int idxMedico = find_index(output, id_medico);

        /* Se il medico è già presente nel vettore, provo ad aggiungere l'appuntamento richiesto */
        if (idxMedico == -1) 
        {
            medico med;
            strcpy(med.id_medico, id_medico);
            strcpy(med.reparto, repartiMedici[idxReparto]);

            aggiungi_medico(output, &med);
            idxMedico = (*output)->lastIndex;
        }

        singolo_turno *pTurno = (*output)->data[idxMedico].turni[to_index(giorno_richiesto)];
        
        int countTurno = 0;
        
        /* Cerco il turno con il corrispondente id_turno */
        singolo_turno *current = pTurno;
        while (current != NULL) 
        {
            if (current->id_turno == turno_richiesto) break;
            countTurno++;
            current = current->next;
        }  

        /* Se non lo trovo, lo creo */
        if (current == NULL && countTurno < NR_TURNI) 
        {
            singolo_turno *turno = (singolo_turno *)malloc(sizeof(singolo_turno));
            turno->id_turno = turno_richiesto;
            turno->next = NULL;
            turno->pazienti_per_turno = 0;

            head_insert(&pTurno, turno);
        }

        /* Se il turno individuato può contenere ulteriori pazienti, inserisco il paziente in coda */
        if (pTurno->pazienti_per_turno < 5) 
        {
            pTurno->pazienti_per_turno++;
        }
        else /* altrimenti aggiungo il paziente alla lista degli esuberi */
        {
            // da finire
        }
    }
}

int main() 
{
    list_medico *medici = (list_medico *)malloc(sizeof(list_medico));
    if (medici == NULL) return;

    medici->lastIndex = -1;
    medici->size = NR_MEDICI;
    
    medici->data = (medico *)malloc(sizeof(medico) * NR_MEDICI);
    if (medici->data == NULL) return;

    leggi_appuntamenti("appuntamenti.txt", &medici);

    return 0;
}
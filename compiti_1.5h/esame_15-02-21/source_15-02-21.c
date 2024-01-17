#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_DENTISTI 3

typedef struct appuntamento 
{
    int ora_inizio;
    int ora_fine;
} appuntamento;

typedef struct list_appuntamento 
{
    appuntamento *data;
    int count;
    int lastIndex;
} list_appuntamento;

typedef struct tariffa 
{
    int id_medico;
    float costo_orario;
} tariffa;

typedef struct list_tariffa {
    tariffa *data;
    int count;
    int lastIndex;
} list_tariffa;

typedef struct paziente {
    int id_paziente;
    int id_medico;
    char nome_e_cognome[100 + 1];
    float preventivo;
    list_appuntamento *appuntamenti;

    struct paziente *next;
} paziente;

void sort_by_ascending(list_tariffa *vect) 
{
    bool swapping = true;
    while (swapping) 
    {
        swapping = false;
        for (int i = 0; i <= vect->lastIndex; i++) 
        {
            tariffa swapEl;
            if (vect->data[i].id_medico > vect->data[i + 1].id_medico) 
            {
                swapping = true;
                swapEl = vect->data[i];
                vect->data[i] = vect->data[i + 1];
                vect->data[i + 1] = swapEl;
            }
        }
    }
}

void aggiungi_tariffa(list_tariffa *vect, tariffa el) 
{
    int currentCount = vect->count;
    vect->data = (tariffa *)realloc((tariffa *)vect->data, (currentCount + 1) * sizeof(tariffa));
    if (vect->data == NULL) {
        printf("An error occurred. Exiting...");
        exit(EXIT_FAILURE);
    }

    vect->count++;
    vect->lastIndex = vect->count - 1;

    vect->data[vect->lastIndex] = el;   

    /* Ordino il vettore in base al campo 'id_medico' - crescente */
    sort_by_ascending(vect);
}

void aggiungi_appuntamento(list_appuntamento **vect, appuntamento *el) 
{
    int firstAvailableIndex = (*vect)->lastIndex + 1;
    int currentCount = (*vect)->count;
    if (firstAvailableIndex >= currentCount) {
        (*vect)->data = (appuntamento *)realloc((*vect)->data, (currentCount + 1) * sizeof(appuntamento));
        (*vect)->count = currentCount + 1;
    }

    (*vect)->data[firstAvailableIndex] = *el;   
    (*vect)->lastIndex++;
}

void head_insert(paziente **list, paziente *node) 
{
    if (node == NULL) return;

    node->next = (*list);
    (*list) = node;
}

paziente *get_paziente_by_id(paziente **list, int id_paziente) 
{
    paziente *current_node = (*list);
    while (current_node != NULL) 
    {
        if (current_node->id_paziente == id_paziente) return current_node;

        current_node = current_node->next;
    }

    return NULL;
}

paziente *leggi_appuntamenti(char *fileName) 
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) 
    {
        printf("Unable to open '%s'. Exiting...", fileName);
        return NULL;
    }

    paziente *out_list = NULL;
    while (!feof(pFile)) 
    {
        int id_paziente, id_medico;
        char tmpNome[100 + 1], tmpCognome[100 + 1];
        float preventivo;

        fscanf(pFile, "%d %d %s %s %f", 
            &id_paziente, 
            &id_medico, 
            tmpNome, 
            tmpCognome, 
            &preventivo);

        paziente *p = get_paziente_by_id(&out_list, id_paziente); /* Cerco il paziente nella mia lista */
        if (p == NULL) 
        {
            /* Se il paziente non esiste, lo creo e inserisco i dati appena letti da file */
            p = (paziente *)malloc(sizeof(paziente));
            if (p == NULL) return NULL;

            p->id_paziente = id_paziente;
            p->id_medico = id_medico;
            p->preventivo = preventivo;

            snprintf(p->nome_e_cognome, 100 + 1, "%s %s", tmpNome, tmpCognome);

            p->appuntamenti = (list_appuntamento *)malloc(sizeof(list_appuntamento));
            if (p->appuntamenti == NULL) return NULL;

            p->appuntamenti->data = malloc(sizeof(appuntamento) * 0);
            if (p->appuntamenti->data == NULL) return NULL;

            p->appuntamenti->lastIndex = -1;
            p->appuntamenti->count = 0;
        }

        /* Leggo gli appuntamenti - numero di coppie indefinito */
        while (fgetc(pFile) == ' ') 
        {  
            appuntamento *ap = (appuntamento *)malloc(sizeof(appuntamento));
            if (ap == NULL) return NULL;

            fscanf(pFile, "%d %d", &ap->ora_inizio, &ap->ora_fine);
            aggiungi_appuntamento(&p->appuntamenti, ap);
        }

        head_insert(&out_list, p);
    }

    return out_list;
}

paziente *duplica_pazienti(paziente *list) 
{
    paziente *duplicate = NULL;
    if (list == NULL) return duplicate;

    head_insert(&duplicate, list);

    return duplica_pazienti(&duplicate);
}

tariffa *get_tariffa_by_id(list_tariffa *tariffe, int id_medico) 
{
    tariffa *output = NULL;
    /* Cerco il medico all'interno della lista tariffe */
    for (int i = 0; i <= tariffe->lastIndex; i++) 
    {
        /* Se lo trovo, me lo salvo */
        if (tariffe->data[i].id_medico == id_medico) 
        {
            output = &tariffe->data[i];
        }
    }

    /* Se non l'ho trovato in lista, allora creo una nuova tariffa standard di 80euro/ora */
    if (output == NULL) 
    {
        aggiungi_tariffa(tariffe, (tariffa){id_medico, 80});
        output = &(tariffe->data[tariffe->lastIndex]);
    }

    return output;
}

void calcola_preventivi(paziente **list, list_tariffa *tariffe)  
{
    paziente *current_node = *list;
    while (current_node != NULL) 
    {
        tariffa *tar = get_tariffa_by_id(tariffe, current_node->id_medico);
        for (int i = 0; i <= current_node->appuntamenti->lastIndex; i++) 
        {
            int durata = current_node->appuntamenti->data[i].ora_fine - current_node->appuntamenti->data[i].ora_inizio;
            current_node->preventivo += tar->costo_orario * durata;
        }

        current_node = current_node->next;
    }
}

/* Non richiesta, ma utile per debug */
void stampa_lista(paziente **list) 
{
    paziente *current_node = *list;
    while (current_node != NULL) 
    {
        printf("ID PAZIENTE: %d - PAZIENTE: %s\n", current_node->id_paziente, current_node->nome_e_cognome);
        printf("Preventivo totale: %f", current_node->preventivo);
        current_node = current_node->next;
    }
}

int main() 
{
    /* Per semplificare, supponiamo di avere al massimo 3 dentisti */
    list_tariffa *tariffe = (list_tariffa *)malloc(sizeof(list_tariffa));
    if (tariffe == NULL) exit(EXIT_FAILURE);

    tariffe->data = NULL;
    tariffe->lastIndex = -1;
    tariffe->count = 0;

    aggiungi_tariffa(tariffe, (tariffa){6784, 50});
    aggiungi_tariffa(tariffe, (tariffa){2351, 75});
    aggiungi_tariffa(tariffe, (tariffa){5568, 40});

    char fileName[] = "appuntamenti.txt";
    /* Poichè non specificato dal testo dell'esame, presuppongo che un dottore 
     * prenda in cura un solo paziente all'interno dello studio. All'interno di "appuntamenti.txt" troverò quindi più appuntamenti
     * dello stesso paziente distribuiti in righe diverse che verranno uniti in un unica lista, e avranno
     * tutti lo stesso medico
     */
    paziente *list = leggi_appuntamenti(fileName);
    
    calcola_preventivi(&list, tariffe);
    stampa_lista(&list);

    return EXIT_SUCCESS;
}
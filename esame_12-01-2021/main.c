#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEZIONI 8
#define INITIAL_COUNT 100

typedef struct Lezione {
    int ora_inizio;
    int durata;
} Lezione;

typedef struct ListLezione {
    Lezione *informazioni;
    int size;
    int lastIndex;
} ListLezione;

typedef struct Studente {
    int matricola;
    char nome_e_cognome[100];
    ListLezione *lezioni;
} Studente;

typedef struct Node {   
    Studente*data;
    struct Node* next;
    struct Node* first;
} Node;

typedef struct Node* ListStudente;

typedef struct NuoveLezioni {
    int matricola;
    int durata;
} NuoveLezioni;

typedef struct ListNuoveLezioni {
    NuoveLezioni *informazioni;
    int size;
    int lastIndex;
} ListNuoveLezioni;

Node* node_alloc(Studente *stud) 
{
    Node* nodo = (Node*)malloc(sizeof(Node));
    if (nodo != NULL) 
    {
        nodo->data = stud;
        nodo->next = NULL;
    }

    return nodo;
}

bool head_insert(struct Node** lista, Node* nodo) 
{
    if (nodo == NULL || lista == NULL) return false;

    *lista = (*lista)->first;

    nodo->next = *lista;
    nodo->first = nodo;
    *lista = nodo;

    return true;
}

Node* get_student_by_matricola(ListStudente *elenco_studenti, int matricola)
{
    Node* current_student = *elenco_studenti;
    while (current_student != NULL) 
    {
        if (current_student->data->matricola == matricola)
            return current_student;

        current_student = current_student->next;
    }

    return NULL;
}

/*
 * Bubble Sort per ordinare le lezioni in ordine crescente,
 * in base all'ora di inizio
 */
void ascending_sort(Lezione *pLezioni, int lastIndex) 
{
    bool swapping = true;
    while (swapping) 
    {
        swapping = false;
        for (int i = 0; i < lastIndex - 1; i++) 
        {
            Lezione swap;
            if (pLezioni[i].ora_inizio > pLezioni[i + 1].ora_inizio) 
            {
                swapping = true;
                
                swap = pLezioni[i];
                pLezioni[i] = pLezioni[i + 1];
                pLezioni[i + 1] = swap;
            }
        }
    }

    return;
}

/*
 * Legge le informazioni richiesta dal problema da file e le memorizza in una 
 * linked list.
 */
ListStudente leggi_lezioni(char fileName[]) 
{
    Node* outputList = (Node*)malloc(sizeof(Node));
    if (outputList == NULL) return NULL;

    FILE* pFile = fopen(fileName, "r");
    if (pFile == NULL)
    {
        printf("Unable to open '%s'; Exiting...", fileName);
        return NULL;
    }

    while (!feof(pFile)) 
    {
        Studente *pStud = (Studente*)malloc(sizeof(Studente));
        if (pStud == NULL) return NULL;

        pStud->lezioni = (ListLezione*)malloc(sizeof(ListLezione));
        if (pStud->lezioni == NULL) return NULL;

        pStud->lezioni->lastIndex = -1;
        pStud->lezioni->size = MAX_LEZIONI;

        char tmpNome[100], tmpCognome[100];
        fscanf(pFile, "%d %s %s",
            &(pStud->matricola),
            tmpNome, tmpCognome);

        snprintf(pStud->nome_e_cognome, 100, "%s %s", tmpNome, tmpCognome);

        int idxLezione = 0;
        Lezione vectLezioni[MAX_LEZIONI];
        while (fgetc(pFile) == ' ') 
        {
            fscanf(pFile, "%d-%d", 
                &(vectLezioni[idxLezione].ora_inizio),
                &(vectLezioni[idxLezione].durata));

            idxLezione++;
            pStud->lezioni->lastIndex++;
        }

        ascending_sort(vectLezioni, pStud->lezioni->lastIndex);
        pStud->lezioni->informazioni = vectLezioni;

        if (!head_insert(&outputList, node_alloc(pStud))) return NULL;
    }

    fclose(pFile);
    return outputList;
}

/*
 * Stampa in maniera ricorsiva la linked list degli studenti.
 */
void stampa_lista(ListStudente current_stud)
{
    if (current_stud == NULL) {
        return;
    }

    printf("Matricola: %d, Nome e cognome: %s\n", 
        current_stud->data->matricola, 
        current_stud->data->nome_e_cognome); 

    for (int idxLezione = 0; idxLezione <= current_stud->data->lezioni->lastIndex; idxLezione++) 
    {
        printf("Lezione [%d]: dalle ore %d x %d ore.\n",
            idxLezione + 1, 
            current_stud->data->lezioni->informazioni[idxLezione].ora_inizio,
            current_stud->data->lezioni->informazioni[idxLezione].durata);
    }
    puts("");

    stampa_lista(current_stud->next);
}

/*
 * Aggiunge, ove possibile, le nuove lezioni alla serie di impegni già previsti per gli studenti;
 * ritorna 'true' se tutte le nuove lezioni previste sono state aggiunte, 'false' altrimenti.
 * Ritorna anche, tramite passaggio per riferimento, il numero di lezioni che non sono state aggiunte.
 */
bool inserisci_nuove_lezioni(ListNuoveLezioni* nuove_lezioni, ListStudente* elenco_studenti, int* numero_lez_non_aggiunte) 
{
    bool everythingAdded = true;
    for (int idxNuovaLezione = 0; idxNuovaLezione < nuove_lezioni->lastIndex; idxNuovaLezione++) 
    {
        Node* studente_interessato = get_student_by_matricola(elenco_studenti, nuove_lezioni->informazioni[idxNuovaLezione].matricola);

        for (int idxLezione = 0; idxLezione < studente_interessato->data->lezioni->lastIndex - 1; idxLezione++) 
        {
            int ora_fine_lezione_programmata = studente_interessato->data->lezioni->informazioni[idxLezione].ora_inizio + studente_interessato->data->lezioni->informazioni[idxLezione].durata;
            int intervallo_tra_lezioni = studente_interessato->data->lezioni->informazioni[idxLezione + 1].ora_inizio - ora_fine_lezione_programmata;
            int ora_fine_nuova_lezione = ora_fine_lezione_programmata + nuove_lezioni->informazioni[idxNuovaLezione].durata;
            
            if ( intervallo_tra_lezioni > nuove_lezioni->informazioni[idxNuovaLezione].durata &&
                ora_fine_nuova_lezione > 9 && ora_fine_nuova_lezione < 18) 
                {
                    // [...]
                }
        }
    }

    return everythingAdded;
}

int main() 
{
    ListNuoveLezioni* nuove_lezioni = (ListNuoveLezioni*)malloc(sizeof(ListNuoveLezioni));
    if (nuove_lezioni == NULL) {
        printf("Could not allocate memory. [1]");
        exit(1);
    }

    nuove_lezioni->informazioni = (NuoveLezioni*)malloc(sizeof(NuoveLezioni) * INITIAL_COUNT);
    if (nuove_lezioni->informazioni == NULL) {
        printf("Could not allocate memory. [2]");
        exit(1);
    }
    
    nuove_lezioni->size = INITIAL_COUNT;
    nuove_lezioni->lastIndex = 0;

    nuove_lezioni->informazioni[0].matricola = 54321;
    nuove_lezioni->informazioni[0].durata = 2;

    nuove_lezioni->informazioni[1].matricola = 54321;
    nuove_lezioni->informazioni[1].durata = 1;

    nuove_lezioni->informazioni[2].matricola = 54321;
    nuove_lezioni->informazioni[2].durata = 3;
    
    char fileName[] = "agenda.txt";
    ListStudente studenti = leggi_lezioni(fileName);

    if (studenti != NULL) studenti = studenti->first;
    stampa_lista(studenti);

    int lez_non_aggiunte;
    inserisci_nuove_lezioni(nuove_lezioni, &studenti, &lez_non_aggiunte);

    puts("");
    printf("Non sono riuscito ad aggiungere %d nuove lezioni al calendario.", lez_non_aggiunte);
    return 0;
}
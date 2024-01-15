#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LEZIONI 8

#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#else
#define CLEAR_CONSOLE system("clear")
#endif

typedef struct {
    int ora_inizio;
    int durata;
} Lezione;

typedef struct Studente {
    int matricola;
    char nome_e_cognome[100];
    Lezione *lezioni;
    int nrLezioni;

    struct Studente *next;
} Studente;

typedef struct {
    int matricola;
    int durata;
} NuovaLezione;

typedef struct {
    NuovaLezione *data;
    int size;
    int lastIndex;
} ListNuoveLezioni;

void aggiungi_elemento(ListNuoveLezioni** nuove_lezioni, NuovaLezione *lezione) 
{
    int firstAvailableIndex = (*nuove_lezioni)->lastIndex + 1;
    (*nuove_lezioni)->data[firstAvailableIndex] = *lezione;
    (*nuove_lezioni)->lastIndex++; 
}

void sort_by_ascending(Studente *stud) 
{
    bool swapping = true;
    while (swapping)
    {
        swapping = false;
        for (int i = 0; i < stud->nrLezioni - 1; i++)
        {
            Lezione swapElement;
            if (stud->lezioni[i].ora_inizio > stud->lezioni[i + 1].ora_inizio) 
            {
                swapping = true;
                swapElement = stud->lezioni[i];
                stud->lezioni[i] = stud->lezioni[i + 1];
                stud->lezioni[i + 1] = swapElement;
            }
        }
    }
}

bool head_insert(Studente **list, Studente *node) 
{
    if (node == NULL) return false;

    node->next = *list;
    *list = node;
    return true;
}

void stampa_lista(Studente **list) 
{
    if (*list == NULL) return;

    Studente *nodo = *list;

    printf("Matricola #%d - Studente: %s\n", (*nodo).matricola, (*nodo).nome_e_cognome);
    printf("Lezioni in agenda:\n");

    for (int i = 0; i < (*nodo).nrLezioni; i++) 
    {
        printf("[%d]\t> Inizio ore: %d - Durata: %d ore;\n",
            i + 1,
            (*nodo).lezioni[i].ora_inizio,
            (*nodo).lezioni[i].durata);
    }
    puts("");

    stampa_lista(&(*nodo).next);
}

Studente* leggi_lezioni(char fileName[])
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) 
    {
        printf("Unable to open '%s'. Exiting...", fileName);
        exit(EXIT_FAILURE);
    }

    Studente* out_list = NULL;

    int idxNode = 0;
    while (!feof(pFile)) 
    {
        Studente *stud = (Studente*)malloc(sizeof(Studente));
        if (stud == NULL) 
        {
            printf("Allocazione memoria non riuscita!\n\n");
        }

        char tmpNome[100], tmpCognome[100];
        fscanf(pFile, "%d %s %s", &stud->matricola, tmpNome, tmpCognome);

        /*
         * Se la riga che sto leggendo è vuota, esco dal ciclo - potrebbe succedere dopo l'ultima
         * riga del file
         */
        if (strcmp(tmpNome, "") == 0 || strcmp(tmpCognome, "") == 0)
            break;
        
        snprintf(stud->nome_e_cognome, 100, "%s %s", tmpNome, tmpCognome);
        
        stud->lezioni = (Lezione*)malloc(sizeof(Lezione) * MAX_LEZIONI);
        if (stud->lezioni == NULL) 
        {
            printf("Unable to allocate memory. Exiting...");
            exit(EXIT_FAILURE);
        }

        stud->nrLezioni = 0;
        int idxLezione = 0;
        while (fgetc(pFile) == ' ') 
        {
            fscanf(pFile, "%d %d", 
                &(stud->lezioni[idxLezione].ora_inizio),
                &(stud->lezioni[idxLezione].durata));
            
            idxLezione++;
            stud->nrLezioni++;
        }

        sort_by_ascending(stud);

        if (!head_insert(&out_list, stud)) 
            printf("[%d] Inserimento non riuscito\n", idxNode);

        idxNode++;
    }

    printf("Nodi inseriti: %d\n\n", idxNode);
    return out_list;
}

Studente* get_studente_by_matricola(Studente *list, int matricola) 
{
    Studente *current_node = list;
    while (current_node != NULL) 
    {
        if (current_node->matricola == matricola)
            return current_node;

        current_node = current_node->next;
    }

    return NULL;
}

bool inserisci_nuove_lezioni(Studente *list, ListNuoveLezioni *nuove_lezioni, int *nr_lezioni_non_aggiunte) 
{
    bool allInserted = true;

    ListNuoveLezioni *nuove_lezioni_non_aggiunte = (ListNuoveLezioni *)malloc(sizeof(ListNuoveLezioni));
    if (nuove_lezioni_non_aggiunte == NULL) 
    {
        printf("Could not allocate memory.");
        return false;
    }

    nuove_lezioni_non_aggiunte->data = NULL;
    nuove_lezioni_non_aggiunte->lastIndex = -1;
    nuove_lezioni_non_aggiunte->size = 0;

    for (int i = 0; i <= nuove_lezioni->lastIndex; i++) 
    {
        Studente *stud_interessato = get_studente_by_matricola(list, nuove_lezioni->data[i].matricola);
        if (stud_interessato == NULL) continue;

        bool lezioneInserita = false;
        Lezione* lezioni = stud_interessato->lezioni;
        for (int j = 0; j < stud_interessato->nrLezioni; j++)
        {
            int durata_intermezzo = lezioni[j + 1].ora_inizio - lezioni[j].ora_inizio;
            if (nuove_lezioni->data[j].durata <= durata_intermezzo) 
            {
                lezioneInserita = true;
            }
        }

        if (!lezioneInserita) 
        {
            nr_lezioni_non_aggiunte++;
            allInserted = false;
            
            int *current_size = &(nuove_lezioni_non_aggiunte->size);
            current_size++;
            nuove_lezioni_non_aggiunte->data =
                    (NuovaLezione*)realloc( (NuovaLezione*)nuove_lezioni_non_aggiunte->data, (unsigned long)current_size * sizeof(NuovaLezione));

            if (nuove_lezioni_non_aggiunte->data == NULL)
            {
                printf("Could not reallocate memory. Exiting...");
                return false;
            }
            
            aggiungi_elemento(&nuove_lezioni_non_aggiunte, &nuove_lezioni->data[i]);
        }
    }

    return allInserted;
}

int main() 
{
    CLEAR_CONSOLE;

    ListNuoveLezioni *nuove_lezioni = (ListNuoveLezioni*)malloc(sizeof(ListNuoveLezioni));
    nuove_lezioni->data = malloc(sizeof(NuovaLezione) * MAX_LEZIONI);
    nuove_lezioni->size = MAX_LEZIONI;
    nuove_lezioni->lastIndex = -1;

    NuovaLezione lez_1 = {67890, 2};
    NuovaLezione lez_2 = {12345, 1};
    aggiungi_elemento(&nuove_lezioni, &lez_1);
    aggiungi_elemento(&nuove_lezioni, &lez_2);

    Studente *list = leggi_lezioni("agenda.txt");
    stampa_lista(&list);

    int nr_lezioni_non_aggiunte = 0;
    inserisci_nuove_lezioni(list, nuove_lezioni, &nr_lezioni_non_aggiunte);
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ESAMI 25
#define SIZE 100

#ifdef _WIN32
#define CLEAR_CONSOLE system("cls")
#else
#define CLEAR_CONSOLE system("clear")
#endif

typedef struct Esame {
  char id_esame[16];
  char esito[5];
} Esame;

typedef struct Studente{
  int matricola;
  char nome_e_cognome[100];
  Esame *sequenza_esami;
  int nrEsami;

  struct Studente* next;
} Studente;

typedef struct {
  int matricola;
  char *esami[MAX_ESAMI];
} PianoStudiStudente;

typedef struct ListPianoStudi {
  PianoStudiStudente *data;
  int size;
  int lastIndex;
} ListPianoStudi;

typedef struct  {
  float perc_promossi;
  float perc_lode;
  int nr_ritirati;
} Statistiche;

void sort_by_ascending(ListPianoStudi **list) 
{
  if ((*list)->lastIndex < 1) return;

  bool swapping = true;
  while (swapping) 
  {
    swapping = false;
    for (int i = 0; i < (*list)->lastIndex; i++) 
    {
      PianoStudiStudente swapElement;
      if ((*list)->data[i].matricola > (*list)->data[i + 1].matricola) 
      {
        swapping = true;

        swapElement = (*list)->data[i];
        (*list)->data[i] = (*list)->data[i + 1];
        (*list)->data[i + 1] = swapElement;
      }
    }
  }
}

/*
 * Funzione per aggiungere un elemento al piano di studi; la funzione ordina
 * automaticamente la lista ad ogni inserimento, in base alla matricola in ordine *crescente*.
 */
void aggiungi_elemento(ListPianoStudi **piano_di_studi, PianoStudiStudente *elemento) 
{
  int firstAvailableIndex = (*piano_di_studi)->lastIndex + 1;
  (*piano_di_studi)->data[firstAvailableIndex] = *elemento;

  (*piano_di_studi)->lastIndex = firstAvailableIndex;
  sort_by_ascending(piano_di_studi);
}

/*
 * Funzione per inserire un nodo in testa alla linked list
 */
bool head_insert(Studente **list, Studente **node) 
{
  if (list == NULL || node == NULL) return false;
  
  (*node)->next = *list;
  *list = *node;

  return true;
}

Studente* leggi_carriera(char fileName[]) 
{
  FILE *pFile = fopen(fileName, "r");
  if (pFile == NULL) 
  {
    printf("Unable to open '%s'. Exiting...", fileName);
    return NULL;
  }

  Studente* out_list = (Studente*)malloc(sizeof(Studente));
  if (out_list == NULL) 
  {
    printf("Unable to allocate memory. Exiting...");
    return NULL;
  }

  while(!feof(pFile)) 
  {
    Studente *stud = (Studente*)malloc(sizeof(Studente));
    if (stud == NULL) return NULL;

    stud->nrEsami = 0;
    char tmpNome[100], tmpCognome[100];

    fscanf(pFile, "%d %s %s", 
      &(stud->matricola),
      tmpNome,
      tmpCognome);
  
    /* 
     * Aggiorno il campo 'nome_e_cognome' della struct Studente, poichè il funzionamento di 'fscanf' non mi permette
     * farlo in maniera automatica
     */
    snprintf(stud->nome_e_cognome, 100, "%s %s", tmpNome, tmpCognome);

    stud->sequenza_esami = (Esame*)malloc(sizeof(Esame) * MAX_ESAMI);
    if (stud->sequenza_esami == NULL) {
      printf("Unable to allocate memory. Exiting...");
      return NULL;
    }

    /*
     * Lettura di un numero indeterminato di coppie di dati - 'id_esame' ed 'esito'
     */
    int idxEsame = 0;
    while (fgetc(pFile) == ' ') 
    {
      fscanf(pFile, "%s %s", 
        stud->sequenza_esami[idxEsame].id_esame,
        stud->sequenza_esami[idxEsame].esito);

      idxEsame++;
      stud->nrEsami++;
    }

    // printf("Studente %s, Matricola: %d\n", stud->nome_e_cognome, stud->matricola);
    // printf("Esami sostenuti:\n");

    // for (int i = 0; i < idxEsame; i++) 
    // {
    //   printf("\t> Codice #%s; Esito: %s\n", stud->sequenza_esami[i].id_esame, stud->sequenza_esami[i].esito);
    // }

    // puts("");


    if (!head_insert(&out_list, &stud)) 
    {
      printf("Inserimento non avvenuto.");
    }
  }

  return out_list;
}

void pulisci_lista(Studente **node, int matricola) 
{
  if (*node == NULL) return;

  if ((*node)->matricola == matricola) 
  {

  }
}

Statistiche statistiche_esame(Studente **list, char id_esame[16])
{
  Statistiche output_stats = {0,0,0};

  Studente *node = *list;
  int nrStudentiEsame = 0, nrPromossi = 0, nrLode = 0;
  while (node != NULL) 
  {
    bool found = false;
    int idxEsame = 0;
    while (!found && idxEsame < (*node).nrEsami) 
    {
      if (strcmp(node->sequenza_esami[idxEsame].id_esame, id_esame) == 0) 
      {
        found = true;
        nrStudentiEsame++;

        if (strcmp(node->sequenza_esami[idxEsame].esito, "I") != 0 &&
          strcmp(node->sequenza_esami[idxEsame].esito, "R") != 0) 
          nrPromossi++;

        if (strcmp(node->sequenza_esami[idxEsame].esito, "30L") == 0)
          nrLode++;

        if (strcmp(node->sequenza_esami[idxEsame].esito, "R") == 0)
          output_stats.nr_ritirati++;
      }

      idxEsame++;
    }

    node = node->next;
  }

  output_stats.perc_lode = ((float)nrLode / nrStudentiEsame) * 100;
  output_stats.perc_promossi = ((float)nrPromossi / nrStudentiEsame) * 100;

  return output_stats;
}

int main() 
{
  CLEAR_CONSOLE;
  ListPianoStudi* piano_di_studi = (ListPianoStudi*)malloc(sizeof(ListPianoStudi));
  piano_di_studi->data = (PianoStudiStudente*)malloc(sizeof(PianoStudiStudente) * SIZE);
  piano_di_studi->size = SIZE;
  piano_di_studi->lastIndex = -1;
  PianoStudiStudente stud_2 = {1, {"GAL", "Analisi I", "Fisica"}};
  PianoStudiStudente stud_1 = {2, {"Programmazione", "OOP", "Programmazione di Reti"}};
  aggiungi_elemento(&piano_di_studi, &stud_2);
  aggiungi_elemento(&piano_di_studi, &stud_1);

  for (int i = 0; i <= piano_di_studi->lastIndex; i++) 
  {
    printf("[%d] Matricola: #%d\n", i, piano_di_studi->data[i].matricola);
    printf("Esami previsti: \n");

    for (int j = 0; j < MAX_ESAMI; j++) 
    {
      if (piano_di_studi->data[i].esami[j] != NULL)
        printf("\t> %s\n", piano_di_studi->data[i].esami[j]);
    }

    puts("");
  }

  Studente *list = leggi_carriera("./carriera.txt");
  Statistiche stats = statistiche_esame(&list, "INF120");

  printf("Esame %s:\n", "INF120");
  printf("\t> Ritirati: %d\n", stats.nr_ritirati);
  printf("\t> Percentuale lode: %.2f%%\n", stats.perc_lode);
  printf("\t> Percentuale promossi: %.2f%%\n", stats.perc_promossi);
  return 0;
}
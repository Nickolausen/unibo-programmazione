#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_ESAMI 25
#define NR_STUDENTI 200
#define EMPTY_STRING ""

typedef struct esame {
  char id_esame[15 + 1];
  char esito[4 + 1];
} esame;

typedef struct studente {
  int matricola;
  char nome_e_cognome[100 + 1];
  esame esami[MAX_ESAMI];
  int nr_esami;

  struct studente *next;
} studente;

typedef struct _piano_di_studi {
  int matricola;
  char *esami[MAX_ESAMI];
} _piano_di_studi;

typedef struct list_piano_di_studi 
{
  _piano_di_studi *data;
  int last_index;
  int size;
} list_piano_di_studi;

typedef struct statistiche {
  float perc_superati;
  float perc_ritirati;
  float perc_lode;
} statistiche;

void inserisci_in_piano_studi(list_piano_di_studi *vect, _piano_di_studi *studente) 
{
  int first_index_available = vect->last_index + 1;
  if (first_index_available >= vect->size)
  {
    fprintf(stderr, "ERRORE: Impossibile inserire nuovi studenti\n");
    return;
  }

  for (int i = 0; i <= vect->last_index; i++) 
  {
    if (studente->matricola > vect->data[i].matricola) 
    {
      for (int j = vect->last_index + 1; j > i; j--)
      {
        vect->data[j] = vect->data[j - 1];
      }

      vect->data[i] = *studente;
      vect->last_index = first_index_available;
    }
  }
}

void aggiungi_carriera_studente(studente **list, studente *stud) 
{
  assert(stud != NULL);

  stud->next = *list;
  *list = stud;
}

studente *leggi_carriera(char *fileName)
{
  FILE *pFile = fopen(fileName, "r");
  assert(pFile != NULL);

  studente *out_list = NULL;

  while (!feof(pFile))
  {
    studente *new_stud = (studente *)malloc(sizeof(studente));
    assert(new_stud != NULL);

    char tmpNome[100 + 1], tmpCognome[100 + 1];
    fscanf(pFile, "%d %s %s", &(new_stud->matricola), tmpNome, tmpCognome);

    snprintf(new_stud->nome_e_cognome, 100, "%s %s", tmpNome, tmpCognome);

    new_stud->nr_esami = 0;
    while (fgetc(pFile) == ' ' && new_stud->nr_esami < MAX_ESAMI) 
    {
      fscanf(pFile, "%s %s", 
        new_stud->esami[new_stud->nr_esami].id_esame,
        new_stud->esami[new_stud->nr_esami].esito);

      new_stud->nr_esami++;
    }

    aggiungi_carriera_studente(&out_list, new_stud);
  }

  return out_list;
}

/* - da correggere - */
void pulisci_lista(studente **list, int matricola)
{
  static studente *prev_node = NULL;

  /* PASSO BASE DELLA RICORSIONE */
  if (*list == NULL) return; /* se ho raggiunto la fine della lista, esco dalla funzione */
  
  if ((*list)->matricola == matricola) /* se ho trovato la matricola corrispondente, elimino il nodo dalla lista */
  {
    /* Aggancio il nodo precedente a quello successivo, lasciando 'per aria' quello corrente */
    prev_node->next = (*list)->next;
    
    /* Elimino quello corrente */
    free(*list);

    prev_node = NULL;
  }
  else /* altrimenti continuo a cercare */
  {
    prev_node = *list;
    pulisci_lista(&((*list)->next), matricola);
  }

}

int index_of(list_piano_di_studi *piano_studi, int matricola)
{
  for (int i = 0; i <= piano_studi->last_index; i++) 
  {
    if (piano_studi->data[i].matricola == matricola)
      return i;
  }

  return -1;
}

bool includes(char *id_esame, int matricola, list_piano_di_studi *piano_studi) 
{
  int idx_studente = index_of(piano_studi, matricola);
  if (idx_studente == -1) return false;

  _piano_di_studi studente = piano_studi->data[idx_studente];
  for (int idx_esame = 0; idx_esame < MAX_ESAMI; idx_esame++)
  {
    if (strcmp(studente.esami[idx_esame], id_esame) == 0)
      return true;
  }

  return false;
}

statistiche *statistiche_esame(char *id_esame, studente *studenti, list_piano_di_studi *piano_studi) 
{
  statistiche *out_stats = (statistiche *)malloc(sizeof(statistiche));
  assert(out_stats != NULL);

  int tot_stud_con_esame = 0;
  for (int i = 0; i <= piano_studi->last_index; i++) 
  {
    /* se uno studente ha quell'esame previsto nel piano di studi, + 1 - diversamente + 0 */
    tot_stud_con_esame += includes(id_esame, piano_studi->data[i].matricola, piano_studi);
  }

  out_stats->perc_lode = 0;
  out_stats->perc_ritirati = 0;
  out_stats->perc_superati = 0;

  studente *current_stud = studenti;
  while (current_stud != NULL) 
  {
    char last_esito[4 + 1] = EMPTY_STRING;
    for (int idxEsame = 0; idxEsame < current_stud->nr_esami; idxEsame++) 
    {
      if (strcmp(current_stud->esami[idxEsame].id_esame, id_esame) == 0)
        strcpy(last_esito, current_stud->esami[idxEsame].esito);
    }

    if (strcmp("R", last_esito) == 0) 
    {
      out_stats->perc_ritirati++;
    } else if (strcmp("30L", last_esito) == 0)
    {
      out_stats->perc_lode++;
      out_stats->perc_superati++;
    } else if (strcmp("", last_esito) != 0 && strcmp("I", last_esito) != 0 )
    {
      out_stats->perc_superati++;
    }

    current_stud = current_stud->next;
  }

  out_stats->perc_lode = (out_stats->perc_lode * 100) / tot_stud_con_esame;
  out_stats->perc_ritirati = (out_stats->perc_ritirati * 100) / tot_stud_con_esame;
  out_stats->perc_superati = (out_stats->perc_superati * 100) / tot_stud_con_esame;
  
  return out_stats;
}

int main()
{
  list_piano_di_studi *piano_di_studi = (list_piano_di_studi *)malloc(sizeof(list_piano_di_studi));
  assert(piano_di_studi != NULL);

  piano_di_studi->data = malloc(sizeof(_piano_di_studi) * NR_STUDENTI);
  assert(piano_di_studi->data != NULL);
  piano_di_studi->last_index = -1;
  piano_di_studi->size = NR_STUDENTI;
  
  _piano_di_studi *stud1 = (_piano_di_studi *)malloc(sizeof(_piano_di_studi));
  assert(stud1 != NULL);
  stud1->matricola = 333145;
  strcpy(stud1->esami[0], "INF120");
  strcpy(stud1->esami[1], "INF070");
  strcpy(stud1->esami[2], "INF090");
  strcpy(stud1->esami[3], "INF100");

  _piano_di_studi *stud2 = (_piano_di_studi *)malloc(sizeof(_piano_di_studi));
  assert(stud2 != NULL);
  stud2->matricola = 33279;
  strcpy(stud2->esami[0], "GIU123");
  strcpy(stud2->esami[1], "GIU280");
  strcpy(stud2->esami[2], "GIU085");
  strcpy(stud2->esami[3], "GIU300");

  inserisci_in_piano_studi(piano_di_studi, stud1);
  inserisci_in_piano_studi(piano_di_studi, stud2);

  studente *studenti = leggi_carriera("carriera.txt");
  statistiche *stats = statistiche_esame("INF090", studenti, piano_di_studi);
  printf("=== Statistiche per esame 'INF090' ===\n");
  printf("\t> Percentuale di promossi: %.2f%%\n", stats->perc_superati);
  printf("\t> Percentuale di respinti: %.2f%%\n", stats->perc_ritirati);
  printf("\t> Percentuale di 30L: %.2f%%\n", stats->perc_lode);
  
  return EXIT_SUCCESS;
}